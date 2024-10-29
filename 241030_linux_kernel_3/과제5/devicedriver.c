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
static volatile uint32_t *PADBank0;
static volatile uint32_t *GPIO20_CTRL;
static volatile uint32_t *PAD_GPIO20;

#define GPIO20_OFFSET 0xa4

static void ledon(void){
        pr_info("on\n");
    //OUTOVER 13:12 2 bit CLR
    *GPIO20_CTRL &= ~(0x3<<12);
    //OUTOVER 13:12 bit 0x3 SET
    *GPIO20_CTRL |= (0x3<<12);
}
static void ledoff(void){
    pr_info("off\n");
    //OUTOVER 13:12 2 bit CLR
    *GPIO20_CTRL &= ~(0x3<<12);

    //OUTOVER 13:12 bit 0x2 SET
    *GPIO20_CTRL |= (0x2<<12);
}
static int deviceFile_open(struct inode *inode, struct file *filp){
    pr_info("Open Device\n");
    return 0;
}

static int deviceFile_release(struct inode *inode, struct file *filp){
    pr_info("Close Device\n");
    return 0;
}

static ssize_t deviceFile_ioctl(struct file *filp, unsigned int cmd, unsigned long arg){
    switch(cmd){
        case _IO(0,3):
                ledon();
            break;
        case _IO(0,4):
            ledoff();
            break;
        default :
            return -EINVAL;
    }
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = deviceFile_open,
    .release = deviceFile_release,
    .unlocked_ioctl = deviceFile_ioctl,
};

//chmod 666 setting
char *node_devnode(const struct device *devc, umode_t *mode) {
    if (!mode)
        return NULL;
    if (devc->devt == dev)
        *mode = 0666;
    return NULL;
}

static int __init deviceFile_init(void){
    NOD_MAJOR = register_chrdev(NOD_MAJOR, NOD_NAME, &fops);
    if( NOD_MAJOR < 0 ){
        pr_alert("Register File\n");
        return NOD_MAJOR;
    }

    pr_info("Insmod Module\n");

    dev = MKDEV(NOD_MAJOR, 0);
    cls = class_create(NOD_NAME);
        //chmod outo
        cls->devnode = node_devnode;
    device_create(cls, NULL, dev, NULL, NOD_NAME);

    pr_info("Major number %d\n", NOD_MAJOR);
    pr_info("Device file : /dev/%s\n", NOD_NAME);

    //base address mapping
    //64MB
    PERIBase = (uint32_t*) ioremap(0x1f00000000, 64*1024*1024);
    IOBank0 = PERIBase + 0xd0000/4;
    PADBank0 = PERIBase + 0xf0000/4;
    GPIO20_CTRL = IOBank0 + GPIO20_OFFSET/4;
    //PAD_GPIO20 offset 0x54
    PAD_GPIO20 = PADBank0 + 0x54/4;

    //FUNSCEL 4:0 5bit CLR
    *GPIO20_CTRL &= ~(0x1f);

    //FUNSCEL 4:0 5bit 0x7 SET
    *GPIO20_CTRL |= (0x7);

    //OEOVER output enable 15:14 bit 0x3 SET
    *GPIO20_CTRL |= (0x3<<14);

        //PAD_GPIO20 7 bit CLR OUTPUT able
        *PAD_GPIO20 &= ~(0x1 << 7);

    //PAD_GPIO20 5:4 bit DRIVE 0x1 SET ( default )
    *PAD_GPIO20 |= (0x1<<4);

    pr_info("LED Access!\n");

    ledon();
    return 0;
}

static void __exit deviceFile_exit(void)
{
    ledoff();
    iounmap(PERIBase);
    device_destroy(cls, dev);
    class_destroy(cls);

    unregister_chrdev(NOD_MAJOR, NOD_NAME);
    pr_info("Unload Module\n");
}

module_init(deviceFile_init);
module_exit(deviceFile_exit);
