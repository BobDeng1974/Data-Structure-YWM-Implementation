/***************************************************************************
 *  @file       SearchBST.cpp
 *  @author     jz
 *  @date       16 Feb. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� �ھ���
 *  @note	����������
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
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

//=====����Ϊ�������Ķ�������洢�ṹ�Ĳ���=====
//__BEGIN -----������BiTree.cpp-----
struct BiTNode
{
	ElemType data;
	BiTNode *lchild,*rchild; //���Һ���ָ��
};
typedef BiTNode * BiTree;


//�Լ�ʵ�ֵ�
Status InOrderTraverse(BiTree T,Status(* Visit)(ElemType e))
//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
{
	if(T)
	{
		if(InOrderTraverse(T->lchild,Visit))
			if(Visit(T->data))
				if(InOrderTraverse(T->rchild,Visit))
					return OK;
		return ERROR;
	}else
		return OK;
}//InOrderTraverse


Status print(ElemType e)
{
	printf("%d ",e.key);
	return OK;
}//print

//__END -----������BiTree.cpp-----

BiTree SearchBST(BiTree T,KeyType key)
//�ڸ�ָ��T��ָ�Ķ����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ��
//�����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ�룬���򷵻ؿ�ָ��
{
	if( !T || EQ(key,T->data.key) )
		return T; //���ҽ���
	else if(LT(key,T->data.key)) //���������м�������
		return SearchBST(T->lchild,key);
	else //���������м�������
		return SearchBST(T->rchild,key);
}//SearchBST

Status SearchBST_F(BiTree T,KeyType key,BiTree f,BiTree &p)
//�ڸ�ָ��T��ָ�Ķ����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ��
//�����ҳɹ�����ָ��pָ�������Ԫ�ؽ��,������true������ָ��pָ�����·��
//�Ϸ��ʵ����һ����㲢����false��ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
{
	if(!T) //���Ҳ��ɹ�
	{
		p=f;
		return false;
	}else if(EQ(key,T->data.key)) //���ҽ���
	{
		p=T;
		return true; 
	}else if(LT(key,T->data.key)) //���������м�������
		return SearchBST_F(T->lchild,key,T,p);
	else //���������м�������
		return SearchBST_F(T->rchild,key,T,p);
}//SearchBST_F

Status InsertBST(BiTree &T,ElemType e)
//��������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ��
//����e������true�����򷵻�false
{
	BiTNode *p,*s;
	if(!SearchBST_F(T,e.key,NULL,p)) //���Ҳ��ɹ�
	{
		s=(BiTree)malloc(sizeof(BiTNode));
		s->data=e;
		s->lchild=s->rchild=NULL;
		if(!p) //*sΪ�µĸ����
			T=s;
		else if(LT(e.key,p->data.key)) //*sΪ����
			p->lchild=s;
		else //*sΪ�Һ���
			p->rchild=s;
		return true;
	}else
		return false;
}//InsertBST

Status Delete(BiTree &p)
//�Ӷ�����������ɾ�����p�����ؽ��������������
{
	BiTNode *q,*s;
	if(!p->rchild) //����������ֻ���ؽ�����������
	{
		q=p;
		p=p->lchild;
		free(q);
	}
	else if(!p->lchild) //����������ֻ���ؽ�����������
	{
		q=p;
		p=p->rchild;
		free(q);
	}
	else //��������������
	{
		q=p;
		s=p->lchild; //ת��
		while(s->rchild) //Ȼ�����ҵ���ͷ
		{
			q=s;
			s=s->rchild;
		}
		p->data=s->data;
		if(q!=p)
			q->rchild=s->lchild; //�ؽ�*q��������
		else
			q->lchild=s->lchild; //�ؽ�*q��������
		free(s);
	}
	return true;
}//Delete

Status DeleteBST(BiTree &T,KeyType key)
//������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ��ɾ��������Ԫ�ؽ�㣬
//������true�����򷵻�false
{
	if(!T) //�����ڹؼ��ֵ���k������Ԫ��
		return false;
	else
	{
		if(EQ(key,T->data.key)) //�ҵ���
			return Delete(T);
		else if(LT(key,T->data.key))
			return DeleteBST(T->lchild,key);
		else
			return DeleteBST(T->rchild,key);
	}
}//DeleteBST


//main������������
int main()
{
	BiTree b=NULL;
	ElemType e;
	bool bi;
	int k=1;
	while(k)
	{
		printf("search ?");
		scanf("%d",&k);
		e.key=k;
		bi=InsertBST(b,e);
		if(bi)
			puts("Insert");
		else
			puts("Found!");
	}
	putchar('\n');
	puts("OrderTraverse:");
	InOrderTraverse(b,print);
	putchar('\n');
	while(k!=12345)
	{
		printf("delete ?");
		scanf("%d",&k);
		bi=DeleteBST(b,k);
		if(bi)
			puts("Delete!");
		else
			puts("NOT Found!");
		puts("OrderTraverse:");
		InOrderTraverse(b,print);
		putchar('\n');
		putchar('\n');
	}

	return 0;
}
