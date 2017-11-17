/***************************************************************************
 *  @file       OLGraph.cpp
 *  @author     jz
 *  @date       22 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	����ͼ��ʮ������
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int VertexType; //������������
typedef char InfoType; //�������Ϣ����
#define MAX_VERTEX_NUM 20 //��󶥵����
struct ArcBox
{
	int tailvex,headvex; //�û���ͷ��β�����λ��
	ArcBox * hlink,* tlink; //�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
	InfoType *info; //�û������Ϣ��ָ��
};
struct VexNode
{
	VertexType data;
	ArcBox * firstin,* firstout; //�ֱ�ָ��ö���ĵ�һ���뻡�ͳ���
};
struct OLGraph
{
	VexNode xlist[MAX_VERTEX_NUM]; //��ͷ����
	int vexnum,arcnum; //����ͼ�ĵ�ǰ�������ͻ���
};

Status CreateDG(OLGraph &G)
//����ʮ������洢��ʾ����������ͼG
{
	int i,j,k,IncInfo;
	puts("�����붥�������������Ƿ��л���Ϣ(1����,0��û��) �ո�ָ�");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);
	puts("������ÿ�������ֵ");
	for(i=0;i<G.vexnum;++i) //���춥������
	{
		scanf("%d",&G.xlist[i].data);
		G.xlist[i].firstin=NULL; //��ʼ��ָ��
		G.xlist[i].firstout=NULL;
	}
	puts("������ÿ������ʼ��v1���յ�v2");
	for(k=0;k<G.arcnum;++k)
	{
		scanf("%d %d",&i,&j);
		i=i-1; //ȷ��v1��v2��G�е�λ��
		j=j-1;
		ArcBox *p=(ArcBox *)malloc(sizeof(ArcBox)); //�ٶ����㹻�ռ�
		p->tailvex=i; //�Ի�ͷ��㸳ֵ
		p->headvex=j;
		p->hlink=G.xlist[j].firstin;
		p->tlink=G.xlist[i].firstout;
		p->info=NULL;
		G.xlist[j].firstin=G.xlist[i].firstout=p; //�ڳ������뻡��ͷ�Ĳ���
		if(IncInfo)
			;//����ߵ���Ϣ
	}
}//CreateDG

//�Լ�ʵ�ֵ�
Status ShowGraph(OLGraph G)
//����Ļ�����ͼg������
{
	int i;
	ArcBox *p;
	for(i=0;i<G.vexnum;i++)
	{
		printf("vex:%d ",G.xlist[i].data);
		p=G.xlist[i].firstin;
		printf("firstin:(show tailvex): ");
		while(p)
		{
			printf("%d ",(p->tailvex)+1);
			p=p->hlink;
		}
		putchar('\n');
		p=G.xlist[i].firstout;
		printf("firstin:(show headvex): ");
		while(p)
		{
			printf("%d ",(p->headvex)+1);
			p=p->tlink;
		}
		putchar('\n');
	}
}//ShowGraph
		
//main������������
int main()
{
	OLGraph g;
	CreateDG(g);
	ShowGraph(g);
	return 0;
}
