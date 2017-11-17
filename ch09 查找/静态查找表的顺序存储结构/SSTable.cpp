/***************************************************************************
 *  @file       SSTable.cpp
 *  @author     jz
 *  @date       31 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� �ھ���
 *  @note	��̬���ұ��˳��洢�ṹ
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

#define MAXSIZE 200 //�������Ԫ�ظ��������ֵΪ200 �ɸ���
typedef int KeyType; //�ؼ�������˵��
struct SElemType //����Ԫ�����Ͷ���
{
	KeyType key; //�ؼ�����
	int data; //�Զ������
};
//�������ؼ��ֵıȽ�Լ�� ��ֵ�͹ؼ���
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))
//��̬���ұ��˳��洢�ṹ
struct SSTable
{
	//����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
	SElemType *elem;
	int length; //����
};

int Search_Seq(SSTable ST,KeyType key)
//��˳���ST�в�����ؼ��ֵ���key������Ԫ�أ����ҵ���
//����ֵΪ��Ԫ���ڱ��е�λ�ã�����Ϊ0
{
	ST.elem[0].key=key; //"�ڱ�"
	int i;
	for(i=ST.length;!EQ(ST.elem[i].key,key);--i) //�Ӻ���ǰ��
		;
	return i; //�Ҳ���ʱ��iΪ0
}//Search_Seq

//�Լ�ʵ�ֵ�
Status CreateSSTable(SSTable &S)
//����һ����̬���ұ�S
{
	int i,j,n;
	printf("���������Ԫ�ظ�����");
	scanf("%d",&n);
	S.length=n;
	SElemType *p;
	p=(SElemType *)malloc((n+1)*sizeof(SElemType));
	S.elem=p;
	puts("���������Ԫ��");
	for(i=1;i<=n;++i)
	{
		S.elem[i].data=i;
		scanf("%d",&j);
		S.elem[i].key=j;
	}
	return OK;
}//CreateSSTable

//�Լ�ʵ�ֵ�
Status DestroySSTable(SSTable S)
//���پ�̬���ұ�S
{
	free(S.elem);
	S.length=0;
	return OK;
}//DestroySSTable

//�Լ�ʵ�ֵ�
void ShowSSTable(SSTable S)
//����Ļ�������̬���ұ�
{
	int i;
	puts("show SSTable ");
	for(i=1;i<=S.length;++i)
	{
		printf("[%d %d] ",S.elem[i].data,S.elem[i].key);
	}
	putchar('\n');
}
int Search_Bin(SSTable ST,KeyType key)
//�������ST�в�������ؼ��ֵ���key������Ԫ�أ�
//���ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã�����Ϊ0
{
	int low=1; //�������ֵ
	int high=ST.length;
	int mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(EQ(key,ST.elem[mid].key))
			return mid; //�ҵ�����Ԫ��
		else if(LT(key,ST.elem[mid].key))
			high=mid-1; //������ǰ��������в���
		else
			low=mid+1; //�����ں��������в���
	}
	return 0; //˳����в����ڴ���Ԫ��
}//Search_Bin


//main������������
int main()
{
	SSTable S;
	KeyType i,n;
	CreateSSTable(S);	
	ShowSSTable(S);
	printf("������key: ");
	scanf("%d",&n);
	i=Search_Bin(S,n);
	printf("found: %d\n",i);
	DestroySSTable(S);
	return 0;
}
