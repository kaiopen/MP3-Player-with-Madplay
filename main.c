#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "music_list.h"
#include "readFileList.h"
#include "madplay.h"

char getCommand(char *arg);
int execCommand(char command, char *arg, pid_t *pid, music_list *mList, int *pos, int *quit);

int sCommand(char *arg, pid_t *pid, music_list *mList, int *pos);
int uCommand(pid_t *pid, music_list *mList, int *pos); 
int cCommand(pid_t *pid);
int nCommand(pid_t *pid, music_list *mList, int *pos); 
int pCommand(pid_t *pid, music_list *mList, int *pos);
int qCommand(pid_t *pid, int *pos, int *quit);

int getMusicFileDir(char *basePath);
int getMusicDir(music_list *mList, char *name, int *pos, int nextLast);


int displayHelp();


int main()
{
    char command;              // 控制指令
    char arg[256];                 // 指令参数

    char musicFilePath[256];   // 音乐文件所在文件的路径

    music_list *mList;         // 音乐信息双向链表
    int *pos;             // 当前播放的音乐在链表中的位置
    pos = (int *)malloc(sizeof(int));
    *pos = -1;
    
    pid_t *pid;                // 音乐进程pid
    pid = (pid_t *)malloc(sizeof(pid_t));
    
    int *quit;
    quit = (int *)malloc(sizeof(int));
    *quit = 0;
    
    mList = createMusicList();          // 初始化音乐信息双向链表
    getMusicFileDir(musicFilePath);     // 获取音乐文件所在文件的路径
    
    readFileList(musicFilePath, mList); // 读取音乐信息并完成链表

    /* 主界面 */
    printf("*******************Welcome to MP3Player******************\n\n");
    printf("                      Version: 1.0.0\n\n");
    printf(" The player with Madplay can play files in form of MP3.\n");
    printf(" For more information and help, use help command (<h> \nor <H>).\n");
    printf("\n\n\n\n\n");

    while(0 == *quit)
    {
        command = getCommand(arg);         // 读指令
        execCommand(command, arg, pid, mList, pos, quit);  // 执行指令
    }
    return 0;
}

/* command */

/* 读取指令和参数 */
char getCommand(char *arg)
{
    char res = '0'; // 指令
    char input[256];
    printf("Input command: ");
    fgets(input, 256, stdin);
    input[strlen(input) - 1] = '\0';

    /* Trim */
    int i = 0;
    while(' ' == input[i]) // 去除前空格
        ++i;
    if('\0' != input[i]) // fget会在字符串尾加'\n'
        res = input[i];  // 获得第一各有效字符    

    if('s' == res || 'S' == res)
    {
	strcpy(arg, "\0");
        if(' ' != input[++i] || '\0' == input[i]) // 为非空格或无参数
            return 'E';
        ++i;
        strcat(arg, &input[i]);
        

    }
    else // 无参数指令，检测指令是否有错
    {
        while('\0' != input[++i])
        {
            if(' ' != input[i])
            {
                res = 'E';
                break;
            }
        }
    }

    return res;
}

/* 指令执行 */
int execCommand(char command, char *arg, pid_t *pid, music_list *mList, int *pos, int *quit)
{   
    switch(command)
    {
        /* 播放 */
        case 's':
        case 'S':
            if(sCommand(arg, pid, mList, pos) == -1)
            printf("ERROR: Fail to play!\n");
            break;
        
        /* 暂停 */
        case 'u':
        case 'U':
            if(uCommand(pid, mList, pos) == -1)
                printf("ERRPR: No music is playing!\n");
            break;

        case 'n':
        case 'N':
            nCommand(pid, mList, pos);
            break;

        case 'c':
        case 'C':
            cCommand(pid);
            break;

        case 'p':
        case 'P':
            pCommand(pid, mList, pos);
            break;

        /* 显示音乐列表 */
        case 'l':
        case 'L':
            musicListDisplay(mList);
            break;

        /* 显示“帮助” */
        case 'h':
        case 'H':
            displayHelp();
            break;

        /* 退出 */
        case 'q':
        case 'Q':
            qCommand(pid, pos, quit);
            break;

        default:
            printf("ERROR: Invalid command!\n");
    }  
    return 0;
}

/* 播放 */
int sCommand(char *arg, pid_t *pid, music_list *mList, int *pos)
{
    getMusicDir(mList, arg, pos, 0); // arg为音乐文件路径
    
    if(-1 == *pos) // 文件不存在
    {
        printf("ERROR: File not exist!\n");
        return -1;
    }
    else
    {
        *pid = play(arg);
        printf("Playing...\n");
        return 0;
    }
}

/* 暂停 */
int uCommand(pid_t *pid, music_list *mList, int *pos)
{
    if(-1 == *pos) // 无音乐播放
        return -1;
    else
    {
        suspend(*pid);
        return 0;
    }
}

/*  */
int cCommand(pid_t *pid)
{
    continuePlay(*pid);
    return 0;
}


/* 下一首 */
int nCommand(pid_t *pid, music_list *mList, int *pos)
{
    if(-1 != *pid)
        end(*pid);
    char name[256];
    getMusicDir(mList, name, pos, 1);
    *pid = play(name);
    printf("Playing...\n");

    return 0;
}

/* 上一首 */
int pCommand(pid_t *pid, music_list *mList, int *pos)
{
    if(-1 != *pos) // 结束未结束的播放
        end(*pid);
    char name[256];
    getMusicDir(mList, name, pos, 2);
    *pid = play(name);
    printf("Playing...\n");

    return 0;
}


/* 退出 */
int qCommand(pid_t *pid, int *pos, int *quit)
{
    if(-1 != *pos) // 结束未结束的播放
        end(*pid);

    *quit = 1;

    return 0;
}



/* display  */

int displayHelp()
{
    printf("You can use commands as follows to control the player.\n");
    
    printf("<s> or <S>: Followed by music's name as argument, \nplaying the music.\n");
    printf("<u> or <U>: Suspend current playing.\n");
    printf("<c> or <C>: Continue to play.\n");
    
    printf("<n> or <N>: The next one.\n");
    printf("<p> or <P>: The previous one.\n");

    printf("<l> or <L>: Show your music list.\n");
    printf("<q> or <Q>: Quit.\n\n\n"); 
    return 0;
}


/* file */

/* 获取音乐文件所在文件的路径 */
int getMusicFileDir(char *basePath)
{
    FILE *fstream;
    fstream = fopen(".music_config", "r"); // .music_config保存音乐文件所在文件的路径
                                           // 默认为./music
    while(fgets(basePath, 256, fstream) != NULL)
    {
        if('#' != basePath[0])             // #为注释
        {
            basePath[strlen(basePath) - 1] = '\0';
            break;
        }
    }
    
    fclose(fstream);
    return 0;
}

/* 获取音乐文件路径 */
int getMusicDir(music_list *mList, char *name, int *pos, int nextLast)
{
    if(0 == nextLast) // 由name指定的歌
    {   
        *pos = musicFind(mList, name); // 文件在链表中位置
        if(-1 == *pos) // 文件不存在
        return -1;
    }    
    else
    {
        music *tmp;
        tmp = locateMusic(mList, *pos); // 指向当前播放的歌曲

        if(1 == nextLast) // 下一首
        {
            strcpy(name, tmp->next->name);
            ++(*pos);
        }
        else // 上一首
        {
            strcpy(name, tmp->prev->name);
            --(*pos);
        }
    }
    char path[256] = "./music/";
    strcat(path, name);
    strcpy(name, path);

    return 0;
}

