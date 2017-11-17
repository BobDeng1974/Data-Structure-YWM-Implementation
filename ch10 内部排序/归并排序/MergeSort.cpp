/***************************************************************************
 *  @file       MergeSort.cpp
 *  @author     jz
 *  @date       03 Mar. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ��ʮ��
 *  @note	�鲢����
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
	int a[10]={49,38,65,97,76,13,27,49,55,4};
	L->length=10;
	for(i=1;i<=L->length;++i)
		L->r[i].key=a[i-1];
}//CreateSL

void Merge(RedType *SR,RedType *TR,int left,int middle,int right)
//�������SR[left...middle]��SR[middle+1...right]�鲢Ϊ�����SR[left...right]
//TRΪ�������飬�����ϱ��иĶ�
{
	int i=left,j=middle+1,k=left;
	while(i<=middle && j<=right)
	{
		if(LQ(SR[i].key,SR[j].key))
			TR[k++]=SR[i++];
		else
			TR[k++]=SR[j++];
	}
	while(i<=middle)
		TR[k++]=SR[i++];
	while(j<=right)
		TR[k++]=SR[j++];
	for(i=left;i<=right;++i)
		SR[i]=TR[i];
}//Merge

void MSort(RedType *SR,RedType *TR,int left,int right)
//��SR[left...right]�鲢����
//TRΪ�������飬�����ϱ��иĶ�
{
	if(left<right)
	{
		int middle=(left+right)/2;
		MSort(SR,TR,left,middle);
		MSort(SR,TR,middle+1,right);
		Merge(SR,TR,left,middle,right);
	}
}//MSort

void MergeSort(SqList &L)
//��˳���L���鲢����
{
	RedType r[L.length+1];
	MSort(L.r,r,1,L.length);
}//MergeSort
	


//main������������
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	MergeSort(l);
	PrintSL(&l);
	return 0;
}
