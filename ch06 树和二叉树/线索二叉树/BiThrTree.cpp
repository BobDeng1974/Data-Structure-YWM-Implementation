/***************************************************************************
 *  @file       BiThrTree.cpp
 *  @author     jz
 *  @date       16 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	����������
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef char ElemType; //����Ԫ�ص�����

enum PointerTag{Link,Thread}; //Link==0:ָ�룬Thread==1:����

struct BiThrNode
{
	ElemType data;
	BiThrNode *lchild,*rchild; //���Һ���ָ��
	PointerTag LTag,RTag;//���ұ�־
};
typedef BiThrNode *BiThrTree;

Status InorderTraverse_Thr(BiThrTree T,Status (*Visit)(ElemType e))
//Tָ��ͷ��㣬ͷ��������lchildָ������
//�����������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
{
	BiThrNode *p=T->lchild; //pָ������
	while(p!=T) //�������������ʱ p==T
	{
		while(p->LTag==Link)
			p=p->lchild;
		if(!Visit(p->data)) //������������Ϊ�յĽ��
			return ERROR;
		while(p->RTag==Thread && p->rchild!=T)
		{
			p=p->rchild;
			Visit(p->data); //���ʺ�̽ڵ�
		}
		p=p->rchild;
	}
	return OK;
}//InorderTraverse_Thr

void InThreading(BiThrTree p,BiThrNode* &pre)
{
	if(p)
	{
		InThreading(p->lchild,pre); //������������
		if(!p->lchild) //ǰ������
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild) //�������
		{
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p; //����preָ��p��ǰ��
		InThreading(p->rchild,pre);//������������
	}
}//InThreading

Status InorderThreading(BiThrTree &Thrt,BiThrTree T)
//�������������T��������������������Thrtָ��ͷ���
{
	BiThrNode *pre,p;
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
	Thrt->LTag=Link; //����ͷ���
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt; //��ָ���ָ
	if(!T) //���������գ�����ָ���ָ
		Thrt->lchild=Thrt;
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		InThreading(T,pre); //���������������������
		pre->rchild=Thrt; //���һ�����������
		pre->RTag=Thread;
		Thrt->rchild=pre;
	}
	return OK;
}//InorderThreading

//__BEGIN -----������BiTree.cpp----�иĶ�

Status CreateBiTree_PreOrder(BiThrTree &T)
//�������������������н���ֵ��һ���ַ������ո��ַ���ʾ������
//������������ʾ�Ķ�����T (����������������ݽڵ�Ŀ�������)
{
	char ch=getchar();
	if(ch==' ')
		T=NULL;
	else
	{
		if(!(T=(BiThrNode *)malloc(sizeof(BiThrNode))))
			exit(OVERFLOW);
		T->data=ch; //���ɸ��ڵ�
		CreateBiTree_PreOrder(T->lchild); //����������
		CreateBiTree_PreOrder(T->rchild); //����������
	}
	return OK;
}//CreateBiTree_PreOrder

Status print(ElemType e)
{
	putchar(e);
	return OK;
}
//__BEGIN -----������BiTree.cpp----

void PreThreading(BiThrTree p,BiThrNode* &pre)
{
	if(p)
	{
		if(!p->lchild) //ǰ������
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild) //�������
		{
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p; //����preָ��p��ǰ��
		if(p->LTag==Link)
			PreThreading(p->lchild,pre); //������������
		PreThreading(p->rchild,pre);//������������
	}
}//PreThreading

Status PreorderThreading(BiThrTree &Thrt,BiThrTree T)
//�������������T��������������������Thrtָ��ͷ���
{
	BiThrNode *pre;
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))
		exit(OVERFLOW);
	Thrt->LTag=Link; //����ͷ���
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt; //��ָ���ָ
	if(!T) //���������գ�����ָ���ָ
		Thrt->lchild=Thrt;
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		PreThreading(T,pre); //���������������������
		pre->rchild=Thrt; //���һ�����������
		pre->RTag=Thread;
		Thrt->rchild=pre;
	}
	return OK;
}//PreorderThreading

Status PreorderTraverse_Thr(BiThrTree T,Status (*Visit)(ElemType e))
//Tָ��ͷ��㣬ͷ��������lchildָ������
//�����������������T�ķǵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
{
	puts("aaaaaaaaaaaaaaaaaaaaa");
	BiThrNode *p=T->lchild; //pָ������
	while(p!=T) //�������������ʱ p==T
	{
		while(p->LTag==Link)
		{
			if(!Visit(p->data))
				return ERROR;
			p=p->lchild;
		}
		if(!Visit(p->data)) 
			return ERROR;
		p=p->rchild;
	}
	return OK;
}//PreorderTraverse_Thr

//main������������
int main()
{
	BiThrTree t1,t2;
	CreateBiTree_PreOrder(t1);
	PreorderThreading(t2,t1);
	PreorderTraverse_Thr(t2,print);
}


