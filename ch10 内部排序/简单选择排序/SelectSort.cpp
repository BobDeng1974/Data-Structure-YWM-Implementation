/***************************************************************************
 *  @file       SelectSort.cpp
 *  @author     jz
 *  @date       03 Mar. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ��ʮ��
 *  @note	��ѡ������
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

void SelectSort(SqList &L)
//��˳���L����ѡ������
{
	int i,j,temp;
	for(i=1;i<L.length;++i)
	{
		temp=i;
		for(j=i+1;j<=L.length;++j)
			if(LT(L.r[j].key,L.r[temp].key))
				temp=j;
		if(i!=temp)
		{
			RedType t;
			t=L.r[i];
			L.r[i]=L.r[temp];
			L.r[temp]=t;
		}
	}
}//SelectSort

//main������������
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	SelectSort(l);
	PrintSL(&l);
	return 0;
}
