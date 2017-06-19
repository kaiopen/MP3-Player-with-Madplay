/*
 * 文件名：readFileList.c
 * 头文件：readFileList.h
 * 说明：linux下读取目录并获得mp3文件，将文件信息存入mList
 * 作者：张开
 * 日期：2017.6.12
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "music_list.h"

// char *basePath = "/home/zhang/VM_CentOS_5/share/music";

int readFileList(const char *basePath, music_list *mList)
{
    DIR *dir;
    struct dirent *ptr;
    
    // char base[1000];
    /* 读取目录，将mp3文件的文件名存入.music_list */    
    if((dir = opendir(basePath)) == NULL)
    {
        perror("Open dir error.\n");
        exit(1);
    }

    while((ptr = readdir(dir)) != NULL)
    {
        if(8 == ptr->d_type) // 文件
        {
            int i = 0;
            int flag = 0;
            while('\0' != ptr->d_name[i])
            {
                if('.' == ptr->d_name[i])
                {
                    if(0 != flag)
                        flag = 0;
                    ++flag;
                }
                else if(1 == flag && 'm' == ptr->d_name[i])
                    ++flag;
                else if(2 == flag && 'p' == ptr->d_name[i])
                    ++flag;
                else if(3 == flag && '3' == ptr->d_name[i])
                {
                    if('\0' ==  ptr->d_name[i + 1]) // 是mp3文件
                    {
                        musicListInsert(mList, ptr->d_name);
                        break;
                    }
                    flag = 0;
                }
                else if(0 != flag)
                    flag = 0;
                ++i;
            }
        }

        /*
        else if(4 == ptr->d_type) // 目录
        {
            memset(base, '\0', sizeof(base));
            strcpy(base, basePath);
            strcat(base, "/");
            strcat(base, ptr->d_name);
            readFileList(base);
        }
        */
    }
    closedir(dir);
    return 0;
}

