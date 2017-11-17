/***************************************************************************
 *  @file       HeapSort.cpp
 *  @author     jz
 *  @date       03 Mar. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ��ʮ��
 *  @note	������
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

typedef SqList HeapType; //�Ѳ���˳���洢��ʾ

void HeapAdjust(HeapType &H,int s,int m)
//��֪h.r[s...m]�м�¼�Ĺؼ��ֳ�H.r[s].key֮�������ѵĶ��壬
//����������H.r[s]�Ĺؼ��֣�ʹH.r[s...m]��Ϊһ���󶥶�
{
	RedType rc=H.r[s];
	int j;
	for(j=2*s;j<=m;j*=2) //��key�ϴ�ĺ��ӽ������ɸѡ
	{
		if(j<m &&LT(H.r[j].key,H.r[j+1].key))
			++j; //jΪ�ϴ�ļ�¼���±�
		if(!LT(rc.key,H.r[j].key))
			break; //rcӦ������λ��S��
		H.r[s]=H.r[j];
		s=j;
	}
	H.r[s]=rc; //����
}//HeapAdjust

void HeapSort(HeapType &H)
{
	int i;
	RedType r;
	for(i=H.length/2;i>0;--i) //��H[1...H.length]���ɴ󶥶�
		HeapAdjust(H,i,H.length);
	for(i=H.length;i>1;--i)
	{
		//���Ѷ���¼�͵�ǰδ������������H.r[1...i]�����һ����¼�໥����
		r=H.r[1];
		H.r[1]=H.r[i];
		H.r[i]=r;
		HeapAdjust(H,1,i-1); //��H.r[1...i-1]���µ���Ϊ�󶥶�
	}
}//HeapSort

//main������������
int main()
{
	SqList l;
	CreateSL(&l);
	PrintSL(&l);
	HeapSort(l);
	PrintSL(&l);
	return 0;
}
