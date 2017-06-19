/*
 * 文件名：madplay.h
 * 源文件：madplay.c
 * 作者：张开
 * 日期：2017.5.12
 */

#ifndef MADPLAY_H
#define MADPLAY_H

int play(char *name);
int suspend(pid_t pid);
int continuePlay(pid_t pid);
int end(pid_t pid);

#endif
