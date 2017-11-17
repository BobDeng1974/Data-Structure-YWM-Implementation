/***************************************************************************
 *  @file       CriticalPath.cpp
 *  @author     jz
 *  @date       28 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	AOE���Ĺؼ�·�����ڽӱ�
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int VertexType; //������������
typedef int InfoType; //�������Ϣ����
#define MAX_VERTEX_NUM 20 //��󶥵����
enum GraphKind {DG,DN,UDG,UDN}; //������ͼ��������������ͼ����������
struct ArcNode
{
	int adjvex; //�û���ָ��Ķ����λ��
	ArcNode * nextarc; //ָ����һ������ָ��
	InfoType info; //�û������Ϣ
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

//�Լ�ʵ�ֵ�
Status CreateDG(ALGraph &G)
//�����ڽӱ�洢��ʾ����������ͼG
{
	int i,j,k,c;
	puts("�����붥����������");
	scanf("%d %d",&G.vexnum,&G.arcnum);
	puts("������ÿ�������ֵ");
	for(i=0;i<G.vexnum;++i) //���춥������
	{
		scanf("%d",&G.vertices[i].data);
		G.vertices[i].firstarc=NULL; //��ʼ��ָ��
	}
	puts("������ÿ������ʼ��v1���յ�v2,Ȩ");
	for(k=0;k<G.arcnum;++k)
	{
		scanf("%d %d %d",&i,&j,&c);
		i=i-1; //ȷ��v1��v2��G�е�λ��
		j=j-1;
		ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode)); //�ٶ����㹻�ռ�
		p->adjvex=j; //�Ի�ͷ��㸳ֵ
		p->nextarc=G.vertices[i].firstarc;
		p->info=c;
		G.vertices[i].firstarc=p; //�ڳ������뻡��ͷ�Ĳ���
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
			printf("(%d %d) ",(p->adjvex)+1,p->info);
			p=p->nextarc;
		}
		putchar('\n');
	}
	return OK;
}//ShowGraph

//�Լ�ʵ�ֵ�
Status FindInDegree(ALGraph G,int *indegree)
//�����ڽӱ���ÿ����������ȣ�����������indegree��
{
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;++i)
		indegree[i]=0; //��ʼ������
	for(i=0;i<G.vexnum;++i)
	{
		p=G.vertices[i].firstarc;
		while(p)
		{
			++indegree[p->adjvex];
			p=p->nextarc;
		}
	}
	return OK;
}

//=====����Ϊջ�Ĳ���=====
//__BEGIN -----������SqStack.cpp-----
typedef int ElemType; //����Ԫ�ص����ͣ������ã��ɸ���

#define STACK_INIT_SIZE 100 //�洢�ռ��ʼ������
#define STACK_INCREMENT 10 //�洢�ռ��������

struct SqStack
{
	ElemType * base; //�ڹ���֮ǰ������֮��base��ֵΪnull
	ElemType * top; //ջ��ָ��
	int StackSize; //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
};

Status InitStack (SqStack &S)
//����һ����ջ
{
	S.base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!S.base) //�洢����ʧ��
		exit(OVERFLOW);
	S.top=S.base;
	S.StackSize=STACK_INIT_SIZE;
	return OK;
}//InitStack

Status GetTop(SqStack S,ElemType &e)
//��ջ���� �򷵻�e��ջ��Ԫ��
{
	if(S.top==S.base) //ջΪ��
		return ERROR;
	e=*(S.top-1);
	return OK;
}//GetTop

Status Push(SqStack &S,ElemType e)
//����Ԫ��eΪ�µ�ջ��Ԫ��
{
	if(S.top-S.base>=S.StackSize)//ջ����׷�Ӵ洢�ռ�
	{
		S.base=(ElemType *)realloc(S.base,(S.StackSize+STACK_INCREMENT)*sizeof(ElemType));
		if(!S.base)  //�洢����ʧ��
			exit(OVERFLOW);
		S.top=S.base+S.StackSize;
		S.StackSize+=STACK_INCREMENT;
	}
	*S.top++=e;
	return OK;
}//Push

Status Pop(SqStack &S,ElemType &e)
//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
{
	if(S.top==S.base) //��ջ
		return ERROR;
	e=*--S.top;
	return OK;
}//Pop

//�Լ�ʵ�ֵ�
Status DestroyStack(SqStack &S)
//����ջS��S���ٴ���
{
	free(S.base);
	S.base=S.top=NULL;
	S.StackSize=0;
	return OK;
}//DestroyStack


//__END -----������SqStack.cpp-----

//__BEGIN -----������Conversion.cpp-----

//�Լ�ʵ�ֵ�
Status StackEmpty(SqStack S)
//��ջSΪ��ջ���򷵻�ture�����򷵻�false
{
	if(S.top==S.base) //��ջ
		return true;
	return false;
}//StackEmpty

//__END -----������Conversion.cpp-----

//__BEGIN -----������LineEdit.cpp-----

//�Լ�ʵ�ֵ�
void ClearStack(SqStack &S)
//��S��Ϊ��ջ
{
	S.top=S.base;
}//ClearStack

//__END -----������LineEdit.cpp-----

//=====����Ϊջ�Ĳ���=====

Status TopologicalOrder(ALGraph G,SqStack &T,int *ve)
//����ͼG�����ڽӱ�洢�ṹ����������¼������緢��ʱ��ve
//��G�޻�·�������G�Ķ����һ���������е�ջT�У�������OK�����򷵻�ERROR
{
	int indegree[MAX_VERTEX_NUM]; //���ÿ��������ȵ�����
	SqStack S; //��������ȶ���ջS
	int i,j,k,count;
	ArcNode *p;
	FindInDegree(G,indegree); //��ÿ�����������
	InitStack(S);
	InitStack(T);
	for(i=0;i<G.vexnum;++i)
	{
		if(!indegree[i])
			Push(S,i);
		ve[i]=0; //��ʼ��ve
	}
	count=0; //������������
	printf("��������Ϊ��");
	while(!StackEmpty(S))
	{
		Pop(S,i);
		Push(T,i);
		printf("%d ",G.vertices[i].data);
		++count; //���i�Ŷ��㲢����
		p=G.vertices[i].firstarc;
		while(p)
		{
			k=p->adjvex;
			if(!(--indegree[k]))
				Push(S,k); //����ȼ�Ϊ0������ջ
			if(ve[i]+(p->info) >ve[k])
				ve[k]=ve[i]+(p->info);
			p=p->nextarc;	
		}//while
	}//while
	putchar('\n');
	DestroyStack(S);
	if(count<G.vexnum)
		return ERROR;
	return OK;
}//TopologicalOrder

Status CriticalPath(ALGraph G)
//GΪ�����������G�ĸ���ؼ��
{
	int ve[MAX_VERTEX_NUM]; //�¼������緢��ʱ��
	SqStack T;
	if(!TopologicalOrder(G,T,ve))
		return ERROR;
	int vl[MAX_VERTEX_NUM]; //ʱ�����ٷ���ʱ��
	int i,j,k,dut,ee,el;
	char tag;
	ArcNode *p;
	for(i=0;i<G.vexnum-1;++i)
		vl[i]=1000; //��ʼ����ٷ���ʱ��
	vl[G.vexnum-1]=ve[G.vexnum-1];
	puts("���");
	while(!StackEmpty(T))
	{
		Pop(T,j);
		p=G.vertices[j].firstarc;
		while(p)
		{
			k=p->adjvex;
			dut=p->info;
			if(vl[k]-dut<vl[j])
				vl[j]=vl[k]-dut;
			p=p->nextarc;
		}//while
	}
	printf("ve ");
	for(i=0;i<G.vexnum;++i)
		printf("%d ",ve[i]);
	putchar('\n');
	printf("vl ");
	for(i=0;i<G.vexnum;++i)
		printf("%d ",vl[i]);
	putchar('\n');
	for(j=0;j<G.vexnum;++j)
	{
		p=G.vertices[j].firstarc;
		while(p)
		{
			k=p->adjvex;
			dut=p->info;
			ee=ve[j];
			el=vl[k]-dut;
			tag=(ee==el)?'*':' ';
			printf("%d %d %d %d %d %c\n",j+1,k+1,dut,ee,el,tag);
			p=p->nextarc;
		}//while
	}
	DestroyStack(T);
}//CriticalPath


		
//main������������
int main()
{
	ALGraph g;
	CreateDG(g);
	ShowGraph(g);
	SqStack s;
	int a[MAX_VERTEX_NUM];
	CriticalPath(g);
	return 0;
}
