#include "message_slot.h"

#include <fcntl.h>     /* open */
#include <unistd.h>    /* exit */
#include <sys/ioctl.h> /* ioctl */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    unsigned int channel_id;
    int fd, message_length, ret_val;
    char buffer[BUF_SIZE];

    if (argc != 3)
    {
        perror("invalid number of arguments\n");
        return -1;
    }

    channel_id = atoi(argv[2]);

    fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        perror("Can't open device file\n");
        exit(-1);
    }

    if (ioctl(fd, MSG_SLOT_CHANNEL, channel_id) < 0)
    {
        perror("failed creating channel\n");
        exit(-1);
    }

    if ((message_length = read(fd, buffer, BUF_SIZE)) < 0)
    {
        perror("Error: couldnt read message from channel\n");
        exit(-1);
    }
    close(fd);

    if (write(1, buffer, message_length) != message_length)
    {
        perror("Cant print message");
        exit(-1);
    }

    close(fd);
    return 0;
}
