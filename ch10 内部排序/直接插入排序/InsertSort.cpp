/***************************************************************************
 *  @file       InsertSort.cpp
 *  @author     jz
 *  @date       25 Feb. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ��ʮ��
 *  @note	ֱ�Ӳ�������
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

void InsertSort(SqList &L)
//��˳���L����������
{
	int i,j;
	for(i=2;i<=L.length;++i)
		if(LT(L.r[i].key,L.r[i-1].key))
		{ //�뽫L.r[i]���������ӱ�
			L.r[0]=L.r[i]; //����Ϊ�ڱ�
			L.r[i]=L.r[i-1];
			for(j=i-2;LT(L.r[0].key,L.r[j].key);--j)
				L.r[j+1]=L.r[j];
			L.r[j+1]=L.r[0];
		}
}//InsertSort

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
	int a[8]={49,38,65,97,76,13,27,49};
	L->length=8;
	for(i=1;i<=L->length;++i)
		L->r[i].key=a[i-1];
}//CreateSL
//main������������
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	InsertSort(l);
	PrintSL(&l);
	return 0;
}
