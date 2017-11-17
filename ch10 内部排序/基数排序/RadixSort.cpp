/***************************************************************************
 *  @file       RadixSort.cpp
 *  @author     jz
 *  @date       05 Mar. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ��ʮ��
 *  @note	��������
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//#include<math.h>
//#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

#define MAX_NUM_OF_KEY 8//�ؼ������������ֵ
#define RADIX 10 //�ؼ��ֻ�������ʱ��ʮ���������Ļ���
#define MAX_SPACE 100
typedef int KeyType; //�ؼ�������˵��
typedef int InfoType; //��������������˵��
struct SLCell //��̬����Ľ������
{
	KeyType keys[MAX_NUM_OF_KEY]; //�ؼ���
	InfoType otheritems; //����������
	int next;
};
struct SLList //��̬��������
{
	SLCell r[MAX_SPACE]; //��̬����Ŀ����ÿռ䣬r[0]Ϊͷ���
	int keynum; //��¼�ĵ�ǰ�ؼ��ָ���
	int recnum; //��̬����ĵ�ǰ����
};
typedef int ArrType[RADIX]; //ָ����������

void Distribute(SLCell *r,int i,ArrType &head,ArrType &tail)
//��̬�����r���еļ�¼�Ѱ�(keys[0],...,keys[i-1])����
//�㷨����i���ؼ���keys[i]����RADIX���ӱ�ʹͬһ���ӱ��м�¼��keys[i]��ͬ
//head[0...RADIX-1]��tail[0...RADIX-1]�ֱ�ָ���ӱ��еĵ�һ�������һ����¼
{
	int j,p;
	for(j=0;j<RADIX;++j)
		head[j]=0; //���ӱ��ʼ��Ϊ�ձ�
	for(p=r[0].next;p;p=r[p].next)
	{
		j=r[p].keys[i];
		if(!head[j])
			head[j]=p;
		else
			r[tail[j]].next=p;
		tail[j]=p; //�嵽ĩβ
	}
}//Distribute

void Collect(SLCell *r,int i,ArrType head,ArrType tail)
//���㷨��keys[i]��С����ؽ�f[0...RADIX-1]��ָ���ӱ��������ӳ�һ������
//head[0...RADIX-1]��tail[0...RADIX-1]�ֱ�ָ���ӱ��еĵ�һ�������һ����¼
{
	int t,j;
	for(j=0;!head[j];++j)
		; //�ҵ���һ���ǿ��ӱ�
	r[0].next=head[j]; //r[0].nextָ��һ���ǿ��ӱ��е�һ�����
	t=tail[j];
	while(j<RADIX)
	{
		for(++j;j<RADIX-1 && !head[j];++j)
			; //�ҵ���һ���ǿ��ӱ�
		if(head[j] && j<RADIX) //���������ǿ��ӱ�
		{
			r[t].next=head[j];
			t=tail[j];
		}
	}
	r[t].next=0; //tָ�����һ���ǿ��ӱ��е����һ�����
}//Collect

void RadixSort(SLList &L)
//L�ǲ��þ�̬�����ʾ��˳�����L����������
//ʹ��L��Ϊ���ؼ�����С���������̬����L.r[0]Ϊͷ���
{
	int i;
	ArrType head;
	ArrType tail;
	for(i=0;i<L.recnum;++i)
		L.r[i].next=i+1;
	L.r[L.recnum].next=0; //��L����Ϊ��̬����
	for(i=0;i<L.keynum;++i) 
	{ //�����λ�������ζԹؼ��ֽ��з�����ռ�
		Distribute(L.r,i,head,tail);
		Collect(L.r,i,head,tail);
	}
}//RadixSort

void CreateSLL(SLList *L)
//�����
{
	int i,j,b,c;
	int a[10]={115,258,746,754,316,543,217,981,155,414};
	L->recnum=10; //10����������
	L->keynum=3; //3λ
	for(i=1;i<=L->recnum;++i)
	{
		L->r[i].otheritems=a[i-1];
		b=RADIX;
		for(j=0;j<L->keynum;++j)
		{
			L->r[i].keys[j]=(L->r[i].otheritems%b)/(b/RADIX);
			b=b*RADIX;
		}
	}
}//CreateSLL

void PrintSLL(SLList *L)
//���˳���
{
	int i,j;
	printf("Put: ");
	for(i=1;i<=L->recnum;++i)
		printf("%d ",L->r[i].otheritems);
	putchar('\n');
}//PrintSLL

void ShowSLL(SLList *L)
//���������
{
	int i,j;
	printf("Show: ");
	i=L->r[0].next;
	while(i)
	{
		printf("%d ",L->r[i].otheritems);
		i=L->r[i].next;
	}
	putchar('\n');
}//ShowSLL

//main������������
int main()
{

	SLList l;
	CreateSLL(&l);
	PrintSLL(&l);
	RadixSort(l);
	ShowSLL(&l);
	return 0;
}
