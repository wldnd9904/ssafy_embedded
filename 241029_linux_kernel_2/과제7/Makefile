CC = gcc
TARGET := g7app

#디바이스 드라이버 

KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build

obj-m += g7driver.o

PWD := $(CURDIR)

all: driver g7app

driver:
	make -C $(KERNEL_HEADERS) M=$(PWD) modules

clean:
	make -C $(KERNEL_HEADERS) M=$(PWD) clean
	rm -f *.o $(TARGET)

g7app:
	$(CC) -o $@ $@.c
