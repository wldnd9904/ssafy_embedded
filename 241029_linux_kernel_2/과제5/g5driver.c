#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#define NOD_NAME "g5"
static int NOD_MAJOR;
static struct class *cls;
static dev_t dev;

MODULE_LICENSE("GPL");

static int deviceFileOpen(struct inode *inode, struct file *filp){
	pr_info("[OPEN] I'm beginner!\n");
	return 0;
}

static int deviceFileClose(struct inode *inode, struct file *filp){
	pr_info("[CLOSE] I'm Master!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = deviceFileOpen,
	.release = deviceFileClose,
};

static int __init deviceFileInit(void){
	NOD_MAJOR = register_chrdev(0, NOD_NAME, &fops);
	if(NOD_MAJOR < 0){
		pr_alert("Register File\n");
		return NOD_MAJOR;
	}

	pr_info("[INSMOD] hello ssafy\n");

	dev = MKDEV(NOD_MAJOR, 0);
	cls = class_create(NOD_NAME);
	device_create(cls, NULL, dev, NULL, NOD_NAME);
	pr_info("[INSMOD] Major number %d\n", NOD_MAJOR);
	pr_info("[INSMOD] Device file : /dev/%s\n", NOD_NAME);
	
	return 0;
}

static void __exit deviceFileExit(void){
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev(NOD_MAJOR, NOD_NAME);
	pr_info("[RMMOD] goodbye ssafy\n");
}

module_init(deviceFileInit);
module_exit(deviceFileExit);
