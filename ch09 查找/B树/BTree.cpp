/***************************************************************************
 *  @file       BTree.cpp
 *  @author     jz
 *  @date       18 Feb. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� �ھ���
 *  @note	B��
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
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

#define M 3 //B-Tree�Ľף�����Ϊ3

typedef ElemType Record;
struct BTNode //�������
{
	int keynum; //����йؼ��ָ���
	BTNode *parent; //ָ��˫�׽ڵ�
	KeyType key[M+1]; //�ؼ���������0�ŵ�Ԫδ��
	BTNode *ptr[M+1]; //����ָ��������0�ŵ�Ԫ�õ�
	Record *recptr[M+1]; //��¼ָ��������0�ŵ�Ԫδ��
};
typedef BTNode * BTree; //B������
struct Result //B���Ĳ��ҽ������
{
	BTNode *pt; //ָ���ҵ��Ľ��
	int i; //�ڽ���еĹؼ������ 1<=i<=m;
	int tag; //1:���ҳɹ� 2:����ʧ��
};

//�Լ�ʵ�ֵ�
int Search(BTNode *p,KeyType K)
{
	int i=1;
	while(i <= p->keynum)
	{
		if(K<=p->key[i])
			break;
		++i;
	}
	if(K==p->key[i])
		return i;
	else
		return i-1;
}//Search

Result SearchBTree(BTree T,KeyType K)
//��M��B���ϲ��ҹؼ���K�����ؽ��(pt,i,tag).�����ҳɹ���
//��tag=1��ָ��pt��ָ����е�i���ؼ��ֵ���K����������ֵtag=0��
//����k�Ĺؼ���Ӧ������ָ��pt��ָ����е�i���ؼ��ֺ͵�i+1���ؼ���֮��
{
	BTNode *p=T,*q=NULL; //pָ�����ڵ㣬qָ��p��˫��
	int i=0;
	bool found=false;
	Result r;
	while(p&&!found)
	{
		i=Search(p,K);
		if(i>0 && p->key[i]==K)
			found=true;
		else
		{
			q=p;
			p=p->ptr[i];
		}
	}
	if(found) //���ҳɹ�
	{
		r.pt=p;
		r.i=i;
		r.tag=1;
	}else //���Ҳ��ɹ�
	{
		r.pt=q;
		r.i=i;
		r.tag=0;
	}
	return r;
}//SearchBTree

//�Լ�ʵ�ֵ�
void Insert(BTNode *q,int i,int x,BTNode *ap)
//��x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]
{
	int s;
	for(s=q->keynum;s>=i+1;--s)
	{
		q->key[s+1]=q->key[s];
		q->ptr[s+1]=q->ptr[s];
	}
	q->key[i+1]=x;
	q->ptr[i+1]=ap;		
	q->keynum=q->keynum+1;
}//Insert

//�Լ�ʵ�ֵ�
void split(BTNode *q,int s,BTree &ap)
//��q->key[s+1...M],q->ptr[s...M]��q->recptr[s+1...M]�����½��*ap
{
	int i,c=0;
	ap=(BTree)malloc(sizeof(BTNode));
	for(i=s;i<=M;++i,++c)
	{
		ap->key[c]=q->key[i];
		ap->ptr[c]=q->ptr[i];
		ap->recptr[c]=q->recptr[i];
	}
	q->keynum=s-1;
	ap->keynum=M-s;
	ap->parent=q->parent;
}//split

//�Լ�ʵ�ֵ�
void NewRoot(BTree &T,BTNode *q,int x,BTNode *ap)
//T�ǿ���(����q��ֵΪNULL)���߸��ڵ��ѷ���Ϊ���*q��*ap
//���ɺ���Ϣ(T,x,ap)���µĸ��ڵ�*T��ԭT��apΪ����ָ��
{
	BTNode *b=(BTree)malloc(sizeof(BTNode));
	b->keynum=1;
	b->parent=NULL;
	b->ptr[0]=T;
	b->ptr[1]=ap;
	b->key[1]=x;
	if(T!=NULL)
		T->parent=ap->parent=b;
	T=b;
}//NewRoot
	
Status InsertBTree(BTree &T,KeyType K,BTree q,int i)
//��m��B���Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K
//������ڵ��������˫�������б�Ҫ�Ľ����ѵ�����ʹT��Ȼ��M��B��
{
	int x=K,s;
	BTNode *ap=NULL;
	bool finished=false;
	while(q && !finished)
	{
		//��x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1];
		Insert(q,i,x,ap);
		if(q->keynum<M) //�������
			finished=true;
		else //���ѽ��*q
		{
			s=int(ceil(double(M)/2));
			//��q->key[s+1...M],q->ptr[s...M]��q->recptr[s+1...M]�����½��*ap
			split(q,s,ap);
			x=q->key[s];
			q=q->parent;
			if(q) //��˫�׽ڵ�*q�в���x�Ĳ���λ��
				i=Search(q,x);
		}
	}
	if(!finished)
		//T�ǿ�������(����q��ֵΪNULL)���߸��ڵ��ѷ���Ϊ���*��*ap
		//���ɺ���Ϣ(T,x,ap)���µĸ��ڵ�*T��ԭT��apΪ����ָ��
		NewRoot(T,q,x,ap);
}//InsertBTree

//main������������
int main()
{
	BTree T=NULL;
	int i=1;
	Result r;
	while(i!=0)
	{
		scanf("%d",&i);
		r=SearchBTree(T,i);
		if(r.tag)
			printf("find! %p %d\n",r.pt,r.i);
		else
		{
			printf("insert! %p %d\n",r.pt,r.i);
			InsertBTree(T,i,r.pt,r.i);
		}
	}
	return 0;
}
