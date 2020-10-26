obj-m += hello.c

all: 
	make CROSS_COMPILE=arm-linux-gnueabihf- -C ~/develop/rpi_kernel/modules/lib/modules/5.4.70-v7+/build M=$(shell pwd) modules

clean:
	make CROSS_COMPILE=arm-linux-gnueabihf- -C ~/develop/rpi_kernel/modules/lib/modules/5.4.70-v7+/build M=$(shell pwd) clean
