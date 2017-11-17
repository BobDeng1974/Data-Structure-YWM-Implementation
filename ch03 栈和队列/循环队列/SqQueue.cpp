/***************************************************************************
 *  @file       SqQueue.cpp
 *  @author     jz
 *  @date       01 Dec. 2015
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	ѭ������ ���е�˳��洢�ṹ
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
//������
#include<stdio.h>

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int ElemType; //����Ԫ�ص����ͣ������ã��ɸ���

#define MAXQSIZE 100 //�����г���

struct SqQueue
{
	ElemType *base; //��ʼ���Ķ�̬����洢�ռ�
	int front; //ͷָ�룬�����в��գ���ָ���ͷԪ��
	int rear; //βָ�룬�����в��գ���ָ�����βԪ�ص���һλ��
};

Status InitQueue(SqQueue &Q)
//����һ���ն���Q
{
	Q.base=(ElemType *)malloc(MAXQSIZE*sizeof(ElemType));
	if(!Q.base) //�洢����ʧ��
		exit(OVERFLOW);
	Q.front=Q.rear=0;
	return OK;
}//InitQueue

int QueueLength(SqQueue Q)
//����Q�е�Ԫ�ظ����������еĳ���
{
	return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}//QueueLength

Status EnQueue(SqQueue &Q,ElemType e)
//����Ԫ��eΪQ���µĶ�βԪ��
{
	if((Q.rear+1)%MAXQSIZE==Q.front) //������
		return ERROR;
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXQSIZE;
	return OK;
}//EnQueue

Status DeQueue(SqQueue &Q,ElemType &e)
//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK
//���򷵻�ERROR
{
	if(Q.front==Q.rear) //���п�
		return ERROR;
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXQSIZE;
	return OK;
}//DeQueue

//main������������
int main()
{
	SqQueue q1;
	InitQueue(q1);
	for(int i=0;i<=75;i++)
		EnQueue(q1,i);
	int temp;
	for(int i=0;i<=50;i++)
	{
		DeQueue(q1,temp);
		printf("%d ",temp);
	}
	putchar('\n');
	for(int i=0;i<=50;i++)
		EnQueue(q1,75+i);
	for(int i=0;i<=75;i++)
	{
		DeQueue(q1,temp);
		printf("%d ",temp);
	}
	return 0;
}
