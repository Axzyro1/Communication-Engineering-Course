#include <linux/clk.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/types.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/mach/time.h>
#include <asm/uaccess.h>
#include <mach/hardware.h>
#include <mach/regs-irq.h>
#include <mach/map.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-e.h>
#include <mach/gpio-bank-f.h>
#include <mach/gpio-bank-k.h>
#include <plat/regs-timer.h>
#include <plat/gpio-cfg.h>
#include "pwm.h"
static struct semaphore lock;
/* freq:  pclk/50/16/65536 ~ pclk/50/16  
 * if pclk = 50MHz, freq is 1Hz to 62500Hz 
 * human ear : 20Hz~ 20000Hz 
*/
/*中断处理函数*/
/*
   static irqreturn_t timer_function(int irq, void *dev_id)
   {
   printk(KERN_INFO"the first irq is OK\n");
   return IRQ_RETVAL(IRQ_HANDLED);
   }
 */
/*pwm frequency set program*/
static void PWM_Set_Freq(unsigned long freq)
{
	unsigned long tcon;
	unsigned long tcnt;
	unsigned long tcfg1;
	unsigned long tcfg0;
	struct clk *clk_p;
	unsigned long pclk;
	unsigned tmp;
	tmp = readl(S3C64XX_GPFCON);
	tmp &= ~(0x3U << 30); //
	tmp |= (0x2U << 30);  //
	writel(tmp, S3C64XX_GPFCON);
	tcon = __raw_readl(S3C_TCON);
	tcfg1 = __raw_readl(S3C_TCFG1);
	tcfg0 = __raw_readl(S3C_TCFG0);
	//prescaler = 50
	tcfg0 &= ~S3C_TCFG_PRESCALER0_MASK;
	tcfg0 |= (50 - 1);
	//mux = 1/16
	tcfg1 &= ~(S3C_TCFG1_MUX0_MASK | S3C_TCFG1_MUX1_MASK);
	tcfg1 |= S3C_TCFG1_MUX0_DIV16 | S3C_TCFG1_MUX1_DIV16; //timer1ÉèÖÃÎª16·ÖÆµ
	__raw_writel(tcfg1, S3C_TCFG1);
	__raw_writel(tcfg0, S3C_TCFG0);
	clk_p = clk_get(NULL, "pclk");
	pclk = clk_get_rate(clk_p);
	tcnt = (pclk / 50 / 16) / freq;
	__raw_writel(tcnt, S3C_TCNTB(1));	  //
	__raw_writel(tcnt / 2, S3C_TCMPB(1)); //
	tcon &= ~(0x1f << 8);
	tcon |= (0xb << 8); //disable deadzone, auto-reload, inv-off, update TCNTB0&TCMPB0, start timer 0
	__raw_writel(tcon, S3C_TCON);
	tcon &= ~(2 << 8); //clear manual update bit
	__raw_writel(tcon, S3C_TCON);
}

/*stop pwm*/

void PWM_Stop(void)
{
	unsigned tmp;
	tmp = readl(S3C64XX_GPFCON);
	tmp &= ~(0x3U << 30);
	writel(tmp, S3C64XX_GPFCON);
}

static int s3c64xx_pwm_open(struct inode *inode, struct file *file)
{
	if (!down_trylock(&lock))
		return 0;
	else
		return -EBUSY;
}
static int s3c64xx_pwm_close(struct inode *inode, struct file *file)
{
	up(&lock);
	return 0;
}
static long s3c64xx_pwm_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)

{
	int ioarg;
	switch (cmd)
	{
	case PWM_IOCTL_SET_FREQ:
		if (arg == 0)
		{
			printk("<1>" DEVICE_NAME "\tfrequency is zero\n");
			return -EINVAL;
		}
		get_user(ioarg, (int *)arg);
		printk("<1>" DEVICE_NAME "\tset frequency%d\n", ioarg);
		PWM_Set_Freq(ioarg);
		break;
	case PWM_IOCTL_STOP:
	default:

		printk("<1>" DEVICE_NAME "\tstop pwm\n");
		PWM_Stop();
		break;
	}
	return 0;
}

static struct file_operations dev_fops = {

	.owner = THIS_MODULE,
	.open = s3c64xx_pwm_open,
	.release = s3c64xx_pwm_close,
	.unlocked_ioctl = s3c64xx_pwm_ioctl,

};

static struct miscdevice misc = {

	.minor = MISC_DYNAMIC_MINOR,

	.name = DEVICE_NAME,

	.fops = &dev_fops,

};

static int __init dev_init(void)
{
	int ret1;
	sema_init(&lock, 1);
	ret1 = misc_register(&misc);
	PWM_Set_Freq(1);
	printk("<1>" DEVICE_NAME "\tinitialized\n");
	/*申请定时器中断 */
	/*	
	enable_irq(IRQ_TIMER1);
	ret2 = request_irq(IRQ_TIMER1, timer_function, IRQ_TYPE_LEVEL_HIGH, DEVICE_NAME, NULL);
	if(0 != ret2)
	{
		printk(KERN_INFO"request the irq is err\n");
		return -1;
	}
	*/
	printk(KERN_INFO "request the irq is well\n");
	return ret1;
}
static void __exit dev_exit(void)
{
	misc_deregister(&misc);
}
module_init(dev_init);
module_exit(dev_exit);

