Broadcom SoC models
===================

	To install the tools:
	    - copy the brcm/ directory to /opt
	    - add /opt/brcm/hndtools-mipsel-linux/bin to your path
	    - add /opt/brcm/hndtools-mipsel-uclibc/bin to your path

Mediatek/Ralink SoC models
==========================

	To install the tools:
	    - copy the brcm/ directory to /opt
	    - add /opt/brcm/hndtools-mipsel-linux/bin to your path
	    - add /opt/brcm/hndtools-mipsel-uclibc/bin to your path
	    - extract buildroot-gcc342.tar.bz2 to /opt
	    - add /opt/buildroot-gcc342/bin to your path

	For MT7621 Uboot:
	    - extract mips-2012.03.tar.bz2 directory to /opt
	    - add /opt/mips-2012.03/bin to your uboot path

Qualcomm SoC models
===================

	To install the tools:
	    - extract openwrt-gcc463.mips.tar.bz2 directory to /opt
	    - add /opt/openwrt-gcc463.mips/bin to your path
	    - If you want to build small utilities out of asuswrt box,
	      add STAGING_DIR environment variable as below:

	      export STAGING_DIR=/opt/openwrt-gcc463.mips

