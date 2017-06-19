/*
 * 文件名：music_list.c
 * 头文件：music_list.h
 * 说明：music结构体双向循环链表的具体实现
 * 作者：张开
 * 日期：2017.5.12
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music_list.h"

int bSearch(int funcFlag, music_list *mList, char *value, int low, int high);


/*
int main()
{
    music_list *mList;
    mList = createMusicList();
    char *name = "abcd";
    musicListInsert(mList, name);
    musicListDisplay(mList);
    return 0;
}
*/

music_list * createMusicList()
{
    music_list *mList;
    mList = (music_list *)malloc(sizeof(music_list));
    if(NULL == mList)
    {
        perror("mList malloc fail\n");
        exit(1);
    }
    mList->length = 0;
    mList->mHead = NULL;

    return mList;
}

int musicListInsert(music_list *mList, char *name)
{
    music *mNew;
    mNew = (music *)malloc(sizeof(music));
    if(NULL == mNew)
    {
        perror("mNew malloc fail\n");
        exit(1);
    }
    mNew->name = name;

    if(NULL == mList->mHead) // 初始节点
    {
        mNew->next = mNew;
        mNew->prev = mNew;
        mList->mHead = mNew;
#ifdef MUSIC_LIST_DEBUG    
        printf("init next: %s\n", mList->mHead->next->name);
        printf("init prev: %s\n", mList->mHead->prev->name);
#endif
    }
    else
    {
        int pos = bSearch(0, mList, name, 0, mList->length - 1); // 得到插入位置
#ifdef MUSIC_LIST_DEBUG
        printf("bsearch success\n");
        printf("pos: %d\n", pos);
#endif

        music *tmp; // tmp指向pos位置的节点
        tmp = locateMusic(mList, pos);

        mNew->next = (tmp);
        mNew->prev = (tmp)->prev;
#ifdef MUSIC_LIST_DEBUG
        printf("mNew->next: %s\n", mNew->next->name); 
        printf("mNew->prev: %s\n", mNew->prev->name);
#endif
        tmp->prev->next = mNew;
#ifdef MUSIC_LIST_DEBUG
        printf("(mList->mHead + pos)->prev->next: %s\n", (tmp)->prev->next->name);
#endif
        tmp->prev = mNew;
#ifdef MUSIC_LIST_DEBUG      
         printf("(mList->mHead + pos)->prev: %s\n", (tmp)->prev->name);
#endif

        if(0 == pos) // 插入在链表头
            mList->mHead = mNew;
    }

    (mList->length)++;
    
    return 0;
}

int bSearch(int funcFlag, music_list *mList, char *value, int low, int high)
{   
    // funcFlag = 0: musicListInsert
    // funcFlag = 1: musicFind or musicListDelete

    int mid = (low + high) / 2;
    music *tmp; // tmp指向mid节点
    tmp = locateMusic(mList, mid);
    // printf("low: %d, high: %d, mid: %d\n", low, high, mid);
    if(0 == funcFlag)
    {
        if(high - low <= 1) // a[low]为比value小的最大值，a[high]为比value大的最小值
            return high;
    }
    if(1 == funcFlag) // musicFind
    {
        //printf("value:%s, tmp->name: %s",value, tmp->name);
        if(strcmp(value, tmp->name) == 0)
            return mid; // 文件存在，返回所在链表位置
        if((high - low) <= 0)
            return -1; // 文件不存
    }
    
    int r = strcmp(value, tmp->name);
    if(r < 0)   
        return bSearch(funcFlag, mList, value, low, mid);
    if(r > 0)
        return bSearch(funcFlag, mList, value, mid, high);
}

int musicListDisplay(music_list *mList)
{
    music *tmp;
    tmp = mList->mHead;
    printf("%s\n", tmp->name);
    int i;
    for(i = 1; i < mList->length; ++i)
    {
        tmp = tmp->next;
        printf("%s\n", tmp->name);
    }
    printf("\n\n");
    return 0;
}

/* 存在返回所在链表位置，不存在返回-1 */
int musicFind(music_list *mList, char *name)
{
    return bSearch(1, mList, name, 0, mList->length - 1);
}

/* 将tmp指向mList第pos位置 */
music *  locateMusic(music_list *mList, int pos)
{
    music *tmp = mList->mHead;
    int i;
    for(i = 0; i < pos; ++i)
        tmp = tmp->next;
   
    return tmp;
}

