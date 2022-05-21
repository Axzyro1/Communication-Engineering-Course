#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
int main(int argc, char **argv)
{
  int fd;
  int val;
  int i;
  int key_value[6];
  fd = open("/dev/keyint", 0);
  if (fd < 0)
  {
    printf("open devie error\n");
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
        printf("KEY%d pressed\n", (i + 1), key_value[i]);
    }
  }
  close(fd);
  return 0;
}
