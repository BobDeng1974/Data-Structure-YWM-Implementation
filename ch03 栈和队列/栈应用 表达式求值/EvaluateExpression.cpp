/***************************************************************************
 *  @file       EvaluateExpression.cpp
 *  @author     jz
 *  @date       07 Nov. 2015
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	ջ��Ӧ�� ���ʽ��ֵ ������ȷ� 
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ���� 
//��Ӧһ����char��һ����int �������õ���һЩ��ʽchar��int��ת��

typedef int ElemType; //����Ԫ�ص�����

//__BEGIN -----������SqStack.cpp----

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

//__END -----������SqStack.cpp----

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

//��𴦶��岻һ��
ElemType GetTop(SqStack S)
//��ջ���� �򷵻�S��ջ��Ԫ��
{
	if(S.top==S.base) //ջΪ��
		return ERROR;
	return *(S.top-1);
}//GetTop

//OPΪ���������
char *OP="+-*/()#";

//�Լ�ʵ�ֵ�
bool In(char c,char *op)
//���ַ�c���ַ���op�д��ڣ��򷵻�true�����򷵻�false
{
	while(*op)
	{
		if(c==*op)
			return true;
		op++;
	}
	return false;
}//In

//�Լ�ʵ�ֵ�
int Operate(int a,char theta,int b)
{
	//��ASCII��ת������ֵ
	a=a-48;
	b=b-48;
	switch(theta)
	{
		case'+':
			return a+b;
		case'-':
			return a-b;
		case'*':
			return a*b;
		case '/':
			return a/b;
		default:
			exit(EXIT_FAILURE);
	}//switch
}//Operate

char Precede(char a,char b)
//����a,b ���֮������ȹ�ϵ
{
	if(!In(a,OP))
		exit(EXIT_FAILURE);
	if(!In(b,OP))
		exit(EXIT_FAILURE);
	if(a=='('&&b==')'||a=='#'&&b=='#')
		return '=';
	if(a=='('||a=='#'||b=='(')
		return '<';
	if(a==')'||b=='#'||b==')')
		return '>';
	if(b=='+'||b=='-')
		return '>';
	if(a=='+'||a=='-')
		return '<';
	return '>';
}//Precede

int EvaluateExpression()
//�������ʽ��ֵ����������㷨������ı��ʽΪ�в�����Ϊ10��������
{
	SqStack OPTR,OPND;
	InitStack(OPTR); //OPTRλ�����ջ
	Push(OPTR,'#');
	InitStack(OPND); //OPNDΪ������ջ
	int theta,c=getchar();
	int a,b;
	while(c!='#'||GetTop(OPTR)!='#')
	{
		if(!In(c,OP)) //������������ջ
		{
			Push(OPND,c);
			c=getchar();
		}
		else
			switch (Precede(GetTop(OPTR),c))
			{
				case '<': //ջ��Ԫ������Ȩ��
					Push(OPTR,c);
					c=getchar();
					break;
				case'=': //�����Ų�������һ���ַ�
					Pop(OPTR,c);
					c=getchar();
					break;
				case'>': //��ջ���������ջ
					Pop(OPTR,theta);
					Pop(OPND,b);
					Pop(OPND,a);
					//48��Ϊascii��int��ת��
					Push(OPND,48+Operate(a,theta,b)); 
					break;
			}//switch
	}//while
	int ret=GetTop(OPND)-48;
	DestroyStack(OPTR);
	DestroyStack(OPND);
	return ret;
}//EvaluateExpression

//main������������
int main()
{
	printf("%d",EvaluateExpression());
	return 0;
}
