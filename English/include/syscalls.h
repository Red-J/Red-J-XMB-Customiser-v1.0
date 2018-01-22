#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__
#include <ppu-lv2.h>
#include <lv2/sysfs.h>
#include <string.>
#include <stdio.h>

using namespace std;

s32 sysFsMount(const char* MOUNT_POINT, const char* TYPE_OF_FILESYSTEM, const char* PATH_TO_MOUNT, int IF_READ_ONLY);
s32 sysFsUnmount(const char* PATH_TO_UNMOUNT);
int is_dev_blind_mounted();
int mount_dev_blind();
int unmount_dev_blind();


#endif // __SYSCALLS_H__
