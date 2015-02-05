/******************************************************************
*
*	CyberIO for C
*
*	Copyright (C) Satoshi Konno 2005
*
*       Copyright (C) 2006 Nokia Corporation. All rights reserved.
*
*       This is licensed under BSD-style license,
*       see file COPYING.
*
*	File: cfile.c
*
*	Revision:
*
*	01/25/05
*		- first revision
*	03/19/06 Theo Beisch
*		- WINCE support (still untested)
*	07/18/07
*		- Added the following functions.
*		  mupnp_file_open()
*		  mupnp_file_close()
*		  mupnp_file_write()
*		  mupnp_file_read()
*		  mupnp_file_seek() ]
*  08/19/07
*		- Added the following functions.
*		  mupnp_file_setpath()
*		  mupnp_file_setfilename()
*
******************************************************************/

#include <mupnp/io/file.h>

#if defined(CG_USE_CFILE)

#include <mupnp/util/log.h>
#include <stdio.h>

#if defined(WIN32) && !defined(WINCE)
#include <windows.h>
#include <sys/stat.h>
#elif defined (WINCE)
#include <windows.h>

/*
#if (_WIN32_WCE < 0x501)
#include <sys\types.h> //from PortSDK
#endif

struct stat {

        _dev_t st_dev;
        _ino_t st_ino;
        unsigned short st_mode;
        short st_nlink;
        short st_uid;
        short st_gid;
        _dev_t st_rdev;
        _off_t st_size;
        time_t st_atime;
        time_t st_mtime;
        time_t st_ctime;
        };
*/

#elif defined(BTRON) || defined(ITRON) || defined(TENGINE)
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dirent.h>
#include <bsys/unixemu.h>
#else
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif

/****************************************
* mupnp_file_new
****************************************/

CgFile *mupnp_file_new()
{
	CgFile *file;

	mupnp_log_debug_l4("Entering...\n");
	
	file = (CgFile *)malloc(sizeof(CgFile));

	if ( NULL != file )
	{
		mupnp_list_node_init((CgList *)file);
		file->name = mupnp_string_new();
		file->path = mupnp_string_new();
		file->content = NULL;
		file->fp = NULL;
	}

	mupnp_log_debug_l4("Leaving...\n");

	return file;
}

/****************************************
* mupnp_file_delete
****************************************/

void mupnp_file_delete(CgFile *file)
{
	mupnp_log_debug_l4("Entering...\n");

	mupnp_list_remove((CgList *)file);

	mupnp_string_delete(file->name);
	mupnp_string_delete(file->path);
	if (file->content != NULL)
		free(file->content);
	free(file);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_setname
****************************************/

void mupnp_file_setname(CgFile *file, char *name)
{
	mupnp_log_debug_l4("Entering...\n");

	mupnp_string_setvalue(file->name, name);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_getname
****************************************/

char *mupnp_file_getname(CgFile *file)
{
	mupnp_log_debug_l4("Entering...\n");

	return mupnp_string_getvalue(file->name);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_getname
****************************************/

long mupnp_file_getlastmodified(CgFile *file)
{
	char *fileName;
#if !defined (WINCE)
	struct stat buf ;
#endif

	mupnp_log_debug_l4("Entering...\n");

#if !defined (WINCE)
	buf.st_mtime = 0;
#endif

	fileName = mupnp_file_getname(file);
#if defined(BTRON) || defined(ITRON) || defined(TENGINE) 
	if(u_stat(fileName, &buf ) == -1)
		return 0;
	return buf.st_mtime;
#elif defined (WINCE)
	#pragma message ("Not Implemented yet")
	#pragma message ("WINCE - support for file I/O not provided by CSTL - fixmelater")
	return 0;
#else
	if(stat(fileName, &buf ) == -1)
		return 0;
	return buf.st_mtime;
#endif

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_getname
****************************************/

long mupnp_file_getlength(CgFile *file)
{
	char *fileName;
#if !defined (WINCE)
	struct stat buf ;
#endif

	mupnp_log_debug_l4("Entering...\n");

	fileName = mupnp_file_getname(file);
#if defined(BTRON) || defined(ITRON) || defined(TENGINE) 
	if(u_stat(fileName, &buf ) == -1)
		return 0;
#elif defined (WINCE)
	#pragma message ("Not Implemented yet")
	#pragma message ("WIN32_WCE - support for file I/O not provided by CSTL - fixmelater")
	return 0;
#else
	if(stat(fileName, &buf ) == -1)
		return 0;
#endif
	
	mupnp_log_debug_l4("Leaving...\n");

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) && !defined (WINCE)
	return buf.st_size;
#endif
}

/****************************************
* mupnp_file_exists
****************************************/

BOOL mupnp_file_exists(CgFile *file)
{
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	FILE *fp;
#else
	int fd;
#endif
	char *fileName;
	
	mupnp_log_debug_l4("Entering...\n");

	fileName = mupnp_file_getname(file);
	
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	fp = fopen(fileName, "r");
	if (fp == NULL)
		return FALSE;
	fclose(fp);
	return TRUE;
#else
	fd = open(fileName, O_RDONLY);
	if (fd == -1)
		return FALSE;
	close(fd);
	return TRUE;
#endif

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_remove
****************************************/

BOOL mupnp_file_remove(CgFile *file)
{
	char *fileName;
	int removeSuccess = 0;
	
	mupnp_log_debug_l4("Entering...\n");

	fileName = mupnp_file_getname(file);
#if defined(WINCE)
	#pragma message("############################## FIXMELATER cfile.c - Verify File removal (untested on CE)")
	removeSuccess = DeleteFile((void*)fileName);
#else
	removeSuccess = remove(fileName);
#endif
	
	return (removeSuccess == 0) ? TRUE : FALSE;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_setcontent
****************************************/

void mupnp_file_setcontent(CgFile *file, char *content)
{
	mupnp_log_debug_l4("Entering...\n");

	if (file->content != NULL) {
		free(file->content);
		file->content = NULL;
	}
	file->content = mupnp_strdup(content);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_getcontent
****************************************/

char *mupnp_file_getcontent(CgFile *file)
{
	mupnp_log_debug_l4("Entering...\n");

	return file->content;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_getfilename
****************************************/

char *mupnp_file_getfilename(CgFile *file)
{
	char *fileName;
	int sepIdx;

	mupnp_log_debug_l4("Entering...\n");

	fileName = mupnp_file_getname(file);	
	sepIdx = mupnp_strrchr(fileName, CG_FILE_SEPARATOR, 1);
	if (0 < sepIdx)
		return (fileName + sepIdx + 1);
	return NULL;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_getpath
****************************************/

char *mupnp_file_getpath(CgFile *file)
{
	char *path;
	char *fileName;
	int sepIdx;

	mupnp_log_debug_l4("Entering...\n");

	path = mupnp_string_getvalue(file->path);
	if (path != NULL)
		return path;
		
	fileName = mupnp_file_getname(file);	
	sepIdx = mupnp_strrchr(fileName, CG_FILE_SEPARATOR, 1);
	
	if (0 < sepIdx) {
		path = (char *)malloc(sizeof(char)*(sepIdx+1));

		if  ( NULL == path )
		{
			mupnp_log_debug_s("Memory allocation failure!\n");
			return NULL;
		}
		
		mupnp_strncpy(path, fileName, sepIdx);
		path[sepIdx]='\0';
		mupnp_string_setpointervalue(file->path, path, mupnp_strlen(path));
	}
	
	return mupnp_string_getvalue(file->path);

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_load
****************************************/

BOOL mupnp_file_load(CgFile *file)
{
#if defined(WIN32) || defined(HAVE_FOPEN)
	FILE *fp;
	size_t nRead;
	size_t readCnt;
#else
	int fd;
	ssize_t nRead;
	ssize_t readCnt;
#endif
	char *fileName;
	long fileLen;
	
	mupnp_log_debug_l4("Entering...\n");

	if ( NULL == file )
		return FALSE;
	
	if (file->content != NULL) {
		free(file->content);
		file->content = NULL;
	}
	
	fileLen = mupnp_file_getlength(file);
	if (fileLen <= 0)
		return FALSE;
		
	fileName = mupnp_file_getname(file);
	file->content = (char *)malloc(fileLen + 1);		

	if ( NULL == file->content )
	{
		mupnp_log_debug("Memory allocation failure!\n");
		return FALSE;
	}
	
#if defined(WIN32) || defined(HAVE_FOPEN)
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		file->content[0] = '\0';
		return FALSE;
	}
	readCnt = 0;
	do {
		int remaining  = fileLen - readCnt;
		int chunkSize = remaining < CG_FILE_READ_CHUNK_SIZE ? remaining : CG_FILE_READ_CHUNK_SIZE;
		nRead = fread((file->content)+readCnt, sizeof(char), chunkSize, fp);
		readCnt += nRead;
	} while (0 < nRead);
	fclose(fp);
#else
	fd = open(fileName, O_RDONLY);
	if (fd == -1) {
		file->content[0] = '\0';
		return FALSE;
	}
	readCnt = 0;
	nRead = read(fd, (file->content)+readCnt, CG_FILE_READ_CHUNK_SIZE);
	while (0 < nRead) {
		readCnt += nRead;
		nRead = read(fd, (file->content)+readCnt, CG_FILE_READ_CHUNK_SIZE);
	}
	close(fd);
#endif

	file->content[readCnt] = '\0';
	
	return TRUE;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_save
****************************************/

BOOL mupnp_file_save(CgFile *file)
{
#if defined(WIN32) || defined(HAVE_FOPEN)
	FILE *fp;
	size_t nWrite;
	size_t writeCnt;
	size_t contentLen;
#else
	int fd;
	ssize_t nWrite;
	ssize_t writeCnt;
	ssize_t contentLen;
#endif
	char *fileName;
	
	mupnp_log_debug_l4("Entering...\n");

	fileName = mupnp_file_getname(file);
	if (fileName == NULL)
		return FALSE;
		
	if (file->content == NULL)
		return FALSE;
	
	contentLen = mupnp_strlen(file->content);
	if (contentLen <= 0)
		return FALSE;
	
#if defined(WIN32) || defined(HAVE_FOPEN)
	fp = fopen(fileName, "w");
	if (fp == NULL)
		return FALSE;
	writeCnt = 0;
	nWrite = fwrite((file->content)+writeCnt, sizeof(char), contentLen-writeCnt, fp);
	while (0 < nWrite) {
		writeCnt += nWrite;
		if (contentLen <= writeCnt)
			break;		
		nWrite = fwrite((file->content)+writeCnt, sizeof(char), contentLen-writeCnt, fp);
	}
	fclose(fp);
#else
	fd = open(fileName, O_WRONLY);
	if (fd == -1)
		return FALSE;
	writeCnt = 0;
	nWrite = write(fd, (file->content)+writeCnt, contentLen-writeCnt);
	while (0 < nWrite) {
		writeCnt += nWrite;
		if (contentLen <= writeCnt)
			break;		
		nWrite = write(fd, (file->content)+writeCnt, contentLen-writeCnt);
	}
	close(fd);
#endif

	return TRUE;

	mupnp_log_debug_l4("Leaving...\n");
}

/****************************************
* mupnp_file_listfiles
****************************************/

int mupnp_file_listfiles(CgFile *file, CgFileList *fileList)
{
	char *dir;
	char *fileName;
	CgString *fullPathStr;
	CgFile *childFile;
#if defined(WIN32)
	CgString *findDirStr;
	#if defined(UNICODE)
	TCHAR wCharBuf[MAX_PATH];
	char mCharBuf[MAX_PATH];
	#endif
	WIN32_FIND_DATA fd;
	HANDLE hFind;
#else
	struct dirent **dirFileList;
	int n;
#endif

	dir = mupnp_file_getname(file);
	if (mupnp_strlen(dir) <= 0)
		return 0;

#if defined(WIN32)
	findDirStr = mupnp_string_new();
	mupnp_string_addvalue(findDirStr, dir);
	mupnp_string_addvalue(findDirStr, "\\*.*");
	#if defined(UNICODE)
	MultiByteToWideChar(CP_UTF8, 0, mupnp_string_getvalue(findDirStr), -1, wCharBuf, (MAX_PATH-1));
	hFind = FindFirstFile(wCharBuf, &fd);
	#else
	hFind = FindFirstFile(mupnp_string_getvalue(findDirStr), &fd);
	#endif
	if (hFind != INVALID_HANDLE_VALUE) {
		do{
			#if defined(UNICODE)
			WideCharToMultiByte(CP_ACP, 0, fd.cFileName, -1, mCharBuf, (MAX_PATH-1), NULL, NULL);
			fileName = mupnp_strdup(mCharBuf);
			#else
			fileName = mupnp_strdup(fd.cFileName);
			#endif
			if (!mupnp_streq(".", fileName) && !mupnp_streq("..", fileName)) {
				fullPathStr = mupnp_string_new();
				mupnp_string_addvalue(fullPathStr, dir);
				mupnp_string_addvalue(fullPathStr, "\\");
				mupnp_string_addvalue(fullPathStr, fileName);
//				conType = (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? CG_UPNPAV_CONTENT_CONTAINER : CG_UPNPAV_CONTENT_ITEM;
#else
	n = scandir(dir, &dirFileList, 0, alphasort);
	if (0 <= n) {
		while(n--) {
			if (!mupnp_streq(".", dirFileList[n]->d_name) && !mupnp_streq("..", dirFileList[n]->d_name)) {
				fileName = mupnp_strdup(dirFileList[n]->d_name);
				fullPathStr = mupnp_string_new();
				mupnp_string_addvalue(fullPathStr, dir);
				mupnp_string_addvalue(fullPathStr, "/");
				mupnp_string_addvalue(fullPathStr, dirFileList[n]->d_name);
//				if(stat(mupnp_string_getvalue(fullPathStr), &fileStat) != -1)
//				conType = ((fileStat.st_mode & S_IFMT)==S_IFDIR) ? CG_UPNPAV_CONTENT_CONTAINER : CG_UPNPAV_CONTENT_ITEM;
#endif
				/* file */
				childFile = mupnp_file_new();
				if (!childFile)
					continue;

				/* title */
				mupnp_file_setname(childFile, fileName);

				mupnp_filelist_add(fileList, childFile);

				free(fileName);
				mupnp_string_delete(fullPathStr);
				
#if defined(WIN32)
			}
		} while(FindNextFile(hFind,&fd) != FALSE);
		FindClose(hFind);
	}
	mupnp_string_delete(findDirStr);
#else
			}
			free(dirFileList[n]);
		}
		free(dirFileList);
	}
#endif

	return mupnp_filelist_size(fileList);
}

/****************************************
* mupnp_file_listfiles
****************************************/

BOOL mupnp_file_open(CgFile *file, int mode)
{
	char *filename;
	char *stdioMode;

	filename = mupnp_file_getname(file);
	if (mupnp_strlen(filename) <= 0)
		return FALSE;

	stdioMode = "";
	if (mode & CG_FILE_OPEN_WRITE) {
		if (mode & CG_FILE_OPEN_CREATE)
			stdioMode = "w+b";
		else
			stdioMode = "r+b";
	}
	else if (mode & CG_FILE_OPEN_READ)
		stdioMode = "rb";

	file->fp = fopen(filename, stdioMode);
	
	return (file->fp) ? TRUE : FALSE;
}

/****************************************
* mupnp_file_listfiles
****************************************/

BOOL mupnp_file_close(CgFile *file)
{
	if (!file->fp)
		return FALSE;

	if (fclose(file->fp) == 0) {
		file->fp = NULL;
		return TRUE;
	}

	return FALSE;
}

/****************************************
* mupnp_file_listfiles
****************************************/

BOOL mupnp_file_write(CgFile *file, CgByte *buf, int bufLen)
{
	if (!file->fp)
		return FALSE;

	return (fwrite(buf, 1, bufLen, file->fp) == bufLen) ? TRUE : FALSE;
}

/****************************************
* mupnp_file_listfiles
****************************************/

BOOL mupnp_file_read(CgFile *file, CgByte *buf, int bufLen)
{
	if (!file->fp)
		return FALSE;

	return (fread(buf, 1, bufLen, file->fp) == bufLen) ? TRUE : FALSE;
}

/****************************************
* mupnp_file_listfiles
****************************************/

BOOL mupnp_file_seek(CgFile *file, CgInt64 offset, int whence)
{
	int stdioWhence;

	if (!file->fp)
		return FALSE;

	switch (whence) {
	case CG_FILE_SEEK_SET:
		stdioWhence = SEEK_SET;
		break;
	case CG_FILE_SEEK_CUR:
		stdioWhence = SEEK_CUR;
		break;
	case CG_FILE_SEEK_END:
		stdioWhence = SEEK_END;
		break;
	default:
		stdioWhence = 0;
	}

	return (fseek(file->fp, (long)offset, stdioWhence) == 0) ? TRUE : FALSE;
}

/****************************************
* mupnp_file_setfilename
****************************************/

void mupnp_file_setfilename(CgFile *file, char *name)
{
	int nameLen;
	char *pathName;
	int pathNameLen;

	nameLen = mupnp_strlen(name);
	if (nameLen <= 0)
		return;

	pathName = mupnp_file_getname(file);
	pathNameLen = mupnp_strlen(pathName); 
	if (pathNameLen <= 0) {
		mupnp_file_setname(file, name);
		return;
	}

	if (pathName[pathNameLen-1] != CG_FILE_SEPARATOR_CHAR) {
		if (name[nameLen-1] != CG_FILE_SEPARATOR_CHAR)
			mupnp_string_addvalue(file->name, CG_FILE_SEPARATOR);
	}

	mupnp_string_addvalue(file->name, name);
}

#endif