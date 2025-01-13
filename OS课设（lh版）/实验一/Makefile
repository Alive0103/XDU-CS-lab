CC=gcc
CFLAGS=-std=c11

ifneq  ($(KERNELRELEASE),)
obj-m:=kernel_module.o
else
KDIR := /lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.ko *.o *.symvers *.cmd *.cmd.o

install:
	make -C $(KDIR) M=$(PWD) modules
	sudo insmod kernel_module.ko

uninstall:
	sudo rmmod kernel_module

endif
