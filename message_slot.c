#undef __KERNEL__
#define __KERNEL__
#undef MODULE
#define MODULE

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");

#include "message_slot.h"

static message_channel *message_slots[255];

// Device Functions

static int device_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t, length, loff_t *offset)
{
    return -EINVAL;
}

static ssize_t device_write(struct file *file, char __user *buffer, size_t, length, loff_t *offset)
{
    return 0;
}

static long device_ioctl(struct file *file, unsigned int ioctl_command_id, unsigned long ioctl_param)
{
    if (ioctl_command_id != MSG_SLOT_CHANNEL)
    {
        printk("some some some \n");
        return EINVAL;
    }
    return 0;
}

// Device Setup

struct file_operations Fops = {
    .owner = THIS_MODULE,
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .unlocked_ioctl = device_ioctl,
    .release = device_release,
};