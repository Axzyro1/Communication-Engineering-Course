#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main (void)
{
	int fd;
	char buf[10]={0,1,0,1};
	fd = open("/dev/my_led",O_RDWR);
	if (fd < 0)
	{
		printf ("Open /dev/my_led file error\n");
		return -1;
	}	
	while(1)
	{
		write(fd,&buf[0],1);
		sleep(1);
		write(fd,&buf[1],1);
		sleep(1);

	}
	close (fd);
	return 0;

}