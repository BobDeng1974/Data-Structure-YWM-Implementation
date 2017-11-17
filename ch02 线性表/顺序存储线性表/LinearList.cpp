/***************************************************************************
 *  @file       LinearList.cpp
 *  @author     jz
 *  @date       11 Oct. 2015
 *  @remark     ���ݽṹ c���԰� ��ε�� �ڶ���
 *  @note	���ݽṹ���Ա�˳��洢�ṹ��ʵ�� ������ʽ
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
//������
#include<stdio.h>

#include "DataStructure.h"//������Ҫ��һЩ����

typedef int ElemType; //����Ԫ�ص����ͣ������ã��ɸ���

//���Ա�Ķ�̬����˳��洢�ṹ
#define LIST_INIT_SIZE 100 //���Ա�洢�ռ�ĳ�ʼ������
#define LIST_INCREMENT 100 //���Ա�洢�ռ�ķ�������

typedef struct
{
	ElemType *elem; //�洢�ռ��ַ
	int length; //��ǰ����
	int ListSize; //��ǰ����Ĵ洢��������sizeof(ElemType)Ϊ��λ��
}SqList;
Status InitList_Sq(SqList &L)
{
//����һ���յ����Ա�L
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW); //�洢����ʧ��
	L.length=0; //�ձ� ����Ϊ0
	L.ListSize=LIST_INIT_SIZE; //��ʼ�洢����
	return OK;
}//InitList_Sq

Status ListInsert_Sq(SqList &L,int i,ElemType e)
{
//��˳��洢���е�i��λ��֮ǰ�����µ�Ԫ��e
//i�ĺϷ�ֵΪ1<=i<=L.length+1
	if(i<1||i>L.length+1)
		return ERROR; //iֵ���Ϸ�
	if(L.length>=L.ListSize)
	{//��ǰ�洢�ռ����� ���ӷ���
		ElemType * newbase=(ElemType *)realloc(L.elem,(L.ListSize+LIST_INCREMENT)*sizeof(ElemType));
		if(!newbase)
			exit(OVERFLOW); //�洢����ʧ��
		L.elem=newbase; //�»�ַ
		L.ListSize+=LIST_INCREMENT; //���Ӵ洢����
	}
	ElemType * InPosition=&(L.elem[i-1]); //InPositionΪ����λ��
	for(ElemType * p=&(L.elem[L.length-1]);p>=InPosition;--p)
		*(p+1)=*p; //����λ��֮���Ԫ������
	*InPosition=e; //����e
	++L.length; //����1
	return OK;
}//ListInsert_Sq

Status ListDelete_Sq(SqList &L,int i,ElemType &e)
{
//��˳�����Ա���ɾ����i��Ԫ�أ�����e������ֵ
//i�ĺϷ�ֵΪ1<=i<=L.length
	if((i<1)||(i>L.length))
		return ERROR; //iֵ���Ϸ�
	ElemType *InPosition=&L.elem[i-1]; //InPositionΪ��ɾ��Ԫ�ص�λ��
	e=*InPosition; //��ɾ��Ԫ��ֵ����e
	ElemType *EndPosition=L.elem+L.length-1; //��βԪ�ص�λ��
	for(++InPosition;InPosition<=EndPosition;++InPosition)
		*(InPosition-1)=*InPosition; //��ɾ��Ԫ��֮���Ԫ�����ƣ�
	--L.length;
	return OK;
}//ListDelete_Sq

//�Լ�ʵ�ֵ�
Status GetElem_Sq(SqList &L,int i,ElemType &e)
{
//��e����L�е�i������Ԫ�ص�ֵ
//i�ĺϷ�ֵΪ1<=i<=L.length
	if((i<1)||(i>L.length))
		return ERROR; //iֵ���Ϸ�
	e=L.elem[i-1];
	return OK;
}//GetElem_Sq

//�Լ�ʵ�ֵ�
Status DestroyList_Sq(SqList &L)
{
//�������Ա�L
	free(L.elem); //�ͷ������ڴ棻
	L.length=0; //����Ϊ0
	L.ListSize=0; //����Ĵ洢����Ϊ0
	return OK;
}//DestroyList_Sq

int LocateELem_Sq(SqList L,ElemType e,Status (* compare)(ElemType,ElemType))
{
//��˳�����Ա�L�в��ҵ�һ��ֵ��e����compare()��Ԫ��(compare����1)��λ��
//���ҵ����򷵻�����L�е�λ�򣬷��򷵻�0
	int i=1; //i�ĳ�ֵΪ��һ��Ԫ�صĴ洢λ��
	ElemType *p=L.elem; //p�ĳ�ֵΪ��һ��Ԫ�صĴ洢λ��
	while(i<=L.length && !compare(*p++,e))
		++i; //���Ҿ���λ��
	if(i<=L.length)
		return i; //����оͷ���λ��i
	else
		return 0; //���򷵻�0
}//LocateELem_Sq

//�Լ�ʵ�ֵ�
//����LocateELem_Sq������
Status equal(ElemType p1,ElemType p2)
{
//�Ƚ�����Ԫ�ص�ֵ ����Ⱦͷ���1�����򷵻�0
	if(p1==p2)
		return 1;
	return 0;
}//equal

//�Լ�ʵ�ֵ�
void UnionList_Sq(SqList &La,SqList Lb)
{
//�����������Ա�Lb���������Ա�La�е�����Ԫ�ز��뵽La��
	int La_len=La.length,Lb_len=Lb.length; //�����Ա�ĳ���
	ElemType e; //��ʱ���������
	for(int i=1;i<=Lb_len;++i)
	{
		GetElem_Sq(Lb,i,e); //ȡLb�е�i������Ԫ�ظ���e
		if(!LocateELem_Sq(La,e,equal))
			ListInsert_Sq(La,++La_len,e); //���La�в����ں�e��ͬ������Ԫ�أ������֮
	}
}//UnionList_Sq

void MergeList_Sq(SqList La,SqList Lb,SqList &Lc)
{
//��֪˳�����Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
//�鲢La��Lb�õ��µ�˳�����Ա�Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
//LcΪδ��ʼ����˳�����Ա�
	ElemType *pa=La.elem,*pb=Lb.elem;
	//��ʼ��Lc��СΪLa��LbԪ�صĺ�
	Lc.ListSize=Lc.length=La.length+Lb.length;
	ElemType *pc=Lc.elem=(ElemType *)malloc(Lc.ListSize*sizeof(ElemType));
	if(!Lc.elem)
		exit(OVERFLOW); //�洢����ʧ��
	//pa_last��pb_last Ϊ��Ӧ���Ա�����һ��Ԫ�ص�λ��
	ElemType *pa_last=La.elem+La.length-1;
	ElemType *pb_last=Lb.elem+Lb.length-1;
	while(pa<=pa_last&&pb<=pb_last)//�鲢����
	{
		if(*pa<=*pb)
			*pc++=*pa++;
		else
			*pc++=*pb++;
	}
	//��La��Lb��ʣ��δ�鲢 ��嵽Lcĩβ
	while(pa<=pa_last)
		*pc++=*pa++;
	while(pb<=pb_last)
		*pc++=*pb++;
}//MergeList_Sq

//main������������
int main()
{
	SqList l1,l2,l3;
	InitList_Sq(l1);
	InitList_Sq(l2);
	for(int i=1;i<=10;i++)
	{
		ListInsert_Sq(l1,i,i*2);
		ListInsert_Sq(l2,i,i*3);
	}
	ElemType e;
	for(int i=10;i>0;--i)
	{
		//GetElem_Sq(l1,i,e);
		//ListDelete_Sq(l1,i,e);
		//printf("%d ",e);
	}

	//UnionList_Sq(l1,l2);
	MergeList_Sq(l1,l2,l3);
	for(int i=1;i<l3.length;i++)
	{	
		GetElem_Sq(l3,i,e);
		printf("%d ",e);
	}
	//printf("\n %d \n",LocateELem_Sq(l1,10,equal));
	DestroyList_Sq(l1);
	DestroyList_Sq(l2);
	
	return 0;
}

	
	
