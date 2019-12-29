obj-m :=mydev.o
HEAD :=$(shell uname -r)
KERNEL := /usr/src/linux-headers-$(HEAD)/
all:
	make -C $(KERNEL) M=$(shell pwd) modules
clean:
	make -C $(KERNEL) M=$(shell pwd) clean
install:
	ismod mydev.ko
unistall:
	rmmod mydev

