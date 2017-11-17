/***************************************************************************
 *  @file       LinkQueue.cpp
 *  @author     jz
 *  @date       01 Dec. 2015
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	���е������ʾ��ʵ��
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
//������
#include<stdio.h>

#include "DataStructure.h" //������Ҫ��һЩ����

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

//main������������
int main()
{
	LinkQueue Q1;
	InitQueue(Q1);
	ElemType temp;
	for(int i=1;i<10;i++)
	{
		EnQueue(Q1,i);
	}
	for(int i=1;i<10;i++)
	{
		DeQueue(Q1,temp);
		printf("%d ",temp);
	}
	DestroyQueue(Q1);
	return 0;
}

