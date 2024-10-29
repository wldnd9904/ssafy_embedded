KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build

obj-m += devicedriver.o

PWD := $(CURDIR)

#driver build
driver:
	make -C $(KERNEL_HEADERS) M=$(PWD) modules

#driver 제거
clean:
	make -C $(KERNEL_HEADERS) M=$(PWD) clean
