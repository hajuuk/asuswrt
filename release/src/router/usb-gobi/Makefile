NET_USB_GOBI = $(INSTALLDIR)/lib/modules/$(LINUX_KERNEL)/kernel/drivers/net/usb/gobi/
PWD = $(shell pwd)
MODULE_DIR = $(PWD)/kernel_module/gobi
GOBI_KO = $(MODULE_DIR)/gobi.ko
GOBI_UTIL = src/gobi

include $(LINUXDIR)/.config
include $(TOP)/.config

ifeq ($(RTCONFIG_QCA),y)
CROSS_TOOLCHAIN_DIR=$(TOOLCHAIN)
LIBRT_VERSION=0.9.33.2
endif

all: $(GOBI_KO) $(GOBI_UTIL)

$(GOBI_KO):
	$(MAKE) -C $(LINUXDIR) SUBDIRS=$(MODULE_DIR) modules CONFIG_USB_NET_GOBI=m

$(GOBI_UTIL):
	$(MAKE) -C src

clean:
	$(MAKE) -C $(LINUXDIR) SUBDIRS=$(MODULE_DIR) clean
	$(MAKE) -C src clean

install: $(GOBI_KO) $(GOBI_UTIL)
	@rm -rf $(INSTALLDIR)
	@install -d $(INSTALLDIR)
	@install -d $(INSTALLDIR)/usr/sbin
	@install $(GOBI_UTIL) $(INSTALLDIR)/usr/sbin/gobi
	@$(STRIP) $(INSTALLDIR)/usr/sbin/gobi
	@install src/gobi_api $(INSTALLDIR)/usr/sbin/gobi_api
	@$(STRIP) $(INSTALLDIR)/usr/sbin/gobi_api
#	@cp -rf usr $(INSTALLDIR)/
	@install -d $(INSTALLDIR)/lib
	@install src/lib/libGobiConnectionMgmt.00.00.02.so $(INSTALLDIR)/lib/
	@cd $(INSTALLDIR)/lib/ && ln -s libGobiConnectionMgmt.00.00.02.so libGobiConnectionMgmt.so
	@install -D $(CROSS_TOOLCHAIN_DIR)/lib/librt-$(LIBRT_VERSION).so $(INSTALLDIR)/lib/librt-$(LIBRT_VERSION).so
	@cd $(INSTALLDIR)/lib && ln -sf librt-$(LIBRT_VERSION).so librt.so.0
	@install src/lib/libstdc++.so.6.0.16 $(INSTALLDIR)/lib/
	@cd $(INSTALLDIR)/lib && ln -sf libstdc++.so.6.0.16 libstdc++.so.6
	@install -d $(NET_USB_GOBI)
	@install $(GOBI_KO) $(NET_USB_GOBI)


.PHONY: all clean install
.PHONY: $(GOBI_KO) $(GOBI_UTIL)

