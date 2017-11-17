/***************************************************************************
 *  @file       SString.cpp
 *  @author     jz
 *  @date       05 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	���Ķ���˳��洢��ʾ
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

//���Ķ���˳��洢��ʾ
#define MAXSTRLEN 20 //�û�����255���ڶ�����󴮳�
typedef unsigned char SString[MAXSTRLEN+1]; //0�ŵ�Ԫ��Ŵ��ĳ���

Status Concat(SString &T,SString S1,SString S2)
//��T����S1��S2���Ӷ��ɵ��´�����δ�ضϣ��򷵻�true�����򷵻�false��
//T������δ����Ĵ�
{
	bool uncnt;
	if(S1[0]+S2[0]<=MAXSTRLEN) //δ�ض�
	{
		for(int i=1;i<=S1[0];i++)
			T[i]=S1[i];
		for(int i=1;i<=S2[0];i++)
			T[S1[0]+i]=S2[i];
		T[0]=S1[0]+S2[0];
		uncnt=true;
	}else if(S1[0]<MAXSTRLEN) //�ض�
	{
		for(int i=1;i<=S1[0];i++)
			T[i]=S1[i];
		for(int i=1;i<=MAXSTRLEN-S1[0];i++)
			T[S1[0]+i]=S2[i];
		T[0]=MAXSTRLEN;
		uncnt=false;
	}else
	{
		for(int i=0;i<=MAXSTRLEN;i++)
			T[i]=S1[i]; //T[0]==S1[0]==MAXSTRLEN
		uncnt=false;
	}
	return uncnt;
}//Concat

//�Լ�ʵ�ֵ�
void InitString(SString &S)
//SΪһ��δ��ʼ���Ĵ�������SΪһ���մ�
{
	S[0]=0;
}//InitString

//�Լ�ʵ�ֵ�
void InitScanfString(SString &S)
//����δ��ʼ���Ĵ�S������������
{
	int i=0;
	unsigned char c=0;
	//�����ַ������� �Իس���β���س��������ַ����ڣ�
	while(c!='\n'&&i<255)
	{
		S[i]=c;
		scanf("%c",&c);
		i++;
	}
	S[0]=i-1;
}//InitScanfString	

//�Լ�ʵ�ֵ�
void StrShow(SString S)
//SΪһ���ǿ��ַ���������Ļ����ʾS������
{
	for(int i=1;i<=S[0];i++)
		printf("%c",S[i]);
}//StrShow

Status SubString(SString &Sub,SString S,int pos,int len)
//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ���
//S������δ����Ĵ�
{
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)
		return ERROR;
	for(int i=1;i<=len;i++)
	{
		Sub[i]=S[pos+i-1];
	}
	Sub[0]=len;
	return OK;
}//SubString

int Index(SString S,SString T,int pos)
//�����Ӵ�T������S�е�pos���ַ���λ�ã��������ڣ�����ֵΪ0
//����T�ǿգ�1<=pos<=S[0]
{
	int i=pos,j=1;
	while(i<=S[0]&&j<=T[0])
	{
		if(S[i]==T[j]) //�����ȽϺ���ַ�
		{
			++i;
			++j;
		}else
		{
			i=i-j+2;
			j=1;
		}
	}//while
	if(j>T[0])
		return i-T[0];
	else
		return 0;
}//Index

int Index_KMP(SString S,SString T,int pos,int next[])
//����ģʽ��T��next������T������S�е�pos���ַ�֮���λ�õ�KMP�㷨
//����T�ǿգ�1<=pos<=S[0]
{
	int i=pos,j=1;
	while(i<=S[0]&&j<=T[0])
	{
		if(j==0||S[i]==T[j]) //�������Ƚ��ַ�
		{
			++i;
			++j;
		}else
			j=next[j];
	}//while
	if(j>T[0])
		return i-T[0]; //ƥ��ɹ�
	else
		return 0;
}//Index_KMP

void get_next(SString T,int next[])
//��ģʽ��T��next����ֵ����������next ������ǰ��
{
	int i=1,j=0;
	next[1]=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			++i;
			++j;
			next[i]=j;
		}else
			j=next[j];
	}
}//get_next

void get_nextval(SString T,int nextval[])
//��ģʽ��T��next����ֵ����������nextval ��������
{
	int i=1,j=0;
	nextval[1]=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			++i;
			++j;
			if(T[i]!=T[j])
				nextval[i]=j;
			else
				nextval[i]=nextval[j];
		}else
			j=nextval[j];
	}
}//get_nextval

//main������������
int main()
{
	SString s1,s2,s;
	InitString(s);
	puts("InitScanfString(s1);");
	InitScanfString(s1);
	puts("InitScanfString(s2);");
	InitScanfString(s2);
	//bool uncnt=Concat(s,s1,s2);
	//printf("%d   ",uncnt);
	//SubString(s,s1,3,4);
	int next[s2[0]];
	get_nextval(s2,next);
	printf("  %d",Index_KMP(s1,s2,1,next));
	//StrShow(s1);
	return 0;
}
