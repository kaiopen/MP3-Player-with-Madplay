/*
 * 文件名：music_list.h
 * 说明：music结构体定义，为循环双向链表
 * 相关文件：music_list.c
 * 作者：张开
 * 日期：2017.5.12
 *
 */

#ifndef MUSIC_LIST_H
#define MUSIC_LIST_H

typedef struct node
{
    char *name;
    // char *singer;
    // int size;
    struct node *next;
    struct node *prev;
}music;

typedef struct musicLst
{
    int length;
    music *mHead;
}music_list;

music_list * createMusicList();
int musicListInsert(music_list *mList, char *name);
int musicListDisplay(music_list *mList);
int musicListDelete(music_list *mList, char *name);
int musicFind(music_list *mList, char *name);
music * locateMusic(music_list *mList, int pos);

#endif
