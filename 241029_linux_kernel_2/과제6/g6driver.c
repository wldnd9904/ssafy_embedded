#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#define NOD_NAME "g6"
static int NOD_MAJOR;
static struct class *cls;
static dev_t dev;

MODULE_LICENSE("GPL");

static int deviceFileOpen(struct inode *inode, struct file *filp){
	pr_info("[OPEN] welcome\n");
	return 0;
}

static int deviceFileClose(struct inode *inode, struct file *filp){
	pr_info("[CLOSE] release\n");
	return 0;
}

static ssize_t deviceFileIoctl(struct file *filp, unsigned int cmd, unsigned long arg){
	pr_alert("command number : %d\n", cmd);
	switch(cmd){
		case _IO(0,3):
			pr_info("AGE : %lu\n", arg);
			break;
		case _IO(0,4):
			pr_info("Birth month : %lu\n", arg);
			break;
		case _IO(0,5):
			pr_info("Birth day : %lu\n", arg);
			break;
		case _IO(0,6):
			pr_info("phone number : %lu\n", arg);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}
	

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = deviceFileOpen,
	.release = deviceFileClose,
	.unlocked_ioctl = deviceFileIoctl,
};

static int __init deviceFileInit(void){
	NOD_MAJOR = register_chrdev(0, NOD_NAME, &fops);
	if(NOD_MAJOR < 0){
		pr_alert("Register File\n");
		return NOD_MAJOR;
	}

	pr_info("[INSMOD] hi\n");

	dev = MKDEV(NOD_MAJOR, 0);
	cls = class_create(NOD_NAME);
	device_create(cls, NULL, dev, NULL, NOD_NAME);
	
	return 0;
}

static void __exit deviceFileExit(void){
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev(NOD_MAJOR, NOD_NAME);
	pr_info("[RMMOD] bye\n");
}

module_init(deviceFileInit);
module_exit(deviceFileExit);
