/***************************************************************************
 *  @file       ShellSort.cpp
 *  @author     jz
 *  @date       02 Mar. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ��ʮ��
 *  @note	Shell����
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

void ShellInsert(SqList &L,int dk)
//��˳���L��һ��shell��������
//��һ��ֱ�Ӳ�������������������޸�
// 1.ǰ���¼λ�õ�������dk��������1
// 2.r[0]֪ʶ�ݴ浥Ԫ�������ڱ�����j<=0ʱ������λ�����ҵ���
{
	int i,j;
	for(i=dk+1;i<=L.length;++i)
	{
		if(LT(L.r[i].key,L.r[i-dk].key)) //�轫L.r[i]�������������ӱ�
		{
			L.r[0]=L.r[i]; //�ݴ���L.r[0]
			for(j=i-dk;j>0 && LT(L.r[0].key,L.r[j].key);j-=dk)
				L.r[j+dk]=L.r[j]; //��¼���ƣ����Ҳ���λ��
			L.r[j+dk]=L.r[0];
		}
	}
}//ShellInsert

void ShellSort(SqList &L)
//������������dlta[0...t-1]��˳���L��Shell����
//�����ϵĸ�ʽ�����˸Ķ�
{
	//�Ķ�begin
	int dlta[20]; //���20�����޸�
	int i=L.length,count=0;
	while(i>=1)
	{
		dlta[count]=i/3;
		i=i/3;
		count++;
	}
	int t=count-1;
	//�Ķ�end
	int k;
	for(k=0;k<t;++k)
		ShellInsert(L,dlta[k]);
}//ShellSort


//main������������
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	ShellSort(l);
	PrintSL(&l);
	return 0;
}
