#디바이스 드라이버 

KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build

obj-m += g4driver.o

PWD := $(CURDIR)

driver:
	make -C $(KERNEL_HEADERS) M=$(PWD) modules

clean:
	make -C $(KERNEL_HEADERS) M=$(PWD) clean
