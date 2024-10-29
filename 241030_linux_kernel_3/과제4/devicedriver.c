#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <asm/io.h>

#define NOD_NAME "deviceFile"

MODULE_LICENSE("GPL");

static int NOD_MAJOR;
static struct class *cls;
static dev_t dev;

static volatile uint32_t *PERIBase;
static volatile uint32_t *IOBank0;
static volatile uint32_t *GPIO2_CTRL; 

static int deviceFile_open(struct inode *inode, struct file *filp){
    pr_info("Open Device\n");
    return 0;
}

static int deviceFile_release(struct inode *inode, struct file *filp){
    pr_info("Close Device\n");
    return 0;
}


static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = deviceFile_open,
    .release = deviceFile_release,
};

static int __init deviceFile_init(void){
    NOD_MAJOR = register_chrdev(NOD_MAJOR, NOD_NAME, &fops);
    if( NOD_MAJOR < 0 ){
        pr_alert("Register File\n");
        return NOD_MAJOR;
    }

    pr_info("Insmod Module\n");

    dev = MKDEV(NOD_MAJOR, 0);
    cls = class_create(NOD_NAME);
    device_create(cls, NULL, dev, NULL, NOD_NAME);

    pr_info("Major number %d\n", NOD_MAJOR);
    pr_info("Device file : /dev/%s\n", NOD_NAME);

    //base address mapping
    //64MB
    PERIBase = (uint32_t*) ioremap(0x1f00000000, 64*1024*1024);
    IOBank0 = PERIBase + 0xd0000/4;
    GPIO2_CTRL = IOBank0 + 0x9c/4;
	uint32_t FUNCSEL = (*GPIO2_CTRL) & 0b11111;
	uint32_t F_M = ((*GPIO2_CTRL)>>5) & 0b1111111;
	pr_info("FUNCSEL default: %x\n", FUNCSEL);
	pr_info("F_M default: %x\n", F_M);

    return 0;
}

static void __exit deviceFile_exit(void)
{
    iounmap(PERIBase);
    device_destroy(cls, dev);
    class_destroy(cls);

    unregister_chrdev(NOD_MAJOR, NOD_NAME);
    pr_info("Unload Module\n");
}

module_init(deviceFile_init);
module_exit(deviceFile_exit);
