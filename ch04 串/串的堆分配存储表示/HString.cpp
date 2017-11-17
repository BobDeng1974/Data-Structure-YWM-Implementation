/***************************************************************************
 *  @file       HString.cpp
 *  @author     jz
 *  @date       03 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	���Ķѷ���洢��ʾ
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

//���Ķѷ���洢��ʾ
struct HString
{
	char *ch; //���Ƿǿմ����򰴴�������洢��������chΪNULL
	int length; //������
};

Status StrInsert(HString &S,int pos,HString T)
//1<=pos<=S.length(S)+1 �ڴ�S�ĵ�pos���ַ�֮ǰ���봮T��
{
	if(pos<1||pos>S.length+1)
		return ERROR; //pos���Ϸ�
	if(T.length) //T�ǿգ������·���洢�ռ䣬����T
	{
		if(!(S.ch=(char *)realloc(S.ch,(S.length+T.length)*sizeof(char))))
			exit(OVERFLOW);
		for(int i=S.length-1;i>=pos-1;--i)
			S.ch[i+T.length]=S.ch[i]; //Ϊ����T���ڳ�λ��
		for(int i=0;i<T.length;++i)
			S.ch[pos-1+i]=T.ch[i]; //����T
		S.length+=T.length;
	}
	return OK;
}//StrInsert

//�Լ�ʵ�ֵ�
void InitString(HString &S)
//SΪһ��δ��ʼ���Ĵ�������SΪһ���մ�
{
	S.ch=NULL;
	S.length=0;
}//InitString

//�Լ�ʵ�ֵ�
Status InitScanfString(HString &S)
//����δ��ʼ���Ĵ�S������������
{
	int i=0,count;
	unsigned char c;
	printf("��Ҫ������ַ�����(�Կո��β) �������ַ�");
	scanf("%d ",&count);
	if(count<0)
		return ERROR;
	S.length=count;
	if(!(S.ch=(char *)malloc(S.length*sizeof(char))))
		exit(OVERFLOW);

	//�����ַ������� �������һ�����ûس���β
	while(i<count)
	{
		scanf("%c",&c);
		S.ch[i]=c;
		i++;
	}
	while(getchar()!='\n') //�����������ʣ���ַ�
		;
}//InitScanfString

//�Լ�ʵ�ֵ�
void StrShow(HString S)
//SΪһ���ǿ��ַ���������Ļ����ʾS������
{
	printf("�ַ�������Ϊ��");
	for(int i=0;i<S.length;++i)
		printf("%c",S.ch[i]);
}//StrShow

//�Լ�ʵ�ֵ�
void DestroyString(HString &S)
//����һ����
{
	if(S.ch!=NULL)
		free(S.ch);
	S.ch=NULL;
	S.length=0;
}//DestroyString

Status StrAssign(HString &T,char *chars)
//����һ����ֵ���ڴ�����chars�Ĵ�T
{
	if(T.ch)
		free(T.ch); //�ͷ�Tԭ�пռ�
	int i;
	char *c;
	for(i=0,c=chars;*c;++i,++c)
		; //��chars�ĳ���i
	if(!i)
	{
		T.ch=NULL;
		T.length=0;
	}else
	{
		if(!(T.ch=(char*)malloc(i*sizeof(char))))
			exit(OVERFLOW);
		for(int a=0;a<i;a++)
			T.ch[a]=chars[a];
		T.length=i;
	}
	return OK;
}//StrAssign

int Strlength(HString S)
//����S��Ԫ�ظ�������Ϊ���ĳ���
{
	return S.length;
}//Strlength

int StrCompare(HString S,HString T)
//��S>T���򷵻�ֵ>0,��S=T,�򷵻�ֵ=0,��S<T,�򷵻�ֵ<0
{
	for(int i=0;i<S.length&&i<T.length;++i)
		if(S.ch[i]!=T.ch[i])
			return S.ch[i]-T.ch[i];
	return S.length-T.length;
}//StrCompare

Status Concat(HString &T,HString S1,HString S2)
//��T������S1��S2���Ӷ��ɵ��´�
{
	if(T.ch)
		free(T.ch); //�ͷžɿռ�
	if(!(T.ch=(char *)malloc((S1.length+S2.length)*sizeof(char))))
		exit(OVERFLOW);
	int i;
	for(i=0;i<S1.length;++i)
		T.ch[i]=S1.ch[i];
	for(i=0;i<S2.length;i++)
		T.ch[i+S1.length]=S2.ch[i];
	T.length=S1.length+S2.length;
	return OK;
}//Concat

Status SubString(HString &Sub,HString S,int pos,int len)
//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
//���У�1<=pos<=S.length,0<=len<=S.length-pos+1
{
	if(pos<1||pos>S.length||len<0||len>S.length-pos+1)
		return ERROR;
	if(Sub.ch)
		free(Sub.ch); //�ͷžɿռ�
	if(!len) //���Ӵ�
	{
		Sub.ch=NULL;
		Sub.length=0;
	}else
	{
		if(!(Sub.ch=(char *)malloc(len*sizeof(char))))
			exit(OVERFLOW);
		for(int i=0;i<len;++i)
			Sub.ch[i]=S.ch[pos+i-1];
		Sub.length=len;
	}
	return OK;
}//SubString

//main������������
int main()
{
	HString s,s1,s2;
	InitString(s);
	InitScanfString(s1);
	//InitScanfString(s2);
	//Concat(s,s1,s2);
	//StrInsert(s,7,s1);
	//char a[7]="qwerty";
	//StrAssign(s,a);
	SubString(s,s1,2,4);
	StrShow(s);
	//printf("   %d",StrCompare(s,s1));
	DestroyString(s);
	DestroyString(s1);
	//DestroyString(s2);
	return 0;
}


