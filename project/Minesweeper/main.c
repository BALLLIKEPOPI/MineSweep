#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main()
{
    int dif,flag;//初始化困难度
    char mine[60][60];
    char disp[60][60];

    welcome(&dif);//将输入的dif返回main函数
    if(dif==3)//若输入为3，退出游戏
    {
        return 0;
    }
    else
    {
        dif_elect(&dif);//检验dif是否符合要求
    }
    game_Init(&dif,SET,disp);//初始化游戏界面
    DISP(&dif,disp);//输出游戏界面
    Start=clock();//设置时间开始
    game_Init(&dif,'0',mine);//初始化地雷数组
    MineSet(&dif,mine);//设置地雷
    Input_Check(&dif);//输入并检验
    if(dif==0)//若dif等于0则退出游戏
    {
        return 0;
    }
    while(1)//重复输入坐标并检查
    {
        flag=Find_Mine(&dif,mine,disp);//检查是否挖到雷并返回值（返回1则终止）
        if(flag==1)
        {
            return 0;
        }
        Input_Check(&dif);
        if(dif==0)
        {
            return 0;
        }
    }
    return 0;
}
