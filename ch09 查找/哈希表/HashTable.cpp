/***************************************************************************
 *  @file       HashTable.cpp
 *  @author     jz
 *  @date       23 Feb. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� �ھ���
 *  @note	��ϣ��
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//#include<math.h>
//#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int KeyType; //�ؼ�������˵��
struct ElemType //����Ԫ�����Ͷ���
{
	KeyType key; //�ؼ�����
	int data; //�Զ������
};
//�������ؼ��ֵıȽ�Լ�� ��ֵ�͹ؼ���
#define EQ(a,b) ((a)==(b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

//��ϣ������������һ�����ʵ���������
int hashsize[8]={499,997,1453,1999,2503,3011,3499,4001};

struct HashTable
{
	ElemType *elem; //����Ԫ�ش洢��ַ����̬��������
	int count; //��ǰ����Ԫ�ظ���
	int sizeindex; //hashsize[sizeindex]Ϊ��ǰ����
};
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1

#define NULLKEY 0 //��ʾ�޼�¼

//�Լ�ʵ�ֵ�
int Hash(KeyType K)
{
	return K;
}//Hash

//�Լ�ʵ�ֵ�
int collision(int p,int c)
{
	return p+1;
}//collision

Status SearchHash(HashTable H,KeyType K,int &p,int &c)
//�ڿ��Ŷ�ַHash���в��ҹؼ���ΪK��Ԫ�أ������ҳɹ���
//��pָʾ��������Ԫ���ڱ���λ�ã�������SUCCESS��
//������pָʾ����λ�ã�������UNSUCCESS
//c���ԼƳ�ͻ���������ֵ��0�����������ʱ�ο�
{
	p=Hash(K); //��ù�ϣ��ַ
	//��λ�����м�¼�ҹؼ��ֲ����
	while(H.elem[p].key!=NULLKEY && !EQ(K,H.elem[p].key) && p<hashsize[H.sizeindex])
		collision(p,++c); //�����һ̽���ַp
	if(EQ(K,H.elem[p].key) && p<hashsize[H.sizeindex]) //���ҳɹ�
		return SUCCESS;
	else
		return UNSUCCESS;
}//SearchHash

//�Լ�ʵ�ֵ�
void CreateHashTable(HashTable &H)
//����һ���µĹ�ϣ��H
{
	H.elem=(ElemType *)malloc(hashsize[0]*sizeof(ElemType));
	H.count=0;
	H.sizeindex=0;
	int i;
	ElemType e;
	e.key=NULLKEY;
	for(i=0;i<hashsize[0];++i)
		H.elem[i]=e;
}//CreateHashTable

//�Լ�ʵ�ֵ�
void RecreateHashTable(HashTable &H)
//�ؽ���ϣ��
{
	int i;
	ElemType e;
	e.key=NULLKEY;
	H.elem=(ElemType *)realloc(H.elem,hashsize[++H.sizeindex]);
	for(i=hashsize[H.sizeindex-1];i<hashsize[H.sizeindex];++i)
		H.elem[i]=e;
}//RecreateHashTable

Status InsertHash(HashTable &H,ElemType e)
//���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H�У�������OK
//����ͻ�����������ؽ���ϣ��
{
	int c=0,p;
	if(SearchHash(H,e.key,p,c))
		return DUPLICATE; //�������к�e��ͬ�ؼ��ֵ�Ԫ��
	else if(c<hashsize[H.sizeindex]/2 && p<hashsize[H.sizeindex]) 
	//����ͻ����δ�����ޣ�c����ֵ�ɵ���
	{ //����e
		H.elem[p]=e;
		++H.count;
		return OK;
	}else
	{
		RecreateHashTable(H); //�ؽ���ϣ��
		return UNSUCCESS;
	}
}//InsertHash

//main������������
int main()
{
	HashTable h;
	CreateHashTable(h);
	int i=1,tag;
	ElemType e;
	while(i!=0)
	{
		e.key=i;
		tag=InsertHash(h,e);
		if(tag==DUPLICATE)
			puts("Find!");
		else if(tag==OK)
			puts("Insert!");
		else
			puts("Fail! RecreateHashTable!");
		scanf("%d",&i);
	}
	return 0;
}

