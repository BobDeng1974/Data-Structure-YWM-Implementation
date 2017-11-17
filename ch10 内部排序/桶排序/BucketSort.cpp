/***************************************************************************
 *  @file       BucketSort.cpp
 *  @author     jz
 *  @date       05 Mar. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ��ʮ��
 *  @note	Ͱ����
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//#include<math.h>
//#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

#define MAXSIZE 20 //˳������󳤶�
typedef int KeyType; //�ؼ�������˵��
typedef int InfoType; //��������������˵��
struct RedType //��¼���Ͷ���
{
	KeyType key; //�ؼ�����
	InfoType data; //����������
};
struct SqList
{
	RedType r[MAXSIZE+1]; //r[0]���û������ڱ���Ԫ
	int length; //˳�����
};

//�������ؼ��ֵıȽ�Լ�� ��ֵ�͹ؼ���
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

void PrintSL(SqList *L)
//���˳���
{
	int i;
	printf("Put: ");
	for(i=1;i<=L->length;++i)
		printf("%d ",L->r[i]);
	putchar('\n');
}//PrintSL

void CreateSL(SqList *L)
//����˳���
{
	int i;
	int a[10]={5,8,6,7,16,3,17,9,15,4};
	L->length=10;
	for(i=1;i<=L->length;++i)
		L->r[i].key=a[i-1];
}//CreateSL

void BucketSort(SqList &L)
//��˳���L��Ͱ����
//key��ΧĬ��Ϊ0....MAXSIZE
{
	RedType R[MAXSIZE];
	int count[MAXSIZE];
	int i;
	for(i=0;i<MAXSIZE;++i)
		count[i]=0; //��ʼ��������
	for(i=1;i<=L.length;++i)
	{
		count[L.r[i].key]++; //����
		R[i]=L.r[i]; //ԭ���鸴�Ƶ�R��
	}
	for(i=1;i<MAXSIZE;++i)
		count[i]=count[i]+count[i-1];
	for(i=1;i<MAXSIZE;++i)
		printf("%d ",count[i]);
	putchar('\n');
	
	for(i=1;i<=L.length;++i)
		L.r[count[R[i].key]--]=R[i]; 
	//�������0��ʼ��ǰ��--����һ��ʼ�ͺ���--
}//BucketSort

//main������������
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	BucketSort(l);
	PrintSL(&l);
	return 0;
}
