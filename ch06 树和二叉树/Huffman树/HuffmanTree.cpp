/***************************************************************************
 *  @file       HuffmanTree.cpp
 *  @author     jz
 *  @date       18 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	Huffman����Huffman����
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef char ElemType; //����Ԫ�ص�����

struct HTNode
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
};
typedef HTNode * HuffmanTree; //��̬��������洢Huffman��
typedef char * * HuffmanCode; //��̬��������洢Huffman�����

//�Լ�ʵ�ֵ�
Status Select_HT(HuffmanTree HT,int i,int &s1,int &s2)
//��Huffman��HT��ǰi�������ѡ��parentΪ0��weight��С�������ڵ�s1��s2
{
	int c;
	int sw1,sw2;
	s1,s2=0;
	sw1=sw2=0x1000; //��Ϊweight�����ܴﵽ�����ֵ
	for(c=1;c<=i;c++)
	{
		if(HT[c].parent==0)
		{
			if(HT[c].weight<sw1)
			{
				s1=c;
				sw1=HT[c].weight;
			}
		}
	}
	for(c=1;c<=i;c++)
	{
		if(HT[c].parent==0)
		{
			if(HT[c].weight<sw2&&c!=s1)
			{
				s2=c;
				sw2=HT[c].weight;
			}
		}
	}
	if(s1==0||s2==0)
		return ERROR;
}

Status HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
//w���n���ַ���Ȩֵ����>0��,����Huffman��HT�������n���ַ���Huffman����
{
	if(n<=1)
		return ERROR;
	int m=2*n-1,i;
	HTNode * p;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); //0�ŵ�Ԫδ��
	for(p=HT+1,i=1;i<=n;++i,++p,++w) //0�ŵ�Ԫ δ�� ������HT+1
	{
		p->weight=*w;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}
	for(;i<=m;++i,++p)
	{
		p->weight=0;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}
	for(i=n+1;i<=m;++i) //��Huffman��
	{
		int s1,s2;
		//��HT��ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
		Select_HT(HT,i-1,s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	//---��Ҷ�ӵ���������ÿ���ַ���Huffman����---
	//����n���ַ������ͷָ������
	HC=(HuffmanCode)(malloc((n+1)*sizeof(char *)));
	char * cd=(char *)malloc(n*sizeof(char)); //���������Ĺ����ռ�
	cd[n-1]='\0'; //���������
	for(i=1;i<=n;++i) //����ַ���Huffman����
	{
		int start=n-1; //���������λ��
		int c,f;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
			if(HT[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
		//Ϊ��i���ַ��������ռ�
		HC[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
	return OK;
}//HuffmanCoding

Status HuffmanCoding1(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
//w���n���ַ���Ȩֵ����>0��,����Huffman��HT�������n���ַ���Huffman����
{
	if(n<=1)
		return ERROR;
	int m=2*n-1,i;
	HTNode * p;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); //0�ŵ�Ԫδ��
	for(p=HT+1,i=1;i<=n;++i,++p,++w) //0�ŵ�Ԫ δ�� ������HT+1
	{
		p->weight=*w;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}
	for(;i<=m;++i,++p)
	{
		p->weight=0;
		p->parent=0;
		p->lchild=0;
		p->rchild=0;
	}
	for(i=n+1;i<=m;++i) //��Huffman��
	{
		int s1,s2;
		//��HT��ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
		Select_HT(HT,i-1,s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	//---��Ҷ�ӵ���������ÿ���ַ���Huffman����---
	//����n���ַ������ͷָ������
	HC=(HuffmanCode)(malloc((n+1)*sizeof(char *)));
	char * cd=(char *)malloc(n*sizeof(char)); //���������Ĺ����ռ�
	int pp=m,cdlen=0;
	for(i=1;i<=m;i++)
		HT[i].weight=0; //����Huffmanʱ����������״̬��־
	while(pp)
	{
		if(HT[pp].weight==0) //����
		{
			HT[pp].weight=1;
			if(HT[pp].lchild!=0)
			{
				pp=HT[pp].lchild;
				cd[cdlen++]='0';
			}
			else if(HT[pp].rchild==0) //�Ǽ�Ҷ�ӽڵ���ַ��ı���	
			{
				HC[pp]=(char *)malloc((cdlen+1)*sizeof(char));
				cd[cdlen]='\0';
				strcpy(HC[pp],cd); //���Ʊ���
			}
		}else if(HT[pp].weight==1) //����
		{
			HT[pp].weight=2;
			if(HT[pp].rchild!=0)
			{
				pp=HT[pp].rchild;
				cd[cdlen++]='1';
			}
		}else //HT[pp].weight==2 ����
		{
			HT[pp].weight=0;
			pp=HT[pp].parent;
			--cdlen;
		}//else
	}//while
	free(cd);
	return OK;
}//HuffmanCoding1


//�Լ�ʵ�ֵ�
void ShowHCode(HuffmanTree HT,HuffmanCode HC,int *w,int n)
//���Huffman����Ͷ�Ӧ��Huffman����wΪn���ַ���Ȩֵ��nΪ�ַ�����
{
	int i;
	for(i=1;i<=n;i++)
		printf("%d  %s\n",*w++,HC[i]);
	putchar('\n');
	for(i=1;i<=2*n-1;i++)
		printf("%d  %d %d %d %d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
}//ShowHCode

//main������������
int main()
{
	HuffmanTree t;
	HuffmanCode hc;
	int w[8]={5,29,7,8,14,23,3,11};
	//int w[4]={7,5,2,4};
	HuffmanCoding1(t,hc,w,8);
	ShowHCode(t,hc,w,8);
	return 0;
}

