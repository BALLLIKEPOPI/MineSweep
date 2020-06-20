#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "game.h"

//初始化欢迎界面，返回dif的值
void welcome(int *dif)
{
    char temp;

    printf("Welcome to minesweeper! Please elect your difficulty. \n\n");
    printf("Input the numbers below to choose your difficulty\n");
    printf("> 0--EASY\n> 1--MEDIUM\n> 2--DIFFICUL\n> 3--QUIT\n\n> ");
    scanf("%c",&temp);//输入难度
    getchar();//消除回车影响
    *dif=temp-48;
    printf("\n");
}

//选择难度
void dif_elect(int *dif)
{
    char temp;

    while((*dif!=0)&&(*dif!=1)&&(*dif!=2))//若输入不合法则重新输入
    {
        printf("\a\nWRONG INOUT! Please try again. \n\n");
        putchar('>');
        scanf("%c",&temp);//重新输入
        getchar();//消除回车影响
        *dif=temp-48;
        printf("\n");
    }
    if(*dif==0)//输入0则返回简单难度
    {
        *dif=EASY;
    }
    if(*dif==1)//输入1则返回中等难度
    {
        *dif=MEDIUM;
    }
    if(*dif==2)//输入2则返回困难难度
    {
        *dif=DIFFICUL;
    }
}

//游戏初始化
void game_Init(int *dif,char set,char disp[60][60])
{
    int i,j;

    for(i=0;i<60;i++)
    {
        for(j=0;j<60;j++)
        {
            disp[i][j]=set;//填满数组
        }
    }
}

//输出游戏界面
void DISP(int *dif,char disp[60][60])
{
    int i,j;

    system("cls");//清屏

    for(i=0;i<(3*(*dif)-8)/2+1;i++)//打印游戏开始标记
    {
        printf("=");
    }
    printf("GAME  ON");
    for(i=0;i<(3*(*dif)-8)/2+1;i++)
    {
        printf("=");
    }
    printf("\n\n  ");
    for(i=0;i<(*dif);i++)//打印列数
    {
        printf(" %2d",i+1);
    }
    printf("\n");

    for(i=1;i<=(*dif);i++)//打印初始面板
    {
        printf("%2d",i);//打印行数
        for(j=1;j<=(*dif);j++)
        {
            printf("  %c",disp[i][j]);
        }
            printf("\n");
    }
    printf("\n");
    for(i=0;i<3*(*dif)+2;i++)//打印分割线
    {
        printf("=");
    }
    printf("\n\n");
}

//设置地雷的位置
void MineSet(int *dif,char mine[60][60])
{
    int count=MINE_NUM,x,y;

    srand((unsigned)(time(NULL)));
    while(count)//地雷坐标取随机数
    {
        x=rand()%(*dif)+1;//从1~*dif随机取数
        y=rand()%(*dif)+1;
        if(mine[x][y]=='0')//若该坐标不为雷区则设置为雷区
        {
            mine[x][y]='1';
            count --;
        }
    }
}

//输入并检验
int Input_Check(int *dif)
{
    int flag=1;//flag为输入标志（1为错误，0为正确）

    End=clock();//设置时间截止
    printf("Time: %.2f s\n",TIME);
    printf("Please input the coordinate(input [0 0] to quit): ");
    scanf("%d %d",&x_y_In.x,&x_y_In.y);//输入坐标
    while(flag)//输入判断
    {
        if(x_y_In.x==0&&x_y_In.y==0)//若输入0,0则退出程序
        {
            *dif=0;
            return 0;
        }
        if(x_y_In.x<1||x_y_In.y>*dif||x_y_In.y<1||x_y_In.y>*dif)//超出范围则重新输入
        {
            printf("Wrong input! Please try again(input [0 0] to quit): ");
            scanf("%d %d",&x_y_In.x,&x_y_In.y);
            printf("\n");
        }
        else//输入正确置标志为0
        {
            flag=0;
        }
    }
    return 0;
}

//检查是否挖到雷
int Find_Mine(int *dif,char mine[60][60],char disp[60][60])
{
    int i,j,count;//count为该坐标周围的雷数
    static int flag=0;//flag为非雷区数

    while(disp[x_y_In.x][x_y_In.y]!=SET)//若该区域已被挖掘，要求重新输入
    {
        printf("Seems that you've already unearthed this area. Try again.\n");
        Input_Check(&(*dif));//重新输入
        if(dif==0)
        {
            return 0;
        }
    }
    if(mine[x_y_In.x][x_y_In.y]=='1')//若输入坐标为地雷所在坐标
    {
        for(i=0;i<*dif;i++)//显示所有地雷
        {
            for(j=0;j<*dif;j++)
            {
                if(mine[i][j]=='1')
                {
                    disp[i][j]=MINE;
                }
            }
        }
        DISP(&(*dif),disp);
        End=clock();//设置时间截止
        printf("Oops! You lose! \nTotal time: %.2f s\n",TIME);
        return 1;
    }
    else
    {
        count=mine[x_y_In.x-1][x_y_In.y]+mine[x_y_In.x-1][x_y_In.y-1]+mine[x_y_In.x][x_y_In.y-1]+\
        mine[x_y_In.x+1][x_y_In.y-1]+mine[x_y_In.x+1][x_y_In.y]+mine[x_y_In.x][x_y_In.y+1]\
        +mine[x_y_In.x+1][x_y_In.y+1]+mine[x_y_In.x-1][x_y_In.y+1]-8*'0';//计算该坐标周围的雷数

        disp[x_y_In.x][x_y_In.y]=count+48;//将雷数存入该坐标
        DISP(&(*dif),disp);
        flag ++;
    }
    if(flag==*dif* *dif-MINE_NUM)//所有雷均排完
    {
        End=clock();//设置时间截止
        printf("Congratulation! You win!\nTotal time: %.2f s",TIME);
        return 1;
    }
    return 0;
}
