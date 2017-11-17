/***************************************************************************
 *  @file       ALGraph.cpp
 *  @author     jz
 *  @date       21 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	ͼ���ڽӱ�
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int VertexType; //������������
typedef char InfoType; //�������Ϣ����
#define MAX_VERTEX_NUM 20 //��󶥵����
enum GraphKind {DG,DN,UDG,UDN}; //������ͼ��������������ͼ����������
struct ArcNode
{
	int adjvex; //�û���ָ��Ķ����λ��
	ArcNode * nextarc; //ָ����һ������ָ��
	InfoType *info; //�û������Ϣ��ָ��
};
struct VNode
{
	VertexType data; //������Ϣ
	ArcNode * firstarc; //ָ���һ�������ڸö���Ļ���ָ��
};
typedef VNode AdjList[MAX_VERTEX_NUM];
struct ALGraph
{
	AdjList vertices;
	int vexnum,arcnum; //ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind; //ͼ�������־
};
//__BEGIN -----������TopologicalSort.cpp-----

//�Լ�ʵ�ֵ�
Status CreateDG(ALGraph &G)
//�����ڽӱ�洢��ʾ����������ͼG
{
	int i,j,k,IncInfo;
	puts("�����붥�������������Ƿ��л���Ϣ(1����,0��û��) �ո�ָ�");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);
	puts("������ÿ�������ֵ");
	for(i=0;i<G.vexnum;++i) //���춥������
	{
		scanf("%d",&G.vertices[i].data);
		G.vertices[i].firstarc=NULL; //��ʼ��ָ��
	}
	puts("������ÿ������ʼ��v1���յ�v2");
	for(k=0;k<G.arcnum;++k)
	{
		scanf("%d %d",&i,&j);
		i=i-1; //ȷ��v1��v2��G�е�λ��
		j=j-1;
		ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode)); //�ٶ����㹻�ռ�
		p->adjvex=j; //�Ի�ͷ��㸳ֵ
		p->nextarc=G.vertices[i].firstarc;
		p->info=NULL;
		G.vertices[i].firstarc=p; //�ڳ������뻡��ͷ�Ĳ���
		if(IncInfo)
			;//����ߵ���Ϣ
	}
}//CreateDG

//�Լ�ʵ�ֵ�
Status ShowGraph(ALGraph G)
//�����ڽӱ�,����Ļ�����ͼg������
{
	int i;
	ArcNode *p;
	puts("show �ڽӱ�");
	for(i=0;i<G.vexnum;i++)
	{
		printf("vex:%d ",G.vertices[i].data);
		p=G.vertices[i].firstarc;
		printf("firstarc:(show adjvex): ");
		while(p)
		{
			printf("%d ",(p->adjvex)+1);
			p=p->nextarc;
		}
		putchar('\n');
	}
	return OK;
}//ShowGraph

//__END -----������TopologicalSort.cpp-----
int main()
{
}

