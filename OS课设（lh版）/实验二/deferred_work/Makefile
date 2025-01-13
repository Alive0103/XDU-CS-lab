CC=gcc
CFLAGS=-std=c11

ifneq  ($(KERNELRELEASE),)
obj-m:=deferred_work.o
else
KDIR := /lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.ko *.o *.symvers *.cmd *.cmd.o .*.cmd *.mod *.mod.c *.order

install:
	make -C $(KDIR) M=$(PWD) modules
	sudo insmod deferred_work.ko

uninstall:
	sudo rmmod deferred_work

endif