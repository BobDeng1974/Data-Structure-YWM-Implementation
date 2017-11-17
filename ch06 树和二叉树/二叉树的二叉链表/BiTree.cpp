/***************************************************************************
 *  @file       BiTree.cpp
 *  @author     jz
 *  @date       14 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	�������Ķ�������洢�ṹ ���ֱ����㷨
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef char ElemType; //����Ԫ�ص�����
struct BiTNode
{
	ElemType data;
	BiTNode *lchild,*rchild; //���Һ���ָ��
};
typedef BiTNode * BiTree;

//=====����Ϊջ�Ĳ���=====
//__BEGIN -----������SqStack.cpp-----

typedef BiTNode * SElemType; //����Ԫ�ص����ͣ������ã��ɸ���

#define STACK_INIT_SIZE 100 //�洢�ռ��ʼ������
#define STACK_INCREMENT 10 //�洢�ռ��������

struct SqStack
{
	SElemType * base; //�ڹ���֮ǰ������֮��base��ֵΪnull
	SElemType * top; //ջ��ָ��
	int StackSize; //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
};

Status InitStack (SqStack &S)
//����һ����ջ
{
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base) //�洢����ʧ��
		exit(OVERFLOW);
	S.top=S.base;
	S.StackSize=STACK_INIT_SIZE;
	return OK;
}//InitStack

Status GetTop(SqStack S,SElemType &e)
//��ջ���� �򷵻�S��ջ��Ԫ��e
{
	if(S.top==S.base) //ջΪ��
		return ERROR;
	e=*(S.top-1);
	return OK;
}//GetTop

Status Push(SqStack &S,SElemType e)
//����Ԫ��eΪ�µ�ջ��Ԫ��
{
	if(S.top-S.base>=S.StackSize)//ջ����׷�Ӵ洢�ռ�
	{
		S.base=(SElemType *)realloc(S.base,(S.StackSize+STACK_INCREMENT)*sizeof(SElemType));
		if(!S.base)  //�洢����ʧ��
			exit(OVERFLOW);
		S.top=S.base+S.StackSize;
		S.StackSize+=STACK_INCREMENT;
	}
	*S.top++=e;
	return OK;
}//Push

Status Pop(SqStack &S,SElemType &e)
//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
{
	if(S.top==S.base) //��ջ
		return ERROR;
	e=*--S.top;
	return OK;
}//Pop

//�Լ�ʵ�ֵ�
Status DestroyStack(SqStack &S)
//����ջS��S���ٴ���
{
	free(S.base);
	S.base=S.top=NULL;
	S.StackSize=0;
	return OK;
}//DestroyStack

//__BEGIN -----������Conversion.cpp-----

//�Լ�ʵ�ֵ�
Status StackEmpty(SqStack S)
//��ջSΪ��ջ���򷵻�ture�����򷵻�false
{
	if(S.top==S.base) //��ջ
		return true;
	return false;
}//StackEmpty

//__END -----������Conversion.cpp-----

//__BEGIN -----������LineEdit.cpp-----

//�Լ�ʵ�ֵ�
void ClearStack(SqStack &S)
//��S��Ϊ��ջ
{
	S.top=S.base;
}//ClearStack

//__END -----������LineEdit.cpp-----
//=====����Ϊջ�Ĳ���=====


Status PreOrderTraverse(BiTree T,Status(* Visit)(ElemType e))
//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
{
	if(T)
	{
		if(Visit(T->data))
			if(PreOrderTraverse(T->lchild,Visit))
				if(PreOrderTraverse(T->rchild,Visit))
					return OK;
		return ERROR;
	}else
		return OK;
}//PreOrderTraverse

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

//�Լ�ʵ�ֵ�
Status PostOrderTraverse(BiTree T,Status(* Visit)(ElemType e))
//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
//�������������T�ĵݹ��㷨����ÿ������Ԫ�ص��ú���Visit
{
	if(T)
	{
		if(PostOrderTraverse(T->lchild,Visit))
			if(PostOrderTraverse(T->rchild,Visit))
				if(Visit(T->data))
					return OK;
		return ERROR;
	}else
		return OK;
}//PostOrderTraverse

Status PreOrderTraverse1(BiTree T,Status(* Visit)(ElemType e))
//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
//�������������T�ķǵݹ��㷨1����ÿ������Ԫ�ص��ú���Visit
{
	SqStack S;
	InitStack(S);
	Push(S,T); //��ָ���ջ
	BiTNode *p;
	while(!StackEmpty(S))
	{
		while(GetTop(S,p)&&p) //�ߵ�����߾�ͷ
		{
			if(!Visit(p->data))
			{
				DestroyStack(S);
				return ERROR;
			}
			Push(S,p->lchild);
		}
		Pop(S,p); //��ָ����ջ
		if(!StackEmpty(S)) //���ʽڵ㣬����һ��
		{
			Pop(S,p);
			Push(S,p->rchild);
		}//if
	}//while
	DestroyStack(S);
	return OK;
}//PreOrderTraverse1

Status InOrderTraverse1(BiTree T,Status(* Visit)(ElemType e))
//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
//�б���������T�ķǵݹ��㷨1����ÿ������Ԫ�ص��ú���Visit
{
	SqStack S;
	InitStack(S);
	Push(S,T); //��ָ���ջ
	BiTNode *p;
	while(!StackEmpty(S))
	{
		while(GetTop(S,p)&&p) //�ߵ�����߾�ͷ
			Push(S,p->lchild); 
		Pop(S,p); //��ָ����ջ
		if(!StackEmpty(S)) //���ʽڵ㣬����һ��
		{
			Pop(S,p);
			if(!Visit(p->data))
			{
				DestroyStack(S);
				return ERROR;
			}
			Push(S,p->rchild);
		}//if
	}//while
	DestroyStack(S);
	return OK;
}//InOrderTraverse1

Status InOrderTraverse2(BiTree T,Status(* Visit)(ElemType e))
//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
//�б���������T�ķǵݹ��㷨2����ÿ������Ԫ�ص��ú���Visit
{
	SqStack S;
	InitStack(S);
	BiTNode *p=T;
	while(p||!StackEmpty(S))
	{
		if(p) //��ָ���ջ������������
		{
			Push(S,p);
			p=p->lchild;
		}else //��ָ����ջ�����ʸ��ڵ㣬����������
		{
			Pop(S,p);
			if(!Visit(p->data))
			{
				DestroyStack(S);
				return ERROR;
			}
			p=p->rchild;
		}//else
	}//while
	DestroyStack(S);
	return OK;
}//InOrderTraverse2

//���ϵ��㷨
Status PostOrderTraverse1(BiTree T,Status(* Visit)(ElemType e))
//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú�����
//�������������T�ķǵݹ��㷨1����ÿ������Ԫ�ص��ú���Visit
{
	SqStack S;
	InitStack(S);
	Push(S,T); //��ָ���ջ
	BiTNode *p,*pre=NULL; //preָ���ѷ��ʹ������һ����㡣
	while(!StackEmpty(S))
	{
		//��ȡջ��ָ�룬�����ǰ�������������������������㲻�Ǹձ����ʵĽڵ㣻
		//�����ǰ�������������������������㲻�Ǹձ����ʵĽ��,
		//����ջ��ָ��ָ��������δ�����ʣ�������������������δ�����ʡ�
		//��ʱ����������������ջ��
		if(GetTop(S,p) && p->lchild && pre!=p->lchild && !(p->rchild && pre == p->rchild))
			Push(S, p->lchild);
		//���ջ��ָ������������ڣ���δ�����ʡ�����������ջ
		else if (p->rchild && pre!=p->rchild)
			Push(S,p->rchild);
		//������������������������ʹ���������ջ�������з��ʡ�����pre��
		else
		{
			Pop(S,p);
			if (!Visit(p->data))
			{
				DestroyStack(S);
				return ERROR;
			}
			pre = p;
		}
	}
	DestroyStack(S);
	return OK;
}//PostOrderTraverse1

Status CreateBiTree_PreOrder(BiTree &T)
//�������������������н���ֵ��һ���ַ������ո��ַ���ʾ������
//������������ʾ�Ķ�����T (����������������ݽڵ�Ŀ�������)
{
	char ch=getchar();
	if(ch==' ')
		T=NULL;
	else
	{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data=ch; //���ɸ��ڵ�
		CreateBiTree_PreOrder(T->lchild); //����������
		CreateBiTree_PreOrder(T->rchild); //����������
	}
	return OK;
}//CreateBiTree_PreOrder

Status print(ElemType e)
{
	putchar(e);
	return OK;
}
//main������������
int main()
{
	BiTree b;
	CreateBiTree_PreOrder(b);
	puts("PreOrderTraverse:");
	PreOrderTraverse(b,print);
	putchar('\n');
	puts("PreOrderTraverse1:");
	PreOrderTraverse1(b,print);
	putchar('\n');
	puts("InOrderTraverse:");
	InOrderTraverse(b,print);
	putchar('\n');
	puts("InOrderTraverse1:");
	InOrderTraverse1(b,print);
	putchar('\n');
	puts("InOrderTraverse2:");
	InOrderTraverse1(b,print);
	putchar('\n');
	puts("PostOrderTraverse:");
	PostOrderTraverse(b,print);
	putchar('\n');
	puts("PostOrderTraverse1:");
	PostOrderTraverse1(b,print);
	putchar('\n');
	return 0;
}
