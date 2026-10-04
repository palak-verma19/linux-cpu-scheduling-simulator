# Linux CPU Scheduler Character Device Driver

## Overview

This directory contains a Linux kernel character-device driver developed as a supporting component for the CPU Scheduling Simulator.

The driver demonstrates Linux Device Driver concepts and provides a simple communication interface between user space and kernel space.

## Architecture

```text
+-----------------------------+
| CPU Scheduling Simulator    |
|        User Space           |
+-------------+---------------+
              |
              | read / write
              v
+-----------------------------+
| /dev/cpu_scheduler          |
| Character Device            |
+-------------+---------------+
              |
              v
+-----------------------------+
| CPU Scheduler Kernel Module |
|        Kernel Space         |
+-----------------------------+

#Device Driver Concepts Demonstrated

The driver implements:

Linux Kernel Module
Character Device
Device number allocation
struct cdev
File operations
open()
read()
write()
release()
User-space to kernel-space communication
copy_to_user()
copy_from_user()
Device creation under /dev
Kernel logging using pr_info() and pr_err()

#Source File
cpu_scheduler_device.c

The source implements a character device named:
/dev/cpu_scheduler

#Building the Module

The driver requires Linux kernel build headers matching the running kernel.

Normally:
make
is sufficient when the following directory exists:

/lib/modules/$(uname -r)/build

The generated kernel module will be:

cpu_scheduler_device.ko

#Current WSL Environment

This project was developed and tested primarily using WSL2.

The current WSL kernel is:

6.6.87.2-microsoft-standard-WSL2

The matching kernel build directory is not available in the current environment:

/lib/modules/6.6.87.2-microsoft-standard-WSL2/build

Therefore, kernel-module compilation/loading is not performed in this WSL environment.

The driver source is nevertheless included as a genuine Linux kernel character-device implementation and can be compiled in a suitable Linux kernel development environment.

#Loading the Module

On a Linux system with matching kernel headers:

sudo insmod cpu_scheduler_device.ko

Check the kernel log:

dmesg | tail

The device should appear as:

/dev/cpu_scheduler

#Testing the Device

Write data to the device:

echo "CPU Scheduler Test" | sudo tee /dev/cpu_scheduler

Read data:

sudo cat /dev/cpu_scheduler

Check the device:

ls -l /dev/cpu_scheduler

#Removing the Module
sudo rmmod cpu_scheduler_device
#Cleaning Build Files
make clean

#Important Note

The CPU scheduling simulator itself is completely usable without loading this kernel module.

The driver is included to demonstrate Linux Device Driver and kernel/user-space architecture concepts required by the capstone specification.


Then **save the file**:

**Ctrl + O → Enter → Ctrl + X**

After you return to the normal `$` prompt, run:

```bash
wc -l linux_driver/README.md
