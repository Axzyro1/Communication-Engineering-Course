#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/device.h>
#include <linux/poll.h>
#include <linux/semaphore.h>
#include <linux/timer.h>
#include <asm/irq.h>
#include <asm/uaccess.h>
#include <mach/hardware.h>
#include <mach/irqs.h>
MODULE_LICENSE("GPL");
#define DEVICE_NAME "keyint"
#define KEYNUM 6
dev_t devid;
//static DEFINE_SEMAPHORE(key_lock);  //declare a mutex lock for keyint
//定义一个信号量
struct semaphore key_lock;
static struct fasync_struct *key_async;
static struct timer_list key_timer;
struct key_irq_desc
{
    int irq;             //irq num
    unsigned long flags; //irq flags,identified the way of irq here,eq.edge,level
    char *name;          //irq name
};
static struct key_irq_desc key_irqs[] = {
    //下降沿产生中断
    {IRQ_EINT(0), IRQF_TRIGGER_FALLING, "KEY1"},
    {IRQ_EINT(1), IRQF_TRIGGER_FALLING, "KEY2"},
    {IRQ_EINT(2), IRQF_TRIGGER_FALLING, "KEY3"},
    {IRQ_EINT(3), IRQF_TRIGGER_FALLING, "KEY4"},
    {IRQ_EINT(4), IRQF_TRIGGER_FALLING, "KEY5"},
    {IRQ_EINT(5), IRQF_TRIGGER_FALLING, "KEY6"},
};
/*define a waiting queue here*/
static DECLARE_WAIT_QUEUE_HEAD(key_waitq);
/*define a event flag ev_press*/
static volatile int ev_press = 0;
static volatile int press_cnt[KEYNUM] = {0, 0, 0, 0, 0, 0};
/*中断处理函数*/
static irqreturn_t keys_interrupt(int irq, void *dev_id)
{
    volatile int *press_cnt = (volatile int *)dev_id;
    /*set the pressed key flag(must do here due to not be static value)*/
    *press_cnt = *press_cnt + 1;
    //延时10ms后执行定时器处理函数
    mod_timer(&key_timer, jiffies + HZ / 100); //start timer after 10ms
    return IRQ_RETVAL(IRQ_HANDLED);
}
//定时器处理函数
static void key_timer_func(unsigned long data)
{
    ev_press = 1;
    //唤醒等待队列
    wake_up_interruptible(&key_waitq);
    kill_fasync(&key_async, SIGIO, POLL_IN);
}
static int key_fasync(int fd, struct file *filp, int on)
{
    printk("Function key_fasync\n");
    return fasync_helper(fd, filp, on, &key_async);
}
static unsigned key_poll(struct file *file, poll_table *wait)
{
    unsigned int mask = 0;
    //指明要使用的等待队列
    poll_wait(file, &key_waitq, wait);
    //返回掩码
    if (ev_press)
        mask |= POLL_IN | POLLRDNORM;
    printk("poll wait\n");
    return mask;
}
static int key_open(struct inode *inode, struct file *file)
{
    int num;
    if (file->f_flags & O_NONBLOCK)
    {
        if (down_trylock(&key_lock))
            return -EBUSY;
    }
    else
    {
        down(&key_lock);
    }
    //为每个按键注册中断处理程序
    for (num = 0; num < KEYNUM; num++)
    {
        request_irq(key_irqs[num].irq, keys_interrupt, key_irqs[num].flags, key_irqs[num].name, (void *)&press_cnt[num]);
    }
    return 0;
}
static int key_close(struct inode *inode, struct file *file)
{
    int num;
    //释放中断号
    for (num = 0; num < 6; num++)
    {
        free_irq(key_irqs[num].irq, (void *)&press_cnt[num]);
    }
    up(&key_lock);
    printk("key_close free irqs\n");
    return 0;
}
static int key_read(struct file *filp, char __user *buff, size_t count, loff_t *offp)
{
    //    unsigned int err;
    //判断是阻塞读还是非阻塞读
    if (filp->f_flags & O_NONBLOCK)
    {
        if (!ev_press)
            return -EAGAIN;
    }
    else
    {
        /*if ev_press==0,then sleep*/
        /*阻塞，当有按键按下时(中断)被唤醒*/
        wait_event_interruptible(key_waitq, ev_press);
    }
    //阻塞结束，有键按下了
    ev_press = 0;
    //拷贝数据到用户空间
    copy_to_user(buff, (const void *)press_cnt, min(sizeof(press_cnt), count));
    memset((void *)press_cnt, 0, sizeof(press_cnt));
    //    printk("read and clean press_cnt\n");
    return 1;
}
static struct file_operations key_ops = {
    .owner = THIS_MODULE,
    .open = key_open,
    .release = key_close,
    .read = key_read,
    .poll = key_poll,
    .fasync = key_fasync,
};
static struct cdev *cdev_keyint;
static struct class *keyint_class;
//模块初始化函数
static int __init s3c6410_keyint_init(void)
{
    int val;
    /*timer initial */
    init_timer(&key_timer);
    key_timer.function = key_timer_func;
    add_timer(&key_timer);
    /*初始化信号量*/
    init_MUTEX(&key_lock);
    /*register device*/
    val = alloc_chrdev_region(&devid, 0, 1, DEVICE_NAME);
    if (val)
    {
        return -1;
        printk("register keyint error\n");
    }
    cdev_keyint = cdev_alloc();
    cdev_init(cdev_keyint, &key_ops);
    cdev_keyint->owner = THIS_MODULE;
    cdev_keyint->ops = &key_ops;
    val = cdev_add(cdev_keyint, devid, 1);
    if (val)
    {
        return -1;
        printk("add device error\n");
    }
    keyint_class = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(keyint_class, NULL, devid, NULL, "%s", DEVICE_NAME);
    printk("KEY initialezed ^_^\n");
    return 0;
}
static void __exit s3c6410_keyint_exit(void)
{
    cdev_del(cdev_keyint);
    device_destroy(keyint_class, devid);
    class_destroy(keyint_class);
    unregister_chrdev_region(devid, 1);
}
module_init(s3c6410_keyint_init);
module_exit(s3c6410_keyint_exit);
