/***************************************************************************
 *  @file       Polynomial.cpp
 *  @author     jz
 *  @date       28 Oct. 2015
 *  @remark     ���ݽṹ c���԰� ��ε�� �ڶ���
 *  @note	�õ������ʾ һԪ����ʽ 
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>

#include "DataStructure.h"//������Ҫ��һЩ����

typedef struct 
//헵ı�ʾ ����ʽ������ΪLinkList������Ԫ��
{
	double coef; //ϵ��
	int expn; //ָ��
} ElemType; //����Ԫ�ص�����

//__BEGIN -----������LinkList.cpp-----
//���Ա�ĵ�����洢�ṹ
struct ListNode
{
	ElemType data;
	ListNode *next;
};
//ͷָ��
typedef ListNode * LinkList;

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

//__END -----������LinkList.cpp-----

//�ô�ͷ�������������ʾ����ʽ
typedef LinkList Polynomial;

//�����нڵ��λ��ָ��
typedef ListNode * Position;

//�Լ�ʵ�ֵ�
ListNode * GetHead(LinkList P)
//���ص������ͷָ��
{
	return P;
}

//�Լ�ʵ�ֵ�
Status LocateElem(LinkList L,ElemType e,Position &q,int (*compare)(ElemType,ElemType))
//����������L�д�����e�����ж�����compare()��ȡֵΪ0 ��Ԫ�أ���qָʾL�е�һ��ֵ
//Ϊe�Ľڵ��λ�ã�������ture������ָʾ��һ����e�����ж�����compare()ȡֵ>0
//��Ԫ�ص�ǰ��λ��,������false
{

	ListNode *p=L->next; //��ʼ��pָ���һ�����
	ListNode *pre=L; //��ʼ��preָ��p��ǰ�����
	while(p!=NULL&&compare(p->data,e)<0)
	{
		pre=p;
		p=p->next;
	}
	if(p==NULL||compare(p->data,e)>0)
	//������������e�����ж�����compare()ȡֵ<0����
	//�ҵ���һ����e�����ж�����compare()ȡֵ>0��Ԫ�ص�ǰ��λ��
	{
		q=pre;
		return false;
	}
	q=p;
	return true;
}

//�Լ�ʵ�ֵ�
int cmp(ElemType a,ElemType b)
//����a��ָ��ֵ<��=��>b��ָ��ֵ���ֱ𷵻�-1��0��1
{
	if(a.expn<b.expn)
		return -1;
	else if(a.expn==b.expn)
		return 0;
	return 1;
}

void CreatePolyn(Polynomial &P,int m)
//����m���ϵ����ָ����������ʾһԪ����ʽ����������P Pδ����ʼ��
{
	InitList_Link(P);
	ListNode *h=GetHead(P); //�õ�ͷ����ָ��
	ElemType e={0.0,-1};
	h->data=e; //����ͷ��������Ԫ��
	Position pos; //����λ��
	puts("please �����������ʽ�еķ�����");
	for(int i=1;i<=m;++i)//��������m��������
	{
		scanf("%lf %d",&e.coef,&e.expn);
		if(!LocateElem(P,e,pos,cmp))
		//��������в����ڸ���
		{
			ListNode *s=(ListNode *)malloc(sizeof(ListNode)); //�����½��
			if(!s) //�洢����ʧ��
				exit(OVERFLOW);
			s->data=e; //���ɽ��
			s->next=pos->next;
			pos->next=s; //��������
		}//if �������д��ڸ�����ʲô������...
	}	
}
void ShowList_Link(Polynomial P)
//�����ͷ���ĵ������Ա�L������Ԫ�ص�ֵ
{
	ListNode *p=P->next; //pΪ��ǰ���
	puts("��ǰ������ȫ��Ԫ��Ϊ��");
	while(p!=NULL)
	{
		//���Ԫ��ֵ������ElemType�Ĳ�ͬ�������б仯��
		printf("||%lf %d ",p->data.coef,p->data.expn);  
		p=p->next;
	}
	putchar('\n');
}

void AddPolyn(Polynomial &Pa,Polynomial &Pb)
//����ʽ�ӷ���Pa=Pa+Pb ������������ʽ�Ľ�㹹�ɡ��Ͷ���ʽ��������������Pb�ѱ�����
{
	ListNode *ha=Pa,*hb=Pb; //ha��hb�ֱ�ָ��Pa��Pb��ͷ���
	ListNode *qa=ha->next,*qb=hb->next; //qa��qb�ֱ�ָ��Pa��Pb�е�ǰ���
	ListNode * temp;
	while(qa&&qb) //qa��qb���ǿ�
	{
		switch(cmp(qa->data,qb->data))
		{
			case -1: //����ʽPa�е�ǰ���ָ��С
				ha=qa;
				qa=qa->next;
				break;
			case 0: //���ߵ�ָ��ֵ���
				qa->data.coef+=qb->data.coef;
				if(qa->data.coef!=0)
				{
					ha=qa;
					qa=qa->next;
				}else //ɾ������ʽPa�е�ǰ���
				{
					ha->next=qa->next;
					free(qa);
					qa=ha->next;
				}
				temp=qb;
				qb=qb->next;
				free(temp); //ɾ��Pb�е�ǰ���
				break;
			case 1: //����ʽPb�е�ǰ���ָ��С
				temp=qb->next;
				qb->next=qa;
				ha->next=qb;
				ha=qb;
				qb=temp;
				break;
		}//switch
	}//while
	if(qb) //����Pb��ʣ����
		ha->next=qb;
	free(hb); //�ͷ�Pb��ͷ���
}//AddPolyn

//main������������
int main()
{
	Polynomial p1,p2;
	CreatePolyn(p1,3);
	CreatePolyn(p2,3);
	AddPolyn(p1,p2);
	ShowList_Link(p1);
	DestroyList_link(p1);
	DestroyList_link(p2);
	return 0;
}
