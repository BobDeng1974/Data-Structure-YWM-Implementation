/***************************************************************************
 *  @file       SqStack.cpp
 *  @author     jz
 *  @date       03 Nov. 2015
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	ջ˳��洢�ṹ��ʵ�� 
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
//������
#include<stdio.h>

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int ElemType; //����Ԫ�ص����ͣ������ã��ɸ���

#define STACK_INIT_SIZE 100 //�洢�ռ��ʼ������
#define STACK_INCREMENT 10 //�洢�ռ��������

struct SqStack
{
	ElemType * base; //�ڹ���֮ǰ������֮��base��ֵΪnull
	ElemType * top; //ջ��ָ��
	int StackSize; //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
};

Status InitStack (SqStack &S)
//����һ����ջ
{
	S.base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!S.base) //�洢����ʧ��
		exit(OVERFLOW);
	S.top=S.base;
	S.StackSize=STACK_INIT_SIZE;
	return OK;
}//InitStack

Status GetTop(SqStack S,ElemType &e)
//��ջ���� �򷵻�e��ջ��Ԫ��
{
	if(S.top==S.base) //ջΪ��
		return ERROR;
	e=*(S.top-1);
	return OK;
}//GetTop

Status Push(SqStack &S,ElemType e)
//����Ԫ��eΪ�µ�ջ��Ԫ��
{
	if(S.top-S.base>=S.StackSize)//ջ����׷�Ӵ洢�ռ�
	{
		S.base=(ElemType *)realloc(S.base,(S.StackSize+STACK_INCREMENT)*sizeof(ElemType));
		if(!S.base)  //�洢����ʧ��
			exit(OVERFLOW);
		S.top=S.base+S.StackSize;
		S.StackSize+=STACK_INCREMENT;
	}
	*S.top++=e;
	return OK;
}//Push

Status Pop(SqStack &S,ElemType &e)
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

//main������������
int main()
{
	SqStack S1;
	InitStack(S1);
	ElemType temp;
	for(int i=1;i<10;++i)
	{
		Push(S1,i);
	}
	for(int i=1;i<10;++i)
	{
		Pop(S1,temp);
		printf("%d ",temp);
	}
	putchar('\n');
	DestroyStack(S1);

	return 0;
}
