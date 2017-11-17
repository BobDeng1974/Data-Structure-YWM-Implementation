/***************************************************************************
 *  @file       Bank_Simulation.cpp
 *  @author     jz
 *  @date       21 Dec. 2015
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	��ɢ�¼�ģ�� �����Ŷ�
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>

#include "DataStructure.h"//������Ҫ��һЩ����

struct Event
{
	int OccurTime; //�¼�����ʱ��
	int NType; //�¼����� 0��ʾ�����¼���1��4��ʾ�ĸ����ڵ��뿪ʱ��
};

struct Person
{
	int ArrivalTime; //����ʱ��
	int Duration; //������������ʱ��
};

typedef Event ElemType_List; //����������Ԫ�ص�����
typedef Person ElemType_Queue; //�����������Ԫ�ص�����


//__BEGIN -----������LinkList.cpp-----

//���Ա�ĵ�����洢�ṹ
struct ListNode
{
	ElemType_List data;
	ListNode *next;
};

//ͷָ��
typedef ListNode * LinkList;

Status GetElem_Link(LinkList L,int i,ElemType_List &e)
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

Status ListInsert_Link(LinkList &L,int i,ElemType_List e)
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

Status ListDelete_Link(LinkList &L,int i,ElemType_List &e)
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

//__END -----������LinkList.cpp----

//�Լ�ʵ�ֵ�
Status ListEmpty(LinkList L)
//������Ϊ�ձ��򷵻�true�����򷵻�false
{
	if(L->next==NULL)
		return true;
	return false;
}//ListEmpty


//__BEGIN -----������LinkQueue.cpp-----

struct QNode
{
	ElemType_Queue data;
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

Status EnQueue(LinkQueue &Q,ElemType_Queue e)
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

Status DeQueue(LinkQueue &Q,ElemType_Queue &e)
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

//__END -----������LinkList.cpp----

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
Status Gethead(LinkQueue Q,ElemType_Queue &e)
//�����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�error
{
	if(Q.front==Q.rear)
		return ERROR;
	e=Q.front->next->data;
	return OK;
}//Gethead

//ȫ�ֱ���
int TotalTime; //�ۼƿͻ�����ʱ��
int CustomerNum; //�ͻ���
LinkList ev; //�¼���
Event en; //�¼�
LinkQueue q[5]; //4���ͻ����� q[0]����
int CloseTime =50; //���йر�ʱ�䣬�����ã��ɸ���
Person customer; //�ͻ���¼

//�Լ�ʵ�ֵ�
int cmp(Event a,Event b)
//���¼�a������ʱ��<��=��>�¼�b������ʱ�̷ֱ𷵻�-1��0��1
{
	if(a.OccurTime<b.OccurTime)
		return -1;
	else if(a.OccurTime==b.OccurTime)
		return 0;
	else
		return 1;
}//cmp

//�Լ�ʵ�ֵ�
void OrderInsert(LinkList &L,Event e)
//��ͷ���ĵ������Ա�L�е�Ԫ����e��cmp�����Ƚϣ���L��Ԫ�ش���e��λ��֮ǰ����Ԫ��e
{
	ListNode *p=L;  //��ʼ��pָ��ͷ���
	while((p->next)!=NULL&&cmp(e,p->next->data)>=0)
	{
		p=p->next;
	}
	ListNode *s=(ListNode *)malloc(sizeof(ListNode)); //�����½��
	if(!s) //�洢����ʧ��
		exit(OVERFLOW); 
	s->data=e;
	s->next=p->next; //����L��
	p->next=s;
}

void OpenForDay()
//��ʼ������
{
	TotalTime=0;
	CustomerNum=0;
	InitList_Link(ev); //��ʼ���¼�����Ϊ�ձ�
	en.OccurTime=0; //�趨��һ���ͻ������¼�
	en.NType=0;
	OrderInsert(ev,en); //�����¼���
	for(int i=1;i<=4;++i)
		InitQueue(q[i]); //��ʼ����������
}//OpenForDay

//�Լ�ʵ�ֵ�
int Minimum_Queue(LinkQueue *L)
//LΪ�������飬�������س�����̵Ķ��е����
{
	int q1=QueueLength(L[1]),q2=QueueLength(L[2]),q3=QueueLength(L[3]),q4=QueueLength(L[4]);
	printf("%d %d %d %d \n",q1,q2,q3,q4);
	if(q1<=q2&&q1<=q3&&q1<=q4)
		return 1;
	if(q2<=q1&&q2<=q3&&q2<=q4)
		return 2;
	if(q3<=q1&&q3<=q2&&q3<=q4)
		return 3;
	return 4;
}

void CustomerArrived()
//�����û������¼���en.NType=0
{
	++CustomerNum;
	int durtime=rand()%5+10; //������������ʱ��1-5���� �����ã��ɸ���
	int intertime=rand()%5+1; //�ͻ�����ļ��ʱ��1-5���� �����ã��ɸ���
	//printf("durtime %d intertime: %d  \n",durtime,intertime);
	int t=en.OccurTime+intertime; //��һ���ͻ�����ʱ��
	Event Etemp; //��ʱ����
	if(t>=CloseTime)
	{
		printf("�����Ѿ��°࣬������customer��\n");
	}else
	{
		Etemp.OccurTime=t;
		Etemp.NType=0;
		OrderInsert(ev,Etemp); //�����¼���
	}
	int i=Minimum_Queue(q);
	Person Ptemp;
	Ptemp.ArrivalTime=en.OccurTime;
	Ptemp.Duration=durtime;
	EnQueue(q[i],Ptemp); //�������
	if(QueueLength(q[i])==1)
	{ //�趨��i���е�һ���뿪�¼��������¼���
		Etemp.OccurTime=en.OccurTime+durtime;
		Etemp.NType=i;
		OrderInsert(ev,Etemp);
	}
}//CustomerArrived

void CustomerDepature()
{
	int i=en.NType;
	DeQueue(q[i],customer); //ɾ����i���е���ͷ�ͻ�
	//printf("i: %d en.OccurTime-customer.ArrivalTime: %d  \n",i,en.OccurTime-customer.ArrivalTime);
	TotalTime+=en.OccurTime-customer.ArrivalTime; //�ۼƿͻ�����ʱ��
	Event Etemp; //��ʱ����
	if(!QueueEmpty(q[i]))
	{
		Gethead(q[i],customer);
		Etemp.OccurTime=en.OccurTime+customer.Duration;
		Etemp.NType=i;
		OrderInsert(ev,Etemp);
	}
}//CustomerDepature

void Bank_Simulation()
{
	OpenForDay();
	while(!ListEmpty(ev))
	{
		ListDelete_Link(ev,1,en);
		if(en.NType==0)
			CustomerArrived();
		else
			CustomerDepature();
	}
	printf("\nTotalTime: %d CustomerNum: %d\n",TotalTime,CustomerNum);
	printf("The Average Time is %f\n",(float)TotalTime/CustomerNum);
}//Bank_Simulation

int main()
{
	Bank_Simulation();
	return 0;
}

