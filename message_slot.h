#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 235

#define MSG_SLOT_CHANNEL _IOW(MAJOR_NUM, 0, unsigned long)

#define DEVICE_RANGE_NAME "message_slot"
#define BUF_LEN 128
#define DEVICE_FILE_NAME "message_slot_ss"

typedef struct message_channel
{
    char[BUF_LEN] message;
    int length;
    int channel_id;
    struct message_channel *next;
} message_channel;

#endif