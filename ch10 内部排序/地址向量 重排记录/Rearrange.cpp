/***************************************************************************
 *  @file       Rearrange.cpp
 *  @author     jz
 *  @date       07 Mar. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ��ʮ��
 *  @note	��ַ���� ���ż�¼
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
	int a[8]={49,65,38,27,97,13,76,49};
	L->length=8;
	for(i=1;i<=L->length;++i)
		L->r[i].key=a[i-1];
}//CreateSL

void Rearrange(SqList &L,int adr[])
//adr����˳���L��������򣬼�L.r[adr[i]]�ǵ�iС�ļ�¼
//���㷨��adr����L.r,ʹ������
{
	int i,j,k;
	for(i=1;i<L.length;++i)
	{
		if(adr[i]!=i)
		{
			j=i;
			L.r[0]=L.r[i]; //�ݴ��¼L.r[i]
			while(adr[j]!=i)
			{ //����L.r[adj[r]]�ļ�¼��λֱ��adr[j]=iΪֹ
				k=adr[j];
				L.r[j]=L.r[k];
				adr[j]=j;
				j=k;
			}
			L.r[j]=L.r[0];
			adr[j]=j;
		}
	}
}//Rearrange



//main������������
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	int adr[MAXSIZE]={0,6,4,3,1,8,2,7,5};
	Rearrange(l,adr);
	PrintSL(&l);
	return 0;
}
