/***************************************************************************
 *  @file       TraverseMGraph.cpp
 *  @author     jz
 *  @date       21 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	ͼ�ı����㷨 ���ڽӾ���Ϊ�洢�ṹ
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

//=====����Ϊͼ���ڽӾ��󲿷�=====
//__BEGIN -----������MGraph.cpp----

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
	puts("������ͼ�����ͣ�0��ʾ����ͼDG,1��ʾ������DN,2��ʾ����ͼUDG,3��ʾ����ͼUDN");
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

//__END -----������MGraph.cpp----

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

//=====����Ϊͼ���ڽӾ��󲿷�=====

bool visited[MAX_VERTEX_NUM]; //���ʱ�־����

void DFS(MGraph G,int v,Status (*Visit)(MGraph G,int v))
//�ӵ�v����������ݹ��������ȱ���ͼG
{
	int w;
	visited[v]=true;
	Visit(G,v); //���ʵ�v������
	for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
		if(!visited[w]) //��v����δ���ʵ��ڽӶ���w�ݹ����DFS
			DFS(G,w,Visit);
}//DFS

void DFSTraverse(MGraph G,Status (*Visit)(MGraph G,int v))
//��ͼG��������ȱ���
{
	int v;
	for(v=0;v<G.vexnum;++v) //���ʱ�־�����ʼ��
		visited[v]=false;
	for(v=0;v<G.vexnum;++v)
		if(!visited[v]) //����δ���ʵĶ������DFS
			DFS(G,v,Visit); 
}//DFSTraverse

//�Լ�ʵ�ֵ�
Status PrintVex(MGraph G,int v)
{
	printf("%d ",G.vexs[v]);
	return OK;
}
//=====����Ϊջ�Ĳ���=====
//__BEGIN -----������LinkQueue.cpp-----

typedef int ElemType; //����Ԫ�ص����ͣ������ã��ɸ���

struct QNode
{
	ElemType data;
	struct QNode * next;
};

typedef QNode * QueuePtr;

struct LinkQueue
{
	QueuePtr front; //��ͷָ��
	QueuePtr rear; //��βָ��
};

Status InitQueue(LinkQueue &Q)
//����һ���ն���Q
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) //�洢����ʧ��
		exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}//InitQueue

Status DestroyQueue(LinkQueue &Q)
//���ٶ���Q
{
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return OK;
}//DestroyQueue

Status EnQueue(LinkQueue &Q,ElemType e)
//����Ԫ��eΪ����Q���µĶ�βԪ��
{
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW); //�洢����ʧ��
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}//EnQueue

Status DeQueue(LinkQueue &Q,ElemType &e)
//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK
//���򷵻�ERROR
{
	if(Q.front==Q.rear) //����Ϊ��
		return ERROR;
	QueuePtr p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) //�����н���һ��Ԫ��
		Q.rear=Q.front;
	free(p);
	return OK;
}//DeQueue
//__END -----������LinkQueue.cpp-----

//__BEGIN -----������Bank_Simulation.cpp-----

//�Լ�ʵ�ֵ�
int QueueLength(LinkQueue &Q)
//������ʽ����Q��Ԫ�ظ����������еĳ���
{
	int i=1;
	QueuePtr lq=Q.front->next;
	if(lq==NULL)
		return 0;
	while(lq!=Q.rear)
	{
		i++;
		lq=lq->next;
	}
	return i;
}//QueueLength

//�Լ�ʵ�ֵ�
Status QueueEmpty(LinkQueue Q)
//������QΪ�ն��У��򷵻�true�����򷵻�false
{
	return (Q.front==Q.rear);
}//QueueEmpty

//�Լ�ʵ�ֵ�
Status Gethead(LinkQueue Q,ElemType &e)
//�����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�error
{
	if(Q.front==Q.rear)
		return ERROR;
	e=Q.front->next->data;
	return OK;
}//Gethead

//__END -----������Bank_Simulation.cpp----

//=====����Ϊջ�Ĳ���=====
void BFSTraverse(MGraph G,Status (*Visit)(MGraph G,int v))
//��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited
{
	int v,w,u;
	LinkQueue Q;
	for(v=0;v<G.vexnum;++v)
		visited[v]=false;
	for(v=0;v<G.vexnum;++v)
	{
		if(!visited[v])
		{
			InitQueue(Q);
			visited[v]=true;
			Visit(G,v);
			EnQueue(Q,v);
			while(!QueueEmpty(Q))
			{
				DeQueue(Q,u);
				for(w=FirstAdjVex(G,u);w>=0;w=NextAdjVex(G,u,w))
					if(!visited[w])
					{
						visited[w]=true;
						Visit(G,w);
						EnQueue(Q,w);
					}//if
			}//while
			DestroyQueue(Q);
		}//if
	}//for
}//BFSTraverse


//main������������
int main()
{
	MGraph g;
	CreateGraph(g);
	ShowGraph(g);
	printf("BFSTraverse: ");
	BFSTraverse(g,PrintVex);
	return 0;
}
