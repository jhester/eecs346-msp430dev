# EECS 346 MSP430 Overview and Setup Guide

This guide gives a brief overview of the Texas Instruments MSP430 and shows how to get simple programs running on the [MSP-EXP430G2 launchpad](http://www.ti.com/tool/MSP-EXP430G2), which is a combined programmer and breakout board for the MSP430

  - [MSP430 Overview](#msp430-overview)
  - [Development Environment (DevEnv) Setup](#development-environment--devenv--setup)
    * [OSX Specific Setup](#osx-specific-setup)
    * [Linux Specific Setup](#linux-specific-setup)
    * [Windows Specific Setup](#windows-specific-setup)
    * [Generic Setup](#generic-setup)
    * [Debugging](#debugging)
  - [Other Resources](#other-resources)


## MSP430 Overview
The Texas Instruments MSP430 family of ultra-low-power microcontrollers consists of several devices featuring different sets of peripherals targeted for various applications. The architecture, combined with five low-power modes, is optimized to achieve extended battery life in portable measurement applications. The device features a 16-bit RISC CPU, 16-bit registers, and constant generators. The digitally controlled oscillator (DCO) allows wake-up from low-power modes to active mode in less than 1 µs.

The [MSP430G2553](http://www.ti.com/product/msp430g2553) we are using has built-in 16-bit timers, up to 24 I/O capacitive-touch enabled pins, a versatile analog comparator, and built-in communication capability using the universal serial communication interface. In addition the MSP430G2x53 family members have a 10-bit analog-to-digital (A/D) converter. Below is the pinout, the [MSP430 launchpad pinout can be found here.](http://energia.nu/wordpress/wp-content/uploads/2014/01/LaunchPads-MSP430G2-%E2%80%94-Pins-Maps-13-42.jpeg)

![MSp430 pinout](media/pinout.jpeg)

The MSP430 incorporates a 16-bit RISC CPU, peripherals, and a flexible clock system that interconnect using a von-Neumann common memory address bus (MAB) and memory data bus (MDB). Partnering a modern CPU with modular memory-mapped analog and digital peripherals, 

Key features of the MSP430x2xx family include:

- Ultralow-power architecture extends battery life
- 0.1 μA RAM retention
- 0.8 μ A real-time clock mode
- 250 μA/MIPS active
- High-performance analog ideal for precision measurement
- Comparator-gated timers for measuring resistive elements
- 16-bit RISC CPU enables new applications at a fraction of the code size.
- Large register file eliminates working file bottleneck
- Compact core design reduces power consumption and cost
- Optimized for modern high-level programming
- Only 27 core instructions and seven addressing modes
- Extensive vectored-interrupt capability
- In-system programmable Flash permits flexible code changes, field upgrades and data logging

The block diagram is shown below.

![MSp430 arch](media/func_diagram.jpeg)


The MSP430 von-Neumann architecture has one address space shared with special function registers (SFRs), peripherals, RAM, and Flash/ROM memory as shown in Figure 1-2. See the device-specific data sheets for specific memory maps. Code access are always performed on even addresses. Data can be accessed as bytes or words.

<p align="center">
<img align="center" src="media/adress_map.jpeg" alt="drawing" style="width: 300px;"/>
</p>


## Development Environment (DevEnv) Setup

You will need to setup the development environment and toolchain for MSP430s. First you need to setup the compiler so that you can write C-code that can be compiled and run on an MSP430. Then you will need to setup the interface for the programmer (mspdebug) to load binary files onto your MSP430 device. Some of these steps are platform dependant.  

### OSX Specific Setup

1. First make sure you have the Command Line Tools for OSX, install them by opening Terminal if you do not, click through and agree to terms:

```
xcode-select --install
```

2. If you do not already have Homebrew, you should. Homebrew is a package manager for OSX, if you have done any development with OSX you probably have this. [If not install it.](https://brew.sh/)

3. Now install the libusb pacakges, open up Terminal, or iTerm 2 and type in the following:

	```
	brew install libusb libusb-compat libelf
	brew upgrade libusb libusb-compat
	```

4. [Now install the CDC drivers](https://github.com/energia/Energia/raw/gh-pages/files/MSP430LPCDC-1.0.3b.zip)

### Linux Specific Setup
1. Download the udev rules: [TI udev rules](http://energia.nu/files/71-ti-permissions.rules)

2. Open a terminal and execute the following command: sudo mv /71-ti-permissions.rules /etc/udev/rules.d/

3. If your Linux distribution supports the service command you can active the new rules with sudo service udev restart. If your Linux distribution does not support this command or if you are not able to upload to the LaunchPad with Energia, then restart your computer to activate the rules.

4. If your board is plugged in, unplug it and plug it back in. Not needed if you rebooted your computer.

### Windows Specific Setup 
1. You should use the Windows Subsystem for Linux (WSL). [Go through this process and use the Ubuntu distro.](https://docs.microsoft.com/en-us/windows/wsl/install-win10). 

2. Download the LaunchPad drivers for Windows: [LaunchPad CDC drivers zip file for Windows 32 and 64 bit](https://github.com/energia/Energia/raw/gh-pages/files/EZ430-UART.zip)

3. Unzip and double click DPinst.exe for Windows 32bit or DPinst64.exe for Windows 64 bit.

4. Follow the installer instructions (should be one click and done). For Windows 8 and 10 users you may need to disable your signed driver feature, [follow this guide.](https://learn.sparkfun.com/tutorials/disabling-driver-signature-on-windows-8)

### Generic Setup
After getting the platform specific stuff done in previous sections, now download and install the compiler and build the programmer software. This assumes you already have a terminal window open:

1. First, [Download and install the compiler (GCC) for your platform.](http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/latest/index_FDS.html). Use the full version; this requires you get an account and verify you wont use the compliler for bad things (whatever that means). For Mac make sure to right click open, then hold OPTION and open.

2. Build the Blink example using the included Makefile
	
	```
	> cd eecs346-msp430dev/examples/blink
	> make
	msp430-elf-gcc -I ~/ti/gcc/include -mmcu=msp430g2553 -O0 -g   -c -o main.o main.c
	msp430-elf-gcc -I ~/ti/gcc/include -mmcu=msp430g2553 -O0 -g -L ~/ti/gcc/include main.o -o main.out
	```
	
	Now you should see this when you look at the contents of blink folder:
	
	```
	> ls -lha
	drwxr-xr-x  6 jhester  staff   192B May  6 14:14 .
	drwxr-xr-x  3 jhester  staff    96B May  6 13:39 ..
	-rw-r--r--  1 jhester  staff   532B May  6 14:04 Makefile
	-rw-r--r--  1 jhester  staff   384B May  6 13:58 main.c
	-rw-r--r--  1 jhester  staff   6.2K May  6 14:14 main.o
	-rwxr-xr-x  1 jhester  staff    12K May  6 14:14 main.out
	```

3. Now grab this repository, in Terminal, in a directory where you want the repository to reside:
	
	```
	git clone git@github.com:jhester/eecs346-msp430dev.git
	```

6. Now lets build `mspdebug` which is the program we will use to flash programs onto the MSP430.

	```
	cd eecs346-msp430dev/mspdebug
	make
	sudo make install
	```
	Note that the last command requires your password and sudo access; this will install the MAN pages for mspdebug as well as put the binary in your path.

7. Now connnect your launchpad via USB to your computer and run mspdebug like below, you should see this output and get a prompt, now you are in the memory space of the MSP430.

	```
	> mspdebug rf2500                                                        
	MSPDebug version 0.25 - debugging tool for MSP430 MCUs
	Copyright (C) 2009-2017 Daniel Beer <dlbeer@gmail.com>
	This is free software; see the source for copying conditions.  There is NO
	warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	Chip info database from MSP430.dll v3.12.0.604 Copyright (C) 2013 TI, Inc.
	
	...
	
	Type "help <topic>" for more information.
	Use the "opt" command ("help opt") to set options.
	Press Ctrl+D to quit.
	
	(mspdebug) _
	```

8. Finally, use the Makefile in examples/blink to flash the Blink example onto your MSP430 Launchpad using mspdebug. You should see something like the following and your Launchpad should be blinking its Red LED:

	```
	> make install
	msp430-elf-gcc -I ~/ti/gcc/include -mmcu=msp430g2553 -O0 -g -L ~/ti/gcc/include main.o -o main.out
	mspdebug rf2500 "prog main.out"
	Device: MSP430G2xx3
	Erasing...
	Programming...
	Writing    2 bytes at fffe [section: __reset_vector]...
	Writing   12 bytes at c000 [section: .rodata2]...
	Writing  706 bytes at c00c [section: .text]...
	Writing    4 bytes at c2ce [section: .data]...
	Done, 724 bytes total
	```


### Debugging

(Optional) Step through the blink example using mspdebug.


## Other Resources

Liux, Makefiles, GCC, GDB