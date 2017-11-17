/***************************************************************************
 *  @file       AVLTree.cpp
 *  @author     jz
 *  @date       18 Feb. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� �ھ���
 *  @note	ƽ�����������
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int KeyType; //�ؼ�������˵��
struct ElemType //����Ԫ�����Ͷ���
{
	KeyType key; //�ؼ�����
	int data; //�Զ������
};
//�������ؼ��ֵıȽ�Լ�� ��ֵ�͹ؼ���
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

#define LH +1 //���
#define EH 0  //�ȸ�
#define RH -1 //�Ҹ�

struct AVLNode
{
	ElemType data;
	int bf; //ƽ������
	AVLNode *lchild,*rchild; //���Һ���ָ��
};
typedef AVLNode * AVLTree;

void R_Rotate(AVLTree &p)
//����pΪ���Ķ�����������������������֮��pָ���µ�������㣬
//����ת����֮ǰ���������ĸ����
{
	AVLNode *lc=p->lchild; //lcָ���*p���������ĸ����
	p->lchild=lc->rchild; //lc���������ҽ�Ϊ*p��������
	lc->rchild=p;
	p=lc; //pָ���µĸ����
}//R_Rotate

void L_Rotate(AVLTree &p)
//����pΪ���Ķ�����������������������֮��pָ���µ�������㣬
//����ת����֮ǰ���������ĸ����
{
	AVLNode *rc=p->rchild; //lcָ���*p���������ĸ����
	p->rchild=rc->lchild; //lc���������ҽ�Ϊ*p��������
	rc->lchild=p;
	p=rc; //pָ���µĸ����
}//L_Rotate

void LeftBalance(AVLTree &T)
//����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����
//���㷨����ʱ��ָ��Tָ���µĸ����
{
	AVLTree lc,rd;
	lc=T->lchild; //lcָ��T�������������
	switch(lc->bf) //���*T����������ƽ��ȣ�������Ӧƽ�⴦��
	{
		case LH: //�½����������ӵ��������ϣ�Ҫ������������
			T->bf=lc->bf=EH;
			R_Rotate(T);
			break;
		case RH: //�½�������*T�����ӵ��������ϣ�Ҫ��˫������
			rd=lc->rchild; //rdָ��*T�����ӵ���������
			switch(rd->bf)
			{
				case LH:
					T->bf=RH;
					lc->bf=EH;
					break;
				case EH:
					T->bf=lc->bf=EH;
					break;
				case RH:
					T->bf=EH;
					lc->bf=LH;
					break;
			}//switch
			rd->bf=EH;
			L_Rotate(T->lchild);
			R_Rotate(T);
	}//switch
}//LeftBalance

void RightBalance(AVLTree &T)
//����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����
//���㷨����ʱ��ָ��Tָ���µĸ����
{
	AVLTree lc,rd;
	lc=T->rchild; //lcָ��T�������������
	switch(lc->bf) //���*T����������ƽ��ȣ�������Ӧƽ�⴦��
	{
		case LH: //�½��������Һ��ӵ��������ϣ�Ҫ��˫������
			rd=lc->lchild; //rdָ��*T���Һ��ӵ���������
			switch(rd->bf)
			{
				case LH:
					T->bf=EH;
					lc->bf=RH;
					break;
				case EH:
					T->bf=lc->bf=EH;
					break;
				case RH:
					T->bf=LH;
					lc->bf=EH;
					break;
			}//switch
			rd->bf=EH;
			R_Rotate(T->rchild);
			L_Rotate(T);
		case RH: //�½�������*T���Һ��ӵ��������ϣ�Ҫ������������
			T->bf=lc->bf=EH;
			L_Rotate(T);
			break;	
	}//switch
}//RightBalance
Status InsertAVL(AVLTree &T,ElemType e,bool &taller)
//����ƽ��Ķ�����T�в����ں�e����ͬ�ؼ��ֵĽ�㣬
//�����һ������Ԫ��Ϊe���½�㣬������1�����򷵻�0
//�������ʹ�ö���������ʧȥƽ�⣬����ƽ����ת����
//taller��ӦT������񣬳�ʼ����ʱֵ����
{
	if(!T) //�����½�㣬�������ߡ�����tallerΪtrue
	{
		T=(AVLNode *)malloc(sizeof(AVLNode));
		T->data=e;
		T->lchild=T->rchild=NULL;
		T->bf=EH;
		taller=true;
	}else
	{
		if(EQ(e.key,T->data.key)) //�����Ѵ��ں�e����ͬ�ؼ��ֵĽ�㣬���ٲ���
		{
			taller=false;
			return 0;
		}
		if(LT(e.key,T->data.key)) //Ӧ������*T���������н�������
		{
			if(!InsertAVL(T->lchild,e,taller)) //δ����
				return 0;
			if(taller) //�Ѳ��뵽*T�����������������������ߡ�
				switch(T->bf) //���*T��ƽ���
				{
					case LH: //ԭ�����������������ߣ���Ҫ����ƽ�⴦��
						LeftBalance(T);
						taller=false;
						break;
					case EH: //ԭ�����������ȸߣ��������������߶�ʹ������
						T->bf=LH;
						taller=true;
						break;
					case RH: //ԭ�����������������ߣ������������ȸ�
						T->bf=EH;
						taller=false;
						break;
				}//switch
		}else //Ӧ������*T���������н�������
		{
			if(!InsertAVL(T->rchild,e,taller)) //δ����
				return 0;
			if(taller) //�Ѳ��뵽*T�����������������������ߡ�
				switch(T->bf) //���*T��ƽ���
				{
					case LH: //ԭ�����������������ߣ������������ȸ�
						T->bf=EH;
						taller=false;
						break;
					case EH: //ԭ�����������ȸߣ��������������߶�ʹ������
						T->bf=RH;
						taller=true;
						break;
					case RH: //ԭ������������������,��Ҫ����ƽ�⴦��
						RightBalance(T);
						taller=false;
						break;
				}//switch
		}//else
	}//else
	return 1;
}//InsertAVL

//__BEGIN -----������BiTree.cpp-----

//�Լ�ʵ�ֵ�
Status InOrderTraverse(AVLTree T,Status(* Visit)(ElemType e))
//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
{
	if(T)
	{
		if(InOrderTraverse(T->lchild,Visit))
			if(Visit(T->data))
				if(InOrderTraverse(T->rchild,Visit))
					return OK;
		return ERROR;
	}else
		return OK;
}//InOrderTraverse

Status print(ElemType e)
{
	printf("%d ",e.key);
	return OK;
}//print

//__END -----������BiTree.cpp-----

//main������������
int main()
{
	AVLTree t=NULL;
	ElemType e;
	bool bi,taller;
	int k=1;
	while(k)
	{
		printf("search ?");
		scanf("%d",&k);
		e.key=k;
		bi=InsertAVL(t,e,taller);
		if(bi)
			puts("Insert");
		else
			puts("Found!");
	}
	putchar('\n');
	puts("OrderTraverse:");
	InOrderTraverse(t,print);
	putchar('\n');
	return 0;
}
