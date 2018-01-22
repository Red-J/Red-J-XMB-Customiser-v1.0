#include <fcntl.h>
#include <ppu-lv2.h>
#include <sys/file.h>
#include <stdio.h>
#include <string.h>
#include "COPY.H"

#define SUCCESS 0
#define FAILED -1

#define SC_SYS_POWER 					(379)
#define SYS_REBOOT				 		0x8201

 ////////////////////////////////////////////
 //Paramètres système de copie de fichiers //
////////////////////////////////////////////

int CopyFile(const char* path, const char* path2)
{
	int ret = 0;
	s32 fd = -1;
	s32 fd2 = -1;
	u64 lenght = 0LL;

	u64 pos = 0ULL;
	u64 readed = 0, writed = 0;

	char *mem = NULL;

	sysFSStat stat;

	ret= sysLv2FsStat(path, &stat);
	lenght = stat.st_size;

	if(ret) goto skip;

	if(strstr(path, "/dev_hdd0/") != NULL && strstr(path2, "/dev_hdd0/") != NULL)
	{
		if(strcmp(path, path2)==0) return ret;

		sysLv2FsUnlink(path2);
		sysLv2FsLink(path, path2);

		if (sysLv2FsStat(path2, &stat) == 0) return 0;
	}

	ret = sysLv2FsOpen(path, 0, &fd, S_IRWXU | S_IRWXG | S_IRWXO, NULL, 0);
	if(ret) goto skip;

	ret = sysLv2FsOpen(path2, SYS_O_WRONLY | SYS_O_CREAT | SYS_O_TRUNC, &fd2, 0777, NULL, 0);
	if(ret) {sysLv2FsClose(fd);goto skip;}

	mem = malloc(0x100000);
	if (mem == NULL) return FAILED;

	while(pos < lenght)
	{
		readed = lenght - pos; if(readed > 0x100000ULL) readed = 0x100000ULL;
		ret=sysLv2FsRead(fd, mem, readed, &writed);
		if(ret<0) goto skip;
		if(readed != writed) {ret = 0x8001000C; goto skip;}

		ret=sysLv2FsWrite(fd2, mem, readed, &writed);
		if(ret<0) goto skip;
		if(readed != writed) {ret = 0x8001000C; goto skip;}

		pos += readed;
	}
  ////////////////////////////////////////////
 //            Vidage de la mémoire        //
////////////////////////////////////////////

skip:

	if(mem) free(mem);
	if(fd >=0) sysLv2FsClose(fd);
	if(fd2>=0) sysLv2FsClose(fd2);
	if(ret) return ret;

	ret = sysLv2FsStat(path2, &stat);
	if((ret == SUCCESS) && (stat.st_size == lenght)) ret = SUCCESS; else ret = FAILED;

	return ret;
}