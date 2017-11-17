/***************************************************************************
 *  @file       LinkList.cpp
 *  @author     jz
 *  @date       19 Oct. 2015
 *  @remark     ���ݽṹ c���԰� ��ε�� �ڶ���
 *  @note	���Ա���ʽ�洢�ṹ��ʵ�� ������
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>

#include "DataStructure.h"//������Ҫ��һЩ����

typedef int ElemType; //����Ԫ�ص����ͣ������ã��ɸ���

//���Ա�ĵ�����洢�ṹ
struct ListNode
{
	ElemType data;
	ListNode *next;
};
//ͷָ��
typedef ListNode * LinkList;

Status GetElem_Link(LinkList L,int i,ElemType &e)
{
//LΪ��ͷ���ĵ������ͷָ��
//����i��Ԫ�ش���ʱ����ֵ����e������OK,���򷵻�ERROR
	ListNode *p=L->next; //��ʼ��pָ���һ�����
	int j=1; //jΪ������
	while(p&&j<i)
	//˳�������ң�ֱ��pָ���i��Ԫ�ػ���pΪ��
	{
		p=p->next;
		++j;
	}
	if(!p||j>i) //��i��Ԫ�ز�����
		return ERROR;
	e=p->data;
	return OK;
}//GetElem_Link

Status ListInsert_Link(LinkList &L,int i,ElemType e)
{
//�ڴ�ͷ���ĵ������Ա��е�i��λ��֮ǰ����Ԫ��e
//i�ĺϷ�ֵΪ1<=i<=��+1
	ListNode * p=L;  //��ʼ��pָ��ͷ���
	int j=0;   //jΪ������
	while(p&&j<i-1)
	//Ѱ�ҵ�i-1�����
	{
		p=p->next;
		++j;
	}
	if(!p||j>i-1)
	//i<1���ߴ��ڱ�+1
		return ERROR;
	ListNode *s=(ListNode *)malloc(sizeof(ListNode)); //�����½��
	if(!s) //�洢����ʧ��
		exit(OVERFLOW); 
	s->data=e;
	s->next=p->next; //����L��
	p->next=s;
	return OK;
}//ListInsert_Link

//�Լ�ʵ�ֵ�
Status InitList_Link(LinkList &L)
{
//����һ����ͷ���Ŀյ����Ա�L
	L=(ListNode *)malloc(sizeof(ListNode));
	if(!L) //�洢����ʧ��
		exit(OVERFLOW);
	L->next=NULL;
	return OK;
}//InitList_Link

Status ListDelete_Link(LinkList &L,int i,ElemType &e)
{
//�ڴ�ͷ���ĵ������Ա�L�У�ɾ����i��Ԫ�أ�����e������ֵ
//i�ĺϷ�ֵΪ1<=i<=��
	ListNode *p=L; //��ʼ��pָ��ͷ���
	int j=0; //jΪ������
	while(p->next&&j<i-1)
	{
	//Ѱ�ҵ�i����㣬����pָ����ǰ��
		p=p->next;
		++j;
	}
	if(!(p->next)||j>i-1) //ɾ��λ�ò�����
		return ERROR;
	ListNode *q=p->next; //qΪҪɾ���Ľ��
	p->next=q->next; //ɾ�����
	e=q->data;
	free(q); //�ͷŽ��
	return OK;
}//ListDelete_Link

void CreateList_Link(LinkList &L,int n)
{
//��λ������n��Ԫ�ص�ֵ���������ͷ���ĵ������Ա�L
//LΪΪ��ʼ���ĵ������Ա� n�ĺϷ�ֵΪn>=1
	L=(LinkList)malloc(sizeof(ListNode));
	if(!L) //�洢����ʧ��
		exit(OVERFLOW);
	L->next=NULL; //�Ƚ�����һ����ͷ���ĵ�����
	ListNode * p=NULL;
	for(int i=n;i>0;--i)
	{
		p=(ListNode *)malloc(sizeof(ListNode)); //�����½��
		if(!p) //�洢����ʧ��
			exit(OVERFLOW);
		scanf("%d",&p->data); //����Ԫ��ֵ������ElemType�Ĳ�ͬ�������б仯��
		p->next=L->next;
		L->next=p;
	}
}//CreateList_Link

void MergeList_Link(LinkList &La,LinkList &Lb,LinkList &Lc)
{
//��֪�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����У�LcΪΪ��ʼ���ĵ������Ա�
//�鲢La��Lb�õ��µĵ������Ա�Lc��Lc��Ԫ��Ҳ���ǵݼ�����
//����������La��Lb�Ѿ������� Lc���������Ŀռ�
	ListNode *pa=La->next,*pb=Lb->next;
	ListNode *pc=La;
	Lc=pc; //��La��ͷ�����ΪLc��ͷ���
	while(pa&&pb) //�鲢����
		if(pa->data<=pb->data)
		{
			pc->next=pa;
			pc=pa;
			pa=pa->next;
		}else
		{
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}
	pc->next=pa?pa:pb; //����ʣ���
	free(Lb); //�ͷ�Lb��ͷ���
}//MergeList_Link

//�Լ�ʵ�ֵ�
void DestroyList_link(LinkList &L)
{
//���ٵ������Ա�L��L���ٴ���
	ListNode *p;
	while(L)
	{
		p=L->next;
		free(L);
		L=p;
	}
}

//__BEGIN -----������Bank_Simulation.cpp-----

//�Լ�ʵ�ֵ�
Status ListEmpty(LinkList L)
//������Ϊ�ձ��򷵻�true�����򷵻�false
{
	if(L->next==NULL)
		return true;
	return false;
}//ListEmpty

//__END -----������Bank_Simulation.cpp----

//main������������
int main()
{
	LinkList L1;
	InitList_Link(L1);
	ElemType temp;
	
	LinkList L2;
	//CreateList_Link(L2,10);
	
	LinkList L3,L4,L5;
	InitList_Link(L3);
	InitList_Link(L4);
	for(int i=1;i<=10;i++)
	{
		ListInsert_Link(L1,i,10-i);
	//	GetElem_Link(L1,i,temp);
	//	printf("%d",temp);
		
		ListInsert_Link(L3,i,2*i);
		ListInsert_Link(L4,i,3*i);
		GetElem_Link(L3,i,temp);
	//	printf("%d ",temp);
		GetElem_Link(L4,i,temp);
	//	printf("*%d ",temp);
	
	//	ListDelete_Link(L2,11-i,temp);
	//	printf(" *%d ",temp);
	}
	putchar('\n');

	MergeList_Link(L3,L4,L5);
	for(int i=1;i<=20;++i)
	{
		GetElem_Link(L5,i,temp);
		printf("%d ",temp);
	}
	putchar('\n');
	
	return 0;
}
