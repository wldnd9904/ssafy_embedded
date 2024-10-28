CC = gcc
TARGET := g5app

#디바이스 드라이버 

KERNEL_HEADERS=/lib/modules/$(shell uname -r)/build

obj-m += g5driver.o

PWD := $(CURDIR)

all: driver g5app

driver:
	make -C $(KERNEL_HEADERS) M=$(PWD) modules

clean:
	make -C $(KERNEL_HEADERS) M=$(PWD) clean
	rm -f *.o $(TARGET)

g5app:
	$(CC) -o $@ $@.c
