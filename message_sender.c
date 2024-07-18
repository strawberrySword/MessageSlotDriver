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

    if (argc != 4)
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
    message_length = strlen(argv[3]);
    if (write(fd, argv[3], message_length) != message_length)
    {
        printf("Error: couldnt write message to channel\n");
        exit(-1);
    }

    close(fd);
    return 0;
}
