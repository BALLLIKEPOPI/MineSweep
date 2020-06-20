#ifndef __GAME_H
#define __GAME_H

#include <time.h>

#define EASY 10//简易难度
#define MEDIUM 30//中等难度
#define DIFFICUL 50//困难难度
#define SET '+'//未发掘区图标
#define MINE '*'//雷区图标
#define MINE_NUM 3*(*dif)//某困难度下雷数
#define TIME (double)(End-Start)/CLOCKS_PER_SEC//游戏时间

struct x_y_In{
    int x;
    int y;
}x_y_In;//输入坐标结构体
clock_t Start,End;

void welcome(int *dif);
void dif_elect(int *dif);
void game_Init(int *dif,char set,char disp[60][60]);
void DISP(int *dif,char disp[60][60]);
void MineSet(int *dif,char mine[60][60]);
int Input_Check(int *dif);
int Find_Mine(int *dif,char mine[60][60],char disp[60][60]);


#endif // __GAME_H
