ifeq ($(KERNELRELEASE),)
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build

	PWD := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	rm -rf *.o *~core .depent .*.cmd *.ko *.mod.c .tmp_versions modules.order  Module.symvers hello.mod

.PHONY:	modules modules_install clean

else
	obj-m := hello.o
endif
