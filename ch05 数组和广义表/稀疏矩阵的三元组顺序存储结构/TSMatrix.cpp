/***************************************************************************
 *  @file       TSMatrix.cpp
 *  @author     jz
 *  @date       10 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	ϡ��������Ԫ��˳��洢�ṹ ���к��д�1��ʼ��
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef char ElemType; //����Ԫ�ص�����

#define MAXSIZE 200 //�������Ԫ���������ֵΪ200 �ɸ���
struct Triple
{
	int i,j; //�÷���Ԫ�����±�����±�
	ElemType e;
};
struct TSMatrix
{
	Triple data[MAXSIZE+1]; //����Ԫ��Ԫ��� data[0]δ��
	int mu,nu,tu; //����������������ͷ���Ԫ����
};

Status TransposeSMatrix(TSMatrix M,TSMatrix &T)
//������Ԫ���洢��ʾ����ϡ�����M��ת�þ���T
{
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	if(T.tu)
	{
		int q=1;
		for(int col=1;col<=M.nu;++col)
			for(int p=1;p<=M.tu;++p)
				if(M.data[p].j==col)
				{
					T.data[q].i=M.data[p].j;
					T.data[q].j=M.data[p].i;
					T.data[q].e=M.data[p].e;
					++q;
				}
	}
	return OK;
}//TransposeSMatrix

Status FastTransposeSMatrix(TSMatrix M,TSMatrix &T)
//������Ԫ���洢��ʾ����ϡ�����M��ת�þ���T
{
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	//num[0]��cpot[0]δ��
	int num[M.tu+1];
	int cpot[M.tu+1];
	if(T.tu)
	{
		int col;
		for(col=1;col<=M.nu;++col)
			num[col]=0;
		for(col=1;col<=M.nu;++col) //��M��ÿһ�к�����Ԫ����
			++num[M.data[col].j];
		cpot[1]=1;
		for(col=2;col<=M.tu;++col) //���col���е�һ������Ԫ��b.data�е����
			cpot[col]=cpot[col-1]+num[col-1];
		int p,q;
		for(p=1;p<=M.tu;++p)
		{
			col=M.data[p].j;
			q=cpot[col];
			T.data[q].i=M.data[p].j;
			T.data[q].j=M.data[p].i;
			T.data[q].e=M.data[p].e;
			++cpot[col];
		}//for
	}//if
	return OK;
}//FastTransposeSMatrix

//�Լ�ʵ�ֵ�
Status CreateTSMatrix(TSMatrix &M)
//����δ��ʼ��������Ԫ�������������
{
	printf("��Ҫ�������Ԫ������������������(�Իس���β)\n");
	scanf("%d %d %d",&M.mu,&M.nu,&M.tu);
	if(M.tu<0)
		return ERROR;
	int c;
	for(c=1;c<=M.tu;++c)
	{
		printf("�����%d����Ԫ�飬һ��%d��(�س���β)\n",c,M.tu);
		scanf("%d %d %d",&M.data[c].i,&M.data[c].j,&M.data[c].e);
	}
	return OK;
}//CreateTSMatrix

//�Լ�ʵ�ֵ�
Status ShowTSMatrix(TSMatrix M)
//���ϡ�����M�е�Ԫ��
{
	int c;
	puts("ϡ������е�Ԫ�����£�");
	for(c=1;c<=M.tu;++c)
		printf("%d  %d  %d\n",M.data[c].i,M.data[c].j,M.data[c].e);
	putchar('\n');
}//ShowTSMatrix


//main������������
int main()
{
	TSMatrix m,t;
	CreateTSMatrix(m);
	//TransposeSMatrix(m,t);
	FastTransposeSMatrix(m,t);
	ShowTSMatrix(t);
	return 0;
}
