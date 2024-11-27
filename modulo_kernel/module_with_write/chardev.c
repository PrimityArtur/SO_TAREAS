/*
* chardev.c: Creates a char device that allows writing and reading messages
*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h> /* for put_user and copy_from_user */
MODULE_LICENSE("GPL");

/*
* Prototypes
*/
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "UCSP" /* Dev name as it appears in /proc/devices */
#define BUF_LEN 80         /* Max length of the message from the device */

/*
* Global variables
*/
static int Major;               /* Major number assigned to our device driver */
static int Device_Open = 0;     /* Is device open? */
static char msg[BUF_LEN];       /* The message the device will give when asked */
static char *msg_Ptr;
static struct file_operations fops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release // device_close
};

/*
* This function is called when the module is loaded
*/
int init_module(void)
{
    Major = register_chrdev(0, DEVICE_NAME, &fops);

    if (Major < 0) {
        printk(KERN_ALERT "Registering char device failed with %d\n", Major);
        return Major;
    }

    printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
    printk(KERN_INFO "the driver, create a dev file with:\n");
    printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
    printk(KERN_INFO "Write to the device using 'echo', read using 'cat'.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");

    return SUCCESS;
}

/*
* This function is called when the module is unloaded
*/
void cleanup_module(void)
{
    int ret; unregister_chrdev(Major, DEVICE_NAME);
    if (ret < 0)
        printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
}

/*
* Called when a process tries to open the device file
*/
static int device_open(struct inode *inode, struct file *file)
{
    if (Device_Open)
        return -EBUSY;

    Device_Open++;
    msg_Ptr = msg; // Reset the pointer to the start of the message
    try_module_get(THIS_MODULE);

    return SUCCESS;
}

/*
* Called when a process closes the device file
*/
static int device_release(struct inode *inode, struct file *file)
{
    Device_Open--; /* We're now ready for our next caller */
    module_put(THIS_MODULE);
    return 0;
}

/*
* Called when a process reads from the device
*/
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t * offset)
{
    int bytes_read = 0;

    /* If we're at the end of the message, return 0 signifying EOF */
    if (*msg_Ptr == 0)
        return 0;

    /* Copy data from the kernel space to the user space */
    while (length && *msg_Ptr) {
        put_user(*(msg_Ptr++), buffer++);
        length--;
        bytes_read++;
    }

    return bytes_read;
}

/*
* Called when a process writes to the device
*/
static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset)
{
    /* Ensure the length doesn't exceed the buffer size */
    if (length > BUF_LEN - 1)
        return -EINVAL;

    /* Copy data from the user space to the kernel space */
    if (copy_from_user(msg, buffer, length))
        return -EFAULT;

    msg[length] = '\0'; // Null-terminate the string
    msg_Ptr = msg;      // Reset the pointer for reading
    printk(KERN_INFO "New message written to device: %s\n", msg);

    return length;
}

