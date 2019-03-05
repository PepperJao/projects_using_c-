//#include "stdafx.h"
#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max 10000
#define NUM 10


//图的定义
typedef struct
{
    int vexnum;
    char vertex[NUM][20];
    int arc[NUM][NUM];
}MGraph;


//辅助数组中的元素定义
typedef struct
{
    int distance;
    int path[NUM];
}ArrayNode;

MGraph G;

void printVertex();
void CreateUDN();
void ShortestPath(int num);
void printShortestPath();
void output(int sight1,int sight2);
char menu();

char Menu() // 主菜单
{
	int c;
	int flag;
	do{
		flag=1;
		printf ("*****数字化校园*****\n");
		printf ("所有地点:\n");
		printf ("东门   艺术学院   体育学院   土木工程实验室   图书馆\n");
		printf ("第一教学楼B座   建筑与环境学院   计算机学院   实验大楼   文新学院楼区\n");
		printf ("1.查询地点\n");
		printf ("2.两个地点之间的最短距离\n");
		printf ("3.退出\n");
		printf ("请输入你的操作:\n");

		scanf("%d",&c);
		getchar();
		if(c==1||c==2||c==3)
			flag=0;
	}while(flag);
	return c+'0';
}


int main() // 主函数
{
	char ck;
	do
	{
		ck=Menu();
		switch(ck)
		{
		case'1':printVertex(); break;
		case'2':printShortestPath();break;
		case'3':exit(0);
		};
	}while(ck!='3');
	return 0;
}


void CreateUDN() // 创建图的函数
{
	int i,j;
	G.vexnum=10;

	strcpy(G.vertex[0],"东门");
	strcpy(G.vertex[1],"艺术学院");
	strcpy(G.vertex[2],"体育学院");
	strcpy(G.vertex[3],"土木工程实验室");
	strcpy(G.vertex[4],"图书馆");
	strcpy(G.vertex[5],"第一教学楼B座");
	strcpy(G.vertex[6],"建筑与环境学院");
	strcpy(G.vertex[7],"计算机学院");
	strcpy(G.vertex[8],"实验大楼");
	strcpy(G.vertex[9],"文新学院楼区");
	for(i=0;i<G.vexnum;++i)
	{
		for(j=0;j<G.vexnum;++j)
		{
			G.arc[i][j]=0;
		}
	}

	G.arc[0][1] =G.arc[1][0] =375;
	G.arc[0][2] =G.arc[2][0] =477;
	G.arc[3][1] =G.arc[1][3] =593;
	G.arc[1][4] =G.arc[4][1] =438;
	G.arc[2][5] =G.arc[5][2] =278;
	G.arc[5][8] =G.arc[8][5] =527;
	G.arc[3][6] =G.arc[6][3] =352;
	G.arc[7][3] =G.arc[7][3] =586;
	G.arc[6][9] =G.arc[9][6] =559;
	G.arc[7][9] =G.arc[9][7] =387;
	G.arc[8][9] =G.arc[9][8] =585;
	G.arc[4][7] =G.arc[7][4] =322;


}
void printVertex()
{
	char dd[30];
	printf("请输入您要查询地点的名称:\n");

	scanf("%s",dd);
	getchar();
	if(strcmp(dd,"东门")==0)
	{
		printf("名称:东门\n");
		printf("简介:四川大学东门\n");
	}else if(strcmp(dd,"艺术学院")==0)
	{
		printf("名称:艺术学院\n");
		printf("简介:四川大学艺术学院\n");
	}else if(strcmp(dd,"体育学院")==0)
	{
		printf("名称:体育学院\n");
		printf("简介:四川大学体育学院\n");
	}else if(strcmp(dd,"土木工程实验室")==0)
	{
		printf("名称:土木工程实验室\n");
		printf("简介:四川大学土木工程实验室\n");
	}else if(strcmp(dd,"图书馆")==0)
	{
		printf("名称:图书馆\n");
		printf("简介:四川大学图书馆\n");
	}else if(strcmp(dd,"第一教学楼B座")==0)
	{
		printf("名称:第一教学楼B座\n");
		printf("简介:四川大学第一教学楼B座\n");
	}else if(strcmp(dd,"建筑与环境学院")==0)
	{
		printf("名称:建筑与环境学院\n");
		printf("简介:四川大学建筑与环境学院\n");
	}else if(strcmp(dd,"计算机学院")==0)
	{
		printf("名称:计算机学院\n");
		printf("简介:四川大学计算机学院\n");
	}else if(strcmp(dd,"实验大楼")==0)
	{
		printf("名称:实验大楼\n");
		printf("简介:四川大学实验大楼\n");
	}else if(strcmp(dd,"文新学院楼区")==0)
	{
		printf("名称:文新学院楼区\n");
		printf("简介:四川大学文新学院楼区\n");
	}else
	{
		printf("输入错误\n");
	}
}

//迪杰斯特拉算法
void Dijkstra(int v0,int v1)
{
    int i,j,index=-1;
    int n=1;//记录已经求出的两个点之间的最短距离的个数
    ArrayNode shortestPath[NUM];
    int flag[NUM]={0};//标记，为1表示到这个顶点的最短距离已求出

    //1.求v0到各个顶点的直接距离，即初始化shortestPath数组
    for(i=0;i<G.vexnum;i++){
        if(v0==i){
            shortestPath[i].distance=0;
            shortestPath[i].path[0]=i;
            flag[v0]=1;
        }
        else if(G.arc[v0][i]>0){
			shortestPath[i].path[0]=v0;
			shortestPath[i].path[1]=i;
			shortestPath[i].distance=G.arc[v0][i];

        }else
            shortestPath[i].distance=Max;

    }
    //2.每次求一个最短路径
    while(n<G.vexnum){
        //选择shortestPath中距离最小的，求出v0到这个顶点的最短路径
        index=-1;
        for(i=0;i<G.vexnum;i++){
            if(i==v0)
                continue;
            if(flag[i]==0 && index==-1 && shortestPath[i].distance!=Max)
                index=i;
            if(flag[i]==0 && index!=-1 && shortestPath[i].distance<shortestPath[index].distance)
                index=i;
        }
        flag[index]=1;
        //修改到各个顶点的最短路径
        for(i=0;i<G.vexnum;i++){
            if(i==v0)
                continue;
            if(G.arc[index][i]>0 && G.arc[index][i]+shortestPath[index].distance<shortestPath[i].distance){
                shortestPath[i].distance=G.arc[index][i]+shortestPath[index].distance;
                //修改路径
                j=0;
                while(1){
                    shortestPath[i].path[j]=shortestPath[index].path[j];
                    if(shortestPath[index].path[j]==index)
                        break;
                    j++;
                }
                shortestPath[i].path[j+1]=i;
            }
        }
        n++;
    }
    //输出v0到v1的最短路径及长度
    if(shortestPath[v1].distance==Max){
        printf("%s到%s没有路径\n",G.vertex[v0],G.vertex[v1]);
        return;
    }
    printf("%s到%s的最短路径长度是：%d\n",G.vertex[v0],G.vertex[v1],shortestPath[v1].distance);
    printf("经过的顶点：  ");
    i=0;
    while(1){
		if(i==0)
		{
			printf("%s",G.vertex[shortestPath[v1].path[i]]);
		}else{
			printf("===>%s",G.vertex[shortestPath[v1].path[i]]);
		}
        if(shortestPath[v1].path[i]==v1)
            break;
        i++;
    }
    printf("\n");
}

void printShortestPath()
{
	CreateUDN();
    char md[20];
    int v0,v1;
    printf("请输入起点:\n");

    scanf("%s",md);
	getchar();
    if(strcmp(md,"东门")==0)
	{
		v0=1;
	}else if(strcmp(md,"艺术学院")==0)
	{
		v0=2;
	}else if(strcmp(md,"体育学院")==0)
	{
		v0=3;
	}else if(strcmp(md,"土木工程实验室")==0)
	{
		v0=4;
	}else if(strcmp(md,"图书馆")==0)
	{
		v0=5;
	}else if(strcmp(md,"第一教学楼B座")==0)
	{
		v0=6;
	}else if(strcmp(md,"建筑与环境学院")==0)
	{
		v0=7;
	}else if(strcmp(md,"计算机学院")==0)
	{
		v0=8;
	}else if(strcmp(md,"实验大楼")==0)
	{
		v0=9;
	}else if(strcmp(md,"文新学院楼区")==0)
	{
		v0=10;
	}else
	{
		printf("输入错误\n");
	}
	printf("请输入终点:\n");


    scanf("%s",md);
	getchar();
    if(strcmp(md,"东门")==0)
	{
		v1=1;
	}else if(strcmp(md,"艺术学院")==0)
	{
		v1=2;
	}else if(strcmp(md,"体育学院")==0)
	{
		v1=3;
	}else if(strcmp(md,"土木工程实验室")==0)
	{
		v1=4;
	}else if(strcmp(md,"图书馆")==0)
	{
		v1=5;
	}else if(strcmp(md,"第一教学楼B座")==0)
	{
		v1=6;
	}else if(strcmp(md,"建筑与环境学院")==0)
	{
		v1=7;
	}else if(strcmp(md,"计算机学院")==0)
	{
		v1=8;
	}else if(strcmp(md,"实验大楼")==0)
	{
		v1=9;
	}else if(strcmp(md,"文新学院楼区")==0)
	{
		v1=10;
	}else
	{
		printf("输入错误\n");
	}
	v0--;//从0开始
	v1--;//从0开始
    Dijkstra(v0,v1);
}
