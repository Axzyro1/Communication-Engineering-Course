#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    int fd;
    int val;
    int i;
    int key_value[6];
    int fd2;
    char buf[10] = {0, 1, 2, 3, 4, 5};
    fd = open("/dev/keyint", 0);
    if (fd < 0)
    {
        printf("open devie error\n");
        return -1;
    }
    fd2 = open("/dev/my_led", O_RDWR);
    if (fd2 < 0)
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
        for (i = 0; i < 6; i++)
        {
            if (key_value[i])
            {
                printf("KEY%d pressed\n", (i + 1), key_value[i]);
                write(fd2, &buf[i], 1);
            }
        }
    }
    close(fd);
    close(fd2);
    return 0;
}
