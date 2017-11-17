/***************************************************************************
 *  @file       BInsertSort.cpp
 *  @author     jz
 *  @date       2 Mar. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ��ʮ��
 *  @note	�۰��������
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
	int a[9]={1,2,5,7,8,9,10,12,8};
	L->length=9;
	for(i=1;i<=L->length;++i)
		L->r[i].key=a[i-1];
}//CreateSL
void BInsertSort(SqList &L)
//��˳���L���۰��������
{
	int i,j,low,high,m;
	for(i=1;i<=L.length;++i)
	{
		L.r[0]=L.r[i]; //��L.r[i]�ݴ浽L.r[0]
		low=1;
		high=i-1;
		while(low<=high) //��r[low...high]���۰��������λ��
		{
			m=(low+high)/2; //�۰�
			if(LT(L.r[0].key,L.r[m].key)) //������ڵͰ���
				high=m-1;
			else //������ڸ߰���
				low=m+1;
		}
		for(j=i-1;j>=high+1;--j)
			L.r[j+1]=L.r[j]; //��¼����
		L.r[high+1]=L.r[0]; //����
	}
}//BInsertSort


//main������������
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	BInsertSort(l);
	PrintSL(&l);
	return 0;
}
