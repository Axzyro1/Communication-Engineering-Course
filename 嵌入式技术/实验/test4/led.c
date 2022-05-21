#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/irq.h>
#include <mach/gpio.h>
#include <mach/gpio-bank-m.h>
#include <mach/regs-gpio.h>
#include <mach/map.h>
//#include <plat/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <mach/hardware.h>
#include <linux/io.h>
MODULE_LICENSE("GPL");
#define LED_MAJOR 240
int led_open(struct inode *inode, struct file *filp)
{
    unsigned int tmp;
    tmp = readl(S3C64XX_GPMCON);
    tmp = (tmp & ~(0xffff) | (0x1111)); //set the GPIO output mode
    writel(tmp, S3C64XX_GPMCON);
    printk(KERN_INFO "$$$$$$$$$$$led_open$$$$$$$$$\n");
    return 0;
}
ssize_t led_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    printk(KERN_INFO "$$$$$$$$$$led_read$$$$$$$$$\n");
    return count;
}
ssize_t led_write(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    char mbuf[10];
    unsigned int tmp;
    copy_from_user(mbuf, buf, count);
    switch (mbuf[0])
    {
    case 0:
        tmp = readl(S3C64XX_GPMDAT);
        tmp |= (0x1);
        writel(tmp, S3C64XX_GPMDAT);
        break;
    case 1:
        tmp = readl(S3C64XX_GPMDAT);
        tmp &= ~(0x1);
        writel(tmp, S3C64XX_GPMDAT);
        break;
    case 2:
        tmp = readl(S3C64XX_GPMDAT);
        tmp |= (0x2);
        writel(tmp, S3C64XX_GPMDAT);
        break;
    case 3:
        tmp = readl(S3C64XX_GPMDAT);
        tmp &= ~(0x2);
        writel(tmp, S3C64XX_GPMDAT);
        break;
    case 4:
        tmp = readl(S3C64XX_GPMDAT);
        tmp |= (0x4);
        writel(tmp, S3C64XX_GPMDAT);
        break;
    case 5:
        tmp = readl(S3C64XX_GPMDAT);
        tmp &= ~(0x4);
        writel(tmp, S3C64XX_GPMDAT);
        break;
    case 6:
        tmp = readl(S3C64XX_GPMDAT);
        tmp |= (0x8);
        writel(tmp, S3C64XX_GPMDAT);
        break;
    case 7:
        tmp = readl(S3C64XX_GPMDAT);
        tmp &= ~(0x8);
        writel(tmp, S3C64XX_GPMDAT);
        break;
    default:
        break;
    }
    printk(KERN_INFO "$$$$$$$$$$led_write$$$$$$$$$\n");
    return count;
}
int led_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "$$$$$$$$$$led_release$$$$$$$$$\n");
    return 0;
}
struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .read = led_read,
    .write = led_write,
    .release = led_release,
};
static int led_init(void)
{
    int rc;
    printk(KERN_INFO "Test led dev\n");
    rc = register_chrdev(LED_MAJOR, "led", &my_fops);
    if (rc < 0)
    {
        printk(KERN_INFO "register %s mychar dev error\n", "led");
        return -1;
    }
    printk(KERN_INFO "$$$$$$$$$ register led dev OK\n");
    return 0;
}
static void led_exit(void)
{
    unregister_chrdev(LED_MAJOR, "led");
    printk(KERN_INFO "Good Bye!\n");
}
module_init(led_init);
module_exit(led_exit);