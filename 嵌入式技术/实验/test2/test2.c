#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void)
{
    int fd;
    char buf[10] = {0, 1, 2, 3, 4, 5, 6, 7};
    fd = open("/dev/my_led", O_RDWR);
    if (fd < 0)
    {
        printf("Open /dev/my_led file error\n");
        return -1;
    }
    while (1)
    {
        write(fd, &buf[1], 1);
        sleep(1);
        write(fd, &buf[0], 1);
        usleep(100);
        write(fd, &buf[3], 1);
        sleep(1);
        write(fd, &buf[2], 1);
        usleep(100);
        write(fd, &buf[5], 1);
        sleep(1);
        write(fd, &buf[4], 1);
        usleep(100);
        write(fd, &buf[7], 1);
        sleep(1);
        write(fd, &buf[6], 1);
        usleep(100);
        write(fd, &buf[5], 1);
        sleep(1);
        write(fd, &buf[4], 1);
        usleep(100);
        write(fd, &buf[3], 1);
        sleep(1);
        write(fd, &buf[2], 1);
        usleep(100);
        write(fd, &buf[1], 1);
        sleep(1);
        write(fd, &buf[0], 1);
        usleep(100);
    }
    close(fd);
    return 0;
}
