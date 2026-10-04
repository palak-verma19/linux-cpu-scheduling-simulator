#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "cpu_scheduler"
#define BUFFER_SIZE 256

static dev_t dev_number;
static struct cdev cpu_cdev;
static struct class *cpu_class;

static char device_buffer[BUFFER_SIZE] =
    "CPU Scheduler Device Ready\n";

static int cpu_device_open(struct inode *inode,
                           struct file *file)
{
    pr_info("cpu_scheduler: device opened\n");
    return 0;
}

static int cpu_device_release(struct inode *inode,
                              struct file *file)
{
    pr_info("cpu_scheduler: device closed\n");
    return 0;
}

static ssize_t cpu_device_read(struct file *file,
                               char __user *buffer,
                               size_t length,
                               loff_t *offset)
{
    size_t data_length;

    if (*offset >= strlen(device_buffer))
        return 0;

    data_length = strlen(device_buffer) - *offset;

    if (length < data_length)
        data_length = length;

    if (copy_to_user(buffer,
                     device_buffer + *offset,
                     data_length))
        return -EFAULT;

    *offset += data_length;

    return data_length;
}

static ssize_t cpu_device_write(struct file *file,
                                const char __user *buffer,
                                size_t length,
                                loff_t *offset)
{
    size_t write_length;

    write_length = length;

    if (write_length >= BUFFER_SIZE)
        write_length = BUFFER_SIZE - 1;

    if (copy_from_user(device_buffer,
                       buffer,
                       write_length))
        return -EFAULT;

    device_buffer[write_length] = '\0';

    pr_info("cpu_scheduler: data received from user space\n");

    return write_length;
}

static struct file_operations cpu_fops = {
    .owner = THIS_MODULE,
    .open = cpu_device_open,
    .read = cpu_device_read,
    .write = cpu_device_write,
    .release = cpu_device_release
};

static int __init cpu_scheduler_init(void)
{
    int result;

    result = alloc_chrdev_region(&dev_number,
                                 0,
                                 1,
                                 DEVICE_NAME);

    if (result < 0) {
        pr_err("cpu_scheduler: failed to allocate device number\n");
        return result;
    }

    cdev_init(&cpu_cdev, &cpu_fops);

    result = cdev_add(&cpu_cdev,
                      dev_number,
                      1);

    if (result < 0) {
        unregister_chrdev_region(dev_number, 1);
        return result;
    }

    cpu_class = class_create(DEVICE_NAME);

    if (IS_ERR(cpu_class)) {
        cdev_del(&cpu_cdev);
        unregister_chrdev_region(dev_number, 1);
        return PTR_ERR(cpu_class);
    }

    if (IS_ERR(device_create(cpu_class,
                             NULL,
                             dev_number,
                             NULL,
                             DEVICE_NAME))) {

        class_destroy(cpu_class);
        cdev_del(&cpu_cdev);
        unregister_chrdev_region(dev_number, 1);

        return -1;
    }

    pr_info("cpu_scheduler: kernel module loaded\n");
    pr_info("cpu_scheduler: /dev/%s created\n",
            DEVICE_NAME);

    return 0;
}

static void __exit cpu_scheduler_exit(void)
{
    device_destroy(cpu_class, dev_number);
    class_destroy(cpu_class);

    cdev_del(&cpu_cdev);
    unregister_chrdev_region(dev_number, 1);

    pr_info("cpu_scheduler: kernel module unloaded\n");
}

module_init(cpu_scheduler_init);
module_exit(cpu_scheduler_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Palak Verma");
MODULE_DESCRIPTION(
    "Linux character device for CPU scheduling simulator"
);
MODULE_VERSION("1.0");
