/*
 * 文件名：madplay.c
 * 头文件：madplay.h
 * 说明：实现madplay的控制，包括播放play、暂停suspend、开始start、下一首next、上一首previous
 * 作者：张开
 * 日期：2017.5.13
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "madplay.h"

#ifdef MADPLAY_DEBUG
int main()
{
    pid_t pid;
    char *name = "./music/happy.mp3";
    pid = play(name);
    printf("child pid: %d\n", pid);
    char con;

    printf("suspend?");
    scanf("%c", &con);
    getchar();
    printf("\n");
    if('y' == con)
        suspend(pid);
   
    printf("continue?");
    scanf("%c", &con);
    getchar();
    if('y' == con)
         continuePlay(pid);

    printf("end?");
    scanf("%c", &con);
    printf("\n");
    end(pid);
    return 0;
}
#endif

/* 成功则返回进程pid，失败则返回0 */
int play(char *name)
{
    pid_t pid;
    int status;
    if((pid = fork()) < 0)
    {
        perror("Fork error\n");
        return 0;
    }
    else if(0 == pid)
    {
        waitpid(getppid(), &status, 0); // 等待父进程结束
        execlp("madplay", "madplay","-q", name, (char*)0);
        return 0;
    }
    else
    {
        return pid;    
    }
}

int suspend(pid_t pid)
{
    kill(pid, SIGSTOP);
    return 0;
}

int continuePlay(pid_t pid)
{
    kill(pid, SIGCONT);
    return 0;
}

int end(pid_t pid)
{
    kill(pid, SIGINT);
    return 0;
}

