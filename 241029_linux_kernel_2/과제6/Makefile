CC = gcc
TARGET := g6app

#디바이스 드라이버 

KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build

obj-m += g6driver.o

PWD := $(CURDIR)

all: driver g6app

driver:
	make -C $(KERNEL_HEADERS) M=$(PWD) modules

clean:
	make -C $(KERNEL_HEADERS) M=$(PWD) clean
	rm -f *.o $(TARGET)

g6app:
	$(CC) -o $@ $@.c
