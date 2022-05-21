#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "pwm.h"
#define DEV_NAME "/dev/" DEVICE_NAME
int main(int argc, char **argv)
{
	int fd;
	int fd1;
	int fd2;
	int val;
	int ioarg;
	int i, a, b, flag = 0;
	int key_value[6];
	char buf[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	fd = open("/dev/keyint", 0);

	fd1 = open(DEV_NAME, O_RDWR);
	if (fd < 0)
	{
		printf("open devie error\n");
		return -1;
	}
	if (fd1 < 0)
	{
		printf("Open /dev/my_led file error\n");
		return -1;
	}

	while (1)
	{

		val = read(fd, key_value, sizeof(key_value));
		if (val < 0)
		{
			printf("read error\n");
			continue;
		}
		else if (key_value[0])
		{
			ioarg = 500;
			ioctl(fd1, PWM_IOCTL_SET_FREQ, (int *)&ioarg);
			usleep(1000);
			ioctl(fd1, PWM_IOCTL_STOP);
		}
		else if (key_value[1])
		{
			ioarg = 1000;
			ioctl(fd1, PWM_IOCTL_SET_FREQ, (int *)&ioarg);
			usleep(1000);
			ioctl(fd1, PWM_IOCTL_STOP);
		}
		else if (key_value[2])
		{
			ioarg = 1500;
			ioctl(fd1, PWM_IOCTL_SET_FREQ, (int *)&ioarg);
			usleep(1000);
			ioctl(fd1, PWM_IOCTL_STOP);
		}
		else if (key_value[3])
		{
			ioarg = 2000;
			ioctl(fd1, PWM_IOCTL_SET_FREQ, (int *)&ioarg);
			usleep(1000);
			ioctl(fd1, PWM_IOCTL_STOP);
		}
		else if (key_value[4])
		{
			ioarg = 2500;
			ioctl(fd1, PWM_IOCTL_SET_FREQ, (int *)&ioarg);
			usleep(1000);
			ioctl(fd1, PWM_IOCTL_STOP);
		}
		else if (key_value[5])
		{

			ioarg = 3000;
			ioctl(fd1, PWM_IOCTL_SET_FREQ, (int *)&ioarg);
			usleep(1000);
			ioctl(fd1, PWM_IOCTL_STOP);
		}
	}
	close(fd);
	return 0;
}
