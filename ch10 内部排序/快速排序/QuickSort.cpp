/***************************************************************************
 *  @file       QuickSort.cpp
 *  @author     jz
 *  @date       03 Mar. 2016
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

int Partition(SqList &L,int low,int high)
//����˳������ӱ�r[low....high]�ļ�¼�������¼��λ��������������λ��
{
	L.r[0]=L.r[low]; //���ӱ�ĵ�һ����¼��Ϊ�����¼
	int pivotkey=L.r[low].key; //�����¼�ؼ���
	while(low<high) //�ӱ�����˽�������м�ɨ��
	{
		while(low<high && L.r[high].key>=pivotkey)
			--high;
		L.r[low]=L.r[high]; //���������¼С�ļ�¼�ƶ����Ͷ�
		while(low<high && L.r[low].key<=pivotkey)
			++low; 
		L.r[high]=L.r[low]; //���������¼��ļ�¼�ƶ����߶�
	}
	L.r[low]=L.r[0]; //�����¼��λ
	return low; //��������λ��
}//Partition

void QSort(SqList &L,int low,int high)
//��˳���L��������L.r[low...high]����������
{
	if(low<high) //���ȴ���1
	{
		int pivotloc=Partition(L,low,high); //һ��Ϊ��
		QSort(L,low,pivotloc-1); //�Ե��ӱ�ݹ�����
		QSort(L,pivotloc+1,high); //�Ը��ӱ�ݹ�����
	}
}//QSort

void QuickSort(SqList &L)
//��˳���L����������
{
	QSort(L,1,L.length);
}//QuickSort

//main������������
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	QuickSort(l);
	PrintSL(&l);
	return 0;
}
