/***************************************************************************
 *  @file       ShortestPath.cpp
 *  @author     jz
 *  @date       29 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	ͼ�����·�����ڽӾ���
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

//=====����Ϊͼ���ڽӾ��󲿷֣��иĶ�=====
//__BEGIN -----������MGraph.cpp----
//�����ϵ���� ����Ȩͼ��1��0��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ����
typedef int VRType; 
typedef int VertexType; //������������
typedef char InfoType; //�������Ϣ����

#define INFINITY INT_MAX/2 //������ȡ�������ֵ
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

//__END -----������MGraph.cpp----

//����CreateUDN,�Լ�ʵ�ֵ�
Status CreateDN(MGraph &G)
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
	puts("������ÿ���ߵĶ���v1��v2��Ȩֵ");
	for(k=0;k<G.arcnum;++k) //�����ڽӾ���
	{
		scanf("%d %d %d",&i,&j,&w);
		i=i-1;
		j=j-1;
		G.arcs[i][j].adj=w;
		if(IncInfo)
			;//����ߵ���Ϣ
	}
	return OK;
}//CreateDN

//__BEGIN -----������MGraph.cpp----

Status CreateGraph(MGraph &G)
//�������飨�ڽӾ��󣩱�ʾ��������ͼG
{
	puts("������ͼ�����ͣ�1��ʾ����ͼDG��2��ʾ������DN��3��ʾ����ͼUDG��4��ʾ����ͼUDN");
	int i;
	scanf("%d",&i);
	G.kind=GraphKind(i-1);
	switch(G.kind)
	{
		case DG:
			//return CreateDG(G); //��������ͼG
		case DN:
			return CreateDN(G); //����������G
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

//=====����Ϊͼ���ڽӾ��󲿷֣��иĶ�=====
void ShortestPath_DIJ(MGraph G,int v0)
//��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]�����Ȩ����D[v]
{
	v0=v0-1;
	//finally[v]Ϊtrue�����ҽ���v����S�����Ѿ���ô�v0��v�����·��
	bool finally[MAX_VERTEX_NUM];
	//��P[v][w]Ϊ�棬��w�Ǵ�v0��v��ǰ��õģ���һ��������ȷ�ģ����·���ϵĶ���
	bool P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	//D[v]���v0��v�����·���Ĵ�Ȩ����
	int D[MAX_VERTEX_NUM];
	int v,i,j,w,min;
	for(v=0;v<G.vexnum;++v)
	{
		finally[v]=false;
		D[v]=G.arcs[v0][v].adj;
		for(w=0;w<G.vexnum;++w)
			P[v][w]=false; //���·��
		if(D[v]<INFINITY)
		{
			P[v][v0]=true; //??��ʲô�ã�
			P[v][v]=true;
		}//for
	}
	D[v0]=0;
	finally[v0]=true; //��ʼ��������v0����S��
	//��ʼ��ѭ����ÿ�����v0��ĳ��v��������·���������뵽S��
	for(i=1;i<G.vexnum;++i) //����G.vexnum-1������
	{
		min=INFINITY;
		for(w=0;w<G.vexnum;++w)
		{
			if(!finally[w]) //w������V-S��
				if(D[w]<min) //w������v0�������
				{
					v=w;
					min=D[w];
				}
		}
		finally[v]=true; //��v0���������v����S��
		for(w=0;w<G.vexnum;++w) //���µ�ǰ���·��������
		{
			if(!finally[w]&&(min+G.arcs[v][w].adj<D[w]))
			{ //�޸�D[w]��P[w],w����V-S
				D[w]=min+G.arcs[v][w].adj;
				for(j=0;j<G.vexnum;++j)
					P[w][j]=P[v][j];
				P[w][w]=true; //P[w]=P[v]+[w]
			}//if
		}//for
	}//for
	printf("D[v]: ");
	for(i=0;i<G.vexnum;++i)
		printf("%d ",D[i]);
	putchar('\n');
	puts("P[v][w]: ");
	for(i=0;i<G.vexnum;++i)
	{
		for(j=0;j<G.vexnum;++j)
			printf("%d ",P[i][j]);
		putchar('\n');
	}
}//ShortestPath_DIJ

void ShortestPath_FLOYD(MGraph G)
//��Floyd�㷨��������G�и��Զ���v��w֮�����·��P[v][w]�����Ȩ����D[v][w]
{
	int v,w,u,i;
	//��P[v][w][u]Ϊtrue����u�Ǵ�v��w��ǰ��õ����·���ϵĶ���
	bool P[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int D[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

	for(v=0;v<G.vexnum;++v) //���Խ��֮���ʼ��֪·��������
		for(w=0;w<G.vexnum;++w)
		{
			D[v][w]=G.arcs[v][w].adj;
			if(v==w) // �˴������ϲ�ͬ
				D[v][w]=0;
			for(u=0;u<G.vexnum;++u)
				P[v][w][u]=false;
			if(D[v][w]<INFINITY) //��v��w��ֱ��·��
			{
				P[v][w][v]=true;
				P[v][w][w]=true;
			}//if
		}//for
	for(u=0;u<G.vexnum;++u)
	for(v=0;v<G.vexnum;++v)
		for(w=0;w<G.vexnum;++w)
			
				if(D[v][u]+D[u][w]<D[v][w])
				{ //��v��u��w��һ��·������
					D[v][w]=D[v][u]+D[u][w];
					for(v=0;v<G.vexnum;++v)	
						P[v][w][i]=P[v][u][i]||P[u][w][i];
				}//if
	puts("D[v][w]: ");
	for(v=0;v<G.vexnum;++v)
	{
		for(w=0;w<G.vexnum;++w)
			printf("%d ",D[v][w]);
		putchar('\n');
	}
	puts("P[v][w][u]: ");
	for(v=0;v<G.vexnum;++v)
	{
		for(w=0;w<G.vexnum;++w)
		{
			for(u=0;u<G.vexnum;++u)
				printf("%d ",P[v][w][u]);
			putchar('\n');
		}
		putchar('\n');
	}
}//ShortestPath_FLOYD






//main������������
int main()
{
	MGraph g;
	CreateGraph(g);
	ShowGraph(g);
	ShortestPath_FLOYD(g);
	return 0;
}
