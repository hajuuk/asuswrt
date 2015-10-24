#
# Makefile for Broadcom BCM947XX boards
#
# Copyright (C) 2008, Broadcom Corporation
# All Rights Reserved.
# 
# THIS SOFTWARE IS OFFERED "AS IS", AND BROADCOM GRANTS NO WARRANTIES OF ANY
# KIND, EXPRESS OR IMPLIED, BY STATUTE, COMMUNICATION OR OTHERWISE. BROADCOM
# SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE.
#
# $Id: Makefile,v 1.55.2.5.6.1 2008/11/11 04:07:47 Exp $
#

# Standard options
CFG_MLONG64 := 0
CFG_LITTLE ?= 1
CFG_RELOC := 0
CFG_UNCACHED := 0
CFG_VAPI := 0 
CFG_BOARDNAME := "BCM947XX"
CFG_PCI ?= 0
CFG_ZLIB := 1
CFG_MINIMAL_SIZE := 1
CFG_CFLASH := 1
CFG_XIP := 0
CFG_ATE := 0

# BCM947XX options
CFG_BCMHND74K ?= 0
CFG_EMBEDDED_NVRAM := 1
CFG_FLASH := 1   # if CFG_XIP is set then CFG_FLASH must be set to 0
CFG_SFLASH := 1
CFG_NFLASH := 0
CFG_ET := 1
CFG_GMAC ?= 1	# CFG_GMAC requires CFG_ET
CFG_WL := 0
CFG_WLU := 0
CFG_SIM := 0	# build for Quickturn/Simulator
CFG_SIM_CONSOLE := 0	# with console
ifeq ($(strip $(CFG_PCI)),1)
CFG_BCM57XX := 1
CFG_ET := 0
else
CFG_BCM57XX := 0
endif
# CFG_DUAL_IMAGE :=1	# Default to off in compile time

CFG_LZMA := 1

# Additional options
COMPRESSED_CFE := 1
RESCUE_MODE := 1
RTN12 := 0
RTN10 := 0
APAN23 := 0
GPV2 := 0
RTN16 := 0
RTN12P := 1

# HND source base
SRCBASE := $(shell cd ../../../.. && pwd)
TOP := $(SRCBASE)/cfe/cfe

ifeq ($(strip $(CFG_RELOC)),0)

# Link binary in RAM
CFG_BOOTRAM := 1
ifeq ($(strip ${CFG_UNCACHED}),1)
  ifeq ($(strip $(CFG_XIP)),0)
    CFG_TEXT_START := 0xa0700000
  else
    CFG_DATA_START := 0xa0001000
  endif
else
  ifeq ($(strip $(CFG_XIP)),0)
    CFG_TEXT_START := 0x80700000
  else
    CFG_DATA_START := 0x80001000
  endif
endif
# To generating ATE traces
ifeq ($(strip $(CFG_ATE)),1)
CFLAGS += -DBCM_ATE
endif

ifeq ($(strip $(RESCUE_MODE)),1)
CFLAGS += -DRESCUE_MODE
endif

ifeq ($(strip $(COMPRESSED_CFE)),1)
CFLAGS += -DCOMPRESSED_CFE
endif

ifeq ($(strip $(RTN12)),1)
CFLAGS += -DRTN12 -DEZ_RESET
endif

ifeq ($(strip $(RTN10)),1)
CFLAGS += -DRTN10 -DEZ_RESET
endif

ifeq ($(strip $(APAN23)),1)
CFLAGS += -DAPAN23
endif

ifeq ($(strip $(GPV2)),1)
CFLAGS += -DGPV2
endif

ifeq ($(strip $(RTN16)),1)
CFLAGS += -DRTN16 -DEZ_RESET
endif

ifeq ($(strip $(RTN12P)),1)
CFLAGS += -DRTN12P -DEZ_RESET
endif

# Toolchain prefix 
ifeq ($(CFG_LITTLE), 1)
TOOLPREFIX := mipsel-linux-
else
TOOLPREFIX := mips-wrs-vxworks-
endif

#PATH := $(PATH):/projects/hnd/tools/linux/bin:/projects/hnd/tools/linux/hndtools-mips-wrs-vxworks-3.2.3/bin

CFLAGS += -Ulinux -pipe

# Disable 4710A0 compiler workarounds if any
check_gcc = $(shell if $(GCC) $(1) -c -o /dev/null -xc /dev/null > /dev/null 2>&1; then echo "$(1)"; else echo "$(2)";  fi)
CFLAGS += $(call check_gcc, -m4710a0kern, )

# Disable PIC
CFLAGS += -G 0 -mno-abicalls -fno-pic

# Discard unused sections if supported
CFLAGS += -ffunction-sections -fdata-sections
LDFLAGS += -static --gc-sections

else

# Locate data in RAM
CFG_BOOTRAM := 0
ifeq ($(strip ${CFG_UNCACHED}),1)
  CFG_DATA_START := 0xa0001000
else
  CFG_DATA_START := 0x80001000
endif

endif

ARCH := mips
CPU := bcmcore
BOARD := bcm947xx


# define WL_CONFFILE for arch/mips/board/bcm947xx/src/Makefile
ifeq ($(strip $(CFG_WL)),1)
WLCONFFILE ?= wlconfig_cfe_apsta
WLTUNEFILE ?= wltunable_cfe.h
WLCFGDIR   := $(SRCBASE)/wl/config
UPDATESH   := $(WLCFGDIR)/diffupdate.sh
endif

include $(TOP)/main/cfe.mk

#
# Main target for normal builds
#
ifneq ($(strip $(CFG_WL)),1)
ALL: cfe.bin
	$(MAKE)  -C compressed
ifeq ($(strip $(RTN10)),1)
	nvserial -i compressed/cfez.bin -o RTN10_boot_0.23.bin -s 45 RT-N10_boot_1.0_16.txt
endif
ifeq ($(strip $(RTN12)),1)
	nvserial -i compressed/cfez.bin -o RTN12_boot_0.22.bin -s 45 RT-N12_boot_1.0_16.txt
endif
ifeq ($(strip $(APAN23)),1)
	nvserial -i compressed/cfez.bin -o APAN23_boot_0.11.bin -s 45 AP-AN23_boot_1.0_64.txt
endif

ifeq ($(strip $(GPV2)),1)
	nvserial -i cfe.bin -o WL500GPV2_boot_0.11.bin -s 45 WL-500GPV2_boot_1.0_32.txt
endif
ifeq ($(strip $(RTN16)),1)
	nvserial -i cfe.bin -o RTN16_boot_0.72_128.bin -s 45 RT-N16_boot_1.2_128.txt
endif
ifeq ($(strip $(RTN12P)),1)
	nvserial -i compressed/cfez.bin -o RTN12P_boot_0.11.bin -s 45 RT-N12P_boot_1.0_16.txt
endif

else # CFG_WL = 1

CLEANOBJS += wlconf.h

ALL: version wlconf.h cfe.bin
	$(MAKE) -C compressed

wlconf.h: $(WLCFGDIR)/$(WLTUNEFILE) FORCE
	[ ! -f $@ ] || chmod +w $@
	@echo "check and update config file"
	cp $< wltemp
	$(UPDATESH) wltemp $@

FORCE:

endif


cfe1M.bin:	cfe.bin
	dd conv=sync if=cfe.bin of=cfe1M.bin bs=1M

CLEANOBJS += cfe1M.bin cfe.qt

CLEAN:
	$(MAKE) -C compressed clean

clean: CLEAN


.EXPORT_ALL_VARIABLES:

#
# Linker script
#

include $(TOP)/main/cfe_link.mk
