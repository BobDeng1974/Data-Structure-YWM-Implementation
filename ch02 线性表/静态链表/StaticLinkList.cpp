/***************************************************************************
 *  @file       StaticLinkList.cpp
 *  @author     jz
 *  @date       20 Oct. 2015
 *  @remark     ���ݽṹ c���԰� ��ε�� �ڶ���
 *  @note	���Ա���ʽ�洢�ṹ��ʵ�� ��̬����
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int ElemType; //����Ԫ�ص����ͣ������ã��ɸ���

//���Ա�ľ�̬������洢�ṹ
#define MAXSIZE 1000 //�������󳤶�
struct ListNode
{
	ElemType data;
	int cur;
};
typedef ListNode StaticLinkList[MAXSIZE];

//�˺�����ͬһ�ļ����������������ף��޷�ִ��
int LocateElem_StaticLink(StaticLinkList S,ElemType e)
//�ھ�̬�������Ա�L�в��ҵ�һ��ֵΪe��Ԫ��
//���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0
{
	int i=S[0].cur; //iָʾ���е�һ�����
	while(i&&S[i].data!=e) //�ڱ���˳������
		i=S[i].cur;
	return i;
}//LocateElem_StaticLink

void InitSpace_StaticLink(StaticLinkList &space)
//����һά����space�ĸ���������һ����������
//space[0].curΪ��������ͷָ�룬��0��Ϊ��ָ��
{
	for(int i=0;i<MAXSIZE-1;++i)
		space[i].cur=i+1;
	space[MAXSIZE-1].cur=0;
}//InitSpace_StaticLink

int Malloc_StaticLink(StaticLinkList &space)
//�����ÿռ������ǿգ��򷵻ط���Ľ���±꣬���򷵻�0
{
	int i=space[0].cur;
	if(space[0].cur)
		space[0].cur=space[i].cur;
	return i;
}//Malloc_StaticLink

void Free_StaticLink(StaticLinkList &space,int k)
//���±�Ϊk�Ŀ��н����յ���������
{
	space[k].cur=space[0].cur;
	space[0].cur=k;
}//Free_StaticLink

void difference(StaticLinkList &space,int &S)
//�������뼯��A��B��Ԫ�أ���һά����space�н�����ʾ����(A-B)||(B-A)�ľ�̬����SΪͷָ��
//���豸�ÿռ��㹻��spaceΪΪ��ʼ���ľ�̬����space[0].curΪ��������ͷָ��
{
	InitSpace_StaticLink(space); //��ʼ�����ÿռ�
	S=Malloc_StaticLink(space); //����S��ͷ���
	int r=S; //rָ��S�ĵ�ǰΪ����A�������
	int m,n; //mΪAԪ�صĸ�����nΪBԪ�صĸ���
	puts("����A,B��Ԫ�ظ��� �ո�ָ�");
	scanf("%d %d",&m,&n);
	int i,j; //ѭ���ñ���
	puts("����A��Ԫ��ֵ");
	for(j=1;j<=m;++j) //��������A������
	{
		i=Malloc_StaticLink(space); //������
		scanf("%d",&space[i].data); //����A��Ԫ��ֵ ������ElemType�Ĳ�ͬ�������б仯��
		space[r].cur=i; //���뵽��β
		r=i;
	}//for
	space[r].cur=0; //β����ָ��Ϊ��
	ElemType b;
	int p,k; 
	puts("����B��Ԫ��ֵ");
	for(j=1;j<=n;++j)
	//��������B��Ԫ�أ������ڵ�ǰ���У�����룬����ɾ��
	{
		scanf("%d",&b); //����B��Ԫ��ֵ������ElemType�Ĳ�ͬ�������б仯��
		k=space[S].cur; //kָ�򼯺�A�е�һ�����
		while(k!=space[r].cur&&space[k].data!=b) 
		//�ڵ�ǰ���в��� pΪ��ǰ����ǰ������ָ�� kΪ��ǰ�ڵ�ָ��
		{
			p=k; 
			k=space[k].cur;
		}//while
		if(k==space[r].cur)
		//��ǰ���в����ڸ�Ԫ�أ�������r��ָ���֮����r��λ�ò���
		{
			i=Malloc_StaticLink(space);
			space[i].data=b;
			space[i].cur=space[r].cur;
			space[r].cur=i;
		}//if
		else //��Ԫ�����ڱ��У�ɾ��֮
		{
			space[p].cur=space[k].cur;
			Free_StaticLink(space,k);
			if(r==k)
				r=p; //��ɾ������β��㣬�����޸�βָ��
		} //else
	}//for
}//difference

//�Լ�ʵ�ֵ�
void Show_StaticLink(const StaticLinkList &space,int S)
//�����̬����space�����е�Ԫ��ֵ��SΪͷ���
{
	int r=space[S].cur; //rΪ��ǰ���
	puts("��ǰ��̬������ȫ��Ԫ��Ϊ��");
	while(r) //������̬����
	{
		printf("%d ",space[r].data); //���Ԫ��ֵ������ElemType�Ĳ�ͬ�������б仯��
		r=space[r].cur;
	}
	putchar('\n');
}//Show_StaticLink

//main������������
int main()
{
	StaticLinkList S1;
	int i=0;
	difference(S1,i);
	Show_StaticLink(S1,i);
	return 0;
}

