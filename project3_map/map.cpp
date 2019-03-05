//#include "stdafx.h"
#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max 10000
#define NUM 10


//ͼ�Ķ���
typedef struct
{
    int vexnum;
    char vertex[NUM][20];
    int arc[NUM][NUM];
}MGraph;


//���������е�Ԫ�ض���
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

char Menu() // ���˵�
{
	int c;
	int flag;
	do{
		flag=1;
		printf ("*****���ֻ�У԰*****\n");
		printf ("���еص�:\n");
		printf ("����   ����ѧԺ   ����ѧԺ   ��ľ����ʵ����   ͼ���\n");
		printf ("��һ��ѧ¥B��   �����뻷��ѧԺ   �����ѧԺ   ʵ���¥   ����ѧԺ¥��\n");
		printf ("1.��ѯ�ص�\n");
		printf ("2.�����ص�֮�����̾���\n");
		printf ("3.�˳�\n");
		printf ("��������Ĳ���:\n");

		scanf("%d",&c);
		getchar();
		if(c==1||c==2||c==3)
			flag=0;
	}while(flag);
	return c+'0';
}


int main() // ������
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


void CreateUDN() // ����ͼ�ĺ���
{
	int i,j;
	G.vexnum=10;

	strcpy(G.vertex[0],"����");
	strcpy(G.vertex[1],"����ѧԺ");
	strcpy(G.vertex[2],"����ѧԺ");
	strcpy(G.vertex[3],"��ľ����ʵ����");
	strcpy(G.vertex[4],"ͼ���");
	strcpy(G.vertex[5],"��һ��ѧ¥B��");
	strcpy(G.vertex[6],"�����뻷��ѧԺ");
	strcpy(G.vertex[7],"�����ѧԺ");
	strcpy(G.vertex[8],"ʵ���¥");
	strcpy(G.vertex[9],"����ѧԺ¥��");
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
	printf("��������Ҫ��ѯ�ص������:\n");

	scanf("%s",dd);
	getchar();
	if(strcmp(dd,"����")==0)
	{
		printf("����:����\n");
		printf("���:�Ĵ���ѧ����\n");
	}else if(strcmp(dd,"����ѧԺ")==0)
	{
		printf("����:����ѧԺ\n");
		printf("���:�Ĵ���ѧ����ѧԺ\n");
	}else if(strcmp(dd,"����ѧԺ")==0)
	{
		printf("����:����ѧԺ\n");
		printf("���:�Ĵ���ѧ����ѧԺ\n");
	}else if(strcmp(dd,"��ľ����ʵ����")==0)
	{
		printf("����:��ľ����ʵ����\n");
		printf("���:�Ĵ���ѧ��ľ����ʵ����\n");
	}else if(strcmp(dd,"ͼ���")==0)
	{
		printf("����:ͼ���\n");
		printf("���:�Ĵ���ѧͼ���\n");
	}else if(strcmp(dd,"��һ��ѧ¥B��")==0)
	{
		printf("����:��һ��ѧ¥B��\n");
		printf("���:�Ĵ���ѧ��һ��ѧ¥B��\n");
	}else if(strcmp(dd,"�����뻷��ѧԺ")==0)
	{
		printf("����:�����뻷��ѧԺ\n");
		printf("���:�Ĵ���ѧ�����뻷��ѧԺ\n");
	}else if(strcmp(dd,"�����ѧԺ")==0)
	{
		printf("����:�����ѧԺ\n");
		printf("���:�Ĵ���ѧ�����ѧԺ\n");
	}else if(strcmp(dd,"ʵ���¥")==0)
	{
		printf("����:ʵ���¥\n");
		printf("���:�Ĵ���ѧʵ���¥\n");
	}else if(strcmp(dd,"����ѧԺ¥��")==0)
	{
		printf("����:����ѧԺ¥��\n");
		printf("���:�Ĵ���ѧ����ѧԺ¥��\n");
	}else
	{
		printf("�������\n");
	}
}

//�Ͻ�˹�����㷨
void Dijkstra(int v0,int v1)
{
    int i,j,index=-1;
    int n=1;//��¼�Ѿ������������֮�����̾���ĸ���
    ArrayNode shortestPath[NUM];
    int flag[NUM]={0};//��ǣ�Ϊ1��ʾ������������̾��������

    //1.��v0�����������ֱ�Ӿ��룬����ʼ��shortestPath����
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
    //2.ÿ����һ�����·��
    while(n<G.vexnum){
        //ѡ��shortestPath�о�����С�ģ����v0�������������·��
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
        //�޸ĵ�������������·��
        for(i=0;i<G.vexnum;i++){
            if(i==v0)
                continue;
            if(G.arc[index][i]>0 && G.arc[index][i]+shortestPath[index].distance<shortestPath[i].distance){
                shortestPath[i].distance=G.arc[index][i]+shortestPath[index].distance;
                //�޸�·��
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
    //���v0��v1�����·��������
    if(shortestPath[v1].distance==Max){
        printf("%s��%sû��·��\n",G.vertex[v0],G.vertex[v1]);
        return;
    }
    printf("%s��%s�����·�������ǣ�%d\n",G.vertex[v0],G.vertex[v1],shortestPath[v1].distance);
    printf("�����Ķ��㣺  ");
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
    printf("���������:\n");

    scanf("%s",md);
	getchar();
    if(strcmp(md,"����")==0)
	{
		v0=1;
	}else if(strcmp(md,"����ѧԺ")==0)
	{
		v0=2;
	}else if(strcmp(md,"����ѧԺ")==0)
	{
		v0=3;
	}else if(strcmp(md,"��ľ����ʵ����")==0)
	{
		v0=4;
	}else if(strcmp(md,"ͼ���")==0)
	{
		v0=5;
	}else if(strcmp(md,"��һ��ѧ¥B��")==0)
	{
		v0=6;
	}else if(strcmp(md,"�����뻷��ѧԺ")==0)
	{
		v0=7;
	}else if(strcmp(md,"�����ѧԺ")==0)
	{
		v0=8;
	}else if(strcmp(md,"ʵ���¥")==0)
	{
		v0=9;
	}else if(strcmp(md,"����ѧԺ¥��")==0)
	{
		v0=10;
	}else
	{
		printf("�������\n");
	}
	printf("�������յ�:\n");


    scanf("%s",md);
	getchar();
    if(strcmp(md,"����")==0)
	{
		v1=1;
	}else if(strcmp(md,"����ѧԺ")==0)
	{
		v1=2;
	}else if(strcmp(md,"����ѧԺ")==0)
	{
		v1=3;
	}else if(strcmp(md,"��ľ����ʵ����")==0)
	{
		v1=4;
	}else if(strcmp(md,"ͼ���")==0)
	{
		v1=5;
	}else if(strcmp(md,"��һ��ѧ¥B��")==0)
	{
		v1=6;
	}else if(strcmp(md,"�����뻷��ѧԺ")==0)
	{
		v1=7;
	}else if(strcmp(md,"�����ѧԺ")==0)
	{
		v1=8;
	}else if(strcmp(md,"ʵ���¥")==0)
	{
		v1=9;
	}else if(strcmp(md,"����ѧԺ¥��")==0)
	{
		v1=10;
	}else
	{
		printf("�������\n");
	}
	v0--;//��0��ʼ
	v1--;//��0��ʼ
    Dijkstra(v0,v1);
}
