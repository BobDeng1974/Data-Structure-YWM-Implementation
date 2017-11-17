/***************************************************************************
 *  @file       MGraph.cpp
 *  @author     jz
 *  @date       21 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	ͼ���ڽӾ���
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

//�����ϵ���� ����Ȩͼ��1��0��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ����
typedef int VRType; 
typedef int VertexType; //������������
typedef char InfoType; //�������Ϣ����

#define INFINITY INT_MAX //������ȡ�������ֵ
#define MAX_VERTEX_NUM 20 //��󶥵����
enum GraphKind {DG,DN,UDG,UDN}; //������ͼ��������������ͼ����������
struct ArcCell
{
	VRType adj; //�����ϵ
	InfoType *info; //�û������Ϣ��ָ��
};
typedef ArcCell AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
struct MGraph
{
	VertexType vexs[MAX_VERTEX_NUM]; //��������
	AdjMatrix arcs; //�ڽӾ���
	int vexnum,arcnum; //ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind; //ͼ�������־
};

Status CreateUDN(MGraph &G)
//�������飨�ڽӾ��󣩱�ʾ��������������G
{
	int i,j,k,w,IncInfo;
	puts("�����붥�������������Ƿ��л���Ϣ��1���У�0��û�У� �ո�ָ�");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);
	puts("������ÿ�������ֵ");
	for(i=0;i<G.vexnum;++i) //���춥������
		scanf("%d",&G.vexs[i]);
	for(i=0;i<G.vexnum;++i) //��ʼ���ڽӾ���
		for(j=0;j<=G.vexnum;++j)
		{
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;
		}
	puts("������ÿ���ߵ����������Ȩֵ");
	for(k=0;k<G.arcnum;++k) //�����ڽӾ���
	{
		scanf("%d %d %d",&i,&j,&w);
		i=i-1;
		j=j-1;
		G.arcs[i][j].adj=w;
		if(IncInfo)
			;//����ߵ���Ϣ
		G.arcs[j][i].adj=G.arcs[i][j].adj; //��<v1,v2>�ĶԳƻ�<v2,v1>
		G.arcs[j][i].info=G.arcs[i][j].info;
	}
	return OK;
}//CreateUDN

Status CreateGraph(MGraph &G)
//�������飨�ڽӾ��󣩱�ʾ��������ͼG
{
	puts("������ͼ�����ͣ�1��ʾ����ͼDG��2��ʾ������DN��3��ʾ����ͼUDG��4��ʾ����ͼUDN");
	scanf("%d",&G.kind);
	switch(G.kind)
	{
		case DG:
			//return CreateDG(G); //��������ͼG
		case DN:
			//return CreateDN(G); //����������G
		case UDG:
			//return CreateUDG(G); //��������ͼG
		case UDN:
			return CreateUDN(G); //����������G
		default:
			return ERROR;
	}
}//CreateGraph

//�Լ�ʵ�ֵ�
Status ShowGraph(MGraph G)
//����Ļ�����ͼg������
{
	int i,j;
	puts("vexs:");
	for(i=0;i<G.vexnum;++i)
		printf("%d ",G.vexs[i]);
	putchar('\n');
	puts("arcs:");
	for(i=0;i<G.vexnum;++i)
	{
		for(j=0;j<G.vexnum;++j)
		{
			if(G.arcs[i][j].adj==INFINITY)
				printf("0 ");
			else
				printf("%d ",G.arcs[i][j].adj);
		}
		putchar('\n');
	}
}//ShowGraph

//__BEGIN -----������TraverseMGraph.cpp----

//�Լ�ʵ�ֵ�
int FirstAdjVex(MGraph G,int v)
//�������飨�ڽӾ��󣩱�ʾ�������ؽ��v�ĵ�һ��(��vΪ��β�Ļ���)�ڽӶ���,��û���򷵻�-1
{
	int i=0;
	while(i<G.vexnum && G.arcs[v][i].adj==INFINITY)
		++i;
	if(i==G.vexnum)
		return -1;
	else
		return i;
}//FirstAdjVex

//�Լ�ʵ�ֵ�
int NextAdjVex(MGraph G,int v,int w)
//�������飨�ڽӾ��󣩱�ʾ�������ؽ��v��(��vΪ��β�Ļ���)��һ���������w�ģ��ڽӶ���,��û���򷵻�-1
{
	int i=w+1;
	while(i<G.vexnum && G.arcs[v][i].adj==INFINITY)
		++i;
	if(i>=G.vexnum)
		return -1;
	else
		return i;
}//NextAdjVex

//__END -----������TraverseMGraph.cpp----

//main������������
int main()
{
	MGraph g;
	CreateUDN(g);
	ShowGraph(g);
	return 0;
}



