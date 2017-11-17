/***************************************************************************
 *  @file       DoubleLinkList.cpp
 *  @author     jz
 *  @date       20 Oct. 2015
 *  @remark     ���ݽṹ c���԰� ��ε�� �ڶ���
 *  @note	���Ա���ʽ�洢�ṹ��ʵ�� ˫������
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int ElemType; //����Ԫ�ص����ͣ������ã��ɸ���

//���Ա��˫������洢�ṹ
struct DoubleLinkNode
{
	ElemType data;
	struct DoubleLinkNode *prior; //ֱ��ǰ����ָ��
	struct DoubleLinkNode *next; //ֱ�Ӻ�̵�ָ��
};
typedef DoubleLinkNode *DoubleLinkList;

//�Լ�ʵ�ֵ�
DoubleLinkNode *GetElemPtr_DoubleLink(DoubleLinkList L,int i)
//����˫��ѭ�����Ա�L�е�i������ָ�룬���������򷵻�NULL i�ĺϷ�ֵΪ1<=i<=��
{
	int count=1; //������
	DoubleLinkNode *p=L->next; //pΪ��ǰλ�õ�ָ��
	while(p&&count<i)
	{
		p=p->next;
		++count;
	}
	if(p&&count==i)
		return p;
	else
		return NULL;
}

Status ListInsert_DoubleLink(DoubleLinkList &L,int i,ElemType e)
//�ڴ�ͷ����˫��ѭ�����Ա�L�е�i��λ��֮ǰ����Ԫ��e
//i�ĺϷ�ֵΪ1<=i<=��+1 ����GetElemPtr_DoubleLink��������ʱ�޷������+1�����
{
	DoubleLinkNode *p=GetElemPtr_DoubleLink(L,i); //pΪ����λ�õ�ָ��
	if(!p)
		return ERROR; //p=NULL ������λ�ò��Ϸ�
	DoubleLinkNode *s=(DoubleLinkNode *)malloc(sizeof(DoubleLinkNode)); //����洢�ռ�
	if(!s)
		return ERROR; //����洢ʧ��
	s->data=e;
	s->prior=p->prior;
	p->prior->next=s;
	s->next=p;
	p->prior=s;
	return OK;
}//ListInsert_DoubleLink

Status ListDelete_DoubleLink(DoubleLinkList &L,int i,ElemType &e)
//ɾ����ͷ����˫��ѭ�����Ա�L�ĵ�i��Ԫ�أ�����e������ֵ��i�ĺϷ�ֵΪ1<=i<=��
{

	DoubleLinkNode *p=GetElemPtr_DoubleLink(L,i); //pΪ����λ�õ�ָ��
	if(!p)
		return ERROR;
	e=p->data;
	p->prior->next=p->next;
	p->next->prior=p->prior;
	free(p); //�ͷŽ��
	return OK;
}//ListDelete_DoubleLink

//�Լ�ʵ�ֵ�
void InitList_DoubleLink(DoubleLinkList &L,ElemType e)
//����һ����ͷ�ڵ�Ŀյ����Ա�L
//�����������������ƣ��������һ��Ԫ��e
{
	L=(DoubleLinkList)malloc(sizeof(DoubleLinkNode));
	if(!L) //�洢����ʧ��
		exit(OVERFLOW);
	DoubleLinkNode * p=(DoubleLinkList)malloc(sizeof(DoubleLinkNode));
	if(!p) //�洢����ʧ��
		exit(OVERFLOW);
	p->data=e;
	L->next=p;
	L->prior=p;
	p->prior=L;
	p->next=L;
}

//�Լ�ʵ�ֵ�
void Show_DoubleLink(DoubleLinkList L)
//�����ͷ����˫��ѭ�����Ա�L������Ԫ�ص�ֵ
{
	DoubleLinkNode *p=L->next; //pΪ��ǰ���
	puts("��ǰ������ȫ��Ԫ��Ϊ��");
	while(p!=L)
	{
		printf("%d ",p->data);  //���Ԫ��ֵ������ElemType�Ĳ�ͬ�������б仯��
		p=p->next;
	}
	putchar('\n');
}

//�Լ�ʵ�ֵ�
void DestroyList_Doublelink(DoubleLinkList &L)
{
//���ٵ������Ա�L��L���ٴ���
	DoubleLinkNode *p=L->next,*q;
	while(p!=L)
	{
		q=p->next;
		free(p);
		p=q;
	}
	free(L);
}
//main������������
int main()
{
	DoubleLinkList D1;
	InitList_DoubleLink(D1,12345);
	ListInsert_DoubleLink(D1,1,1234);
	ListInsert_DoubleLink(D1,1,123);
	ElemType e;
	ListDelete_DoubleLink(D1,2,e);
	Show_DoubleLink(D1);


	return 0;
}
