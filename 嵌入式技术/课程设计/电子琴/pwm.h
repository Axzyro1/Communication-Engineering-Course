#ifndef __PWM_H__
#define __PWM_H__
#include <linux/ioctl.h>
#define DEVICE_NAME "pwm"
#define PWM_IOC_MAGIC 'l'
#define PWM_IOCTL_SET_FREQ _IOW(PWM_IOC_MAGIC, 1, int)
#define PWM_IOCTL_STOP _IO(PWM_IOC_MAGIC, 2)
#define PWM_IOC_MAXNR 2
#endif /* __PWM_H__ */
