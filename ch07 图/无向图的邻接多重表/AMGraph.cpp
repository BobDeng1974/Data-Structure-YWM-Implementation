/***************************************************************************
 *  @file       AMGraph.cpp
 *  @author     jz
 *  @date       22 Jan. 2016
 *  @remark     ���ݽṹ c���԰� ��ε�� ������
 *  @note	����ͼ���ڽӶ��ر�
 ***************************************************************************/
//ʵ����
#include<stdlib.h>
#include<stdio.h>
//#include<limits.h>
//#include<string.h>
//������

#include "DataStructure.h" //������Ҫ��һЩ����

typedef int VertexType; //������������
typedef char InfoType; //�������Ϣ����
#define MAX_VERTEX_NUM 20 //��󶥵����
enum VisitIf {unvisited,visited}; 
struct EBox
{
	VisitIf mark; //���ʱ��
	int ivex,jvex; //�ñ����������������λ��
	EBox *ilink,*jlink; //�ֱ��������������������һ����
	InfoType *info; //�ñ���Ϣָ��
};
struct VexBox
{
	VertexType data;
	EBox *firstedge; //��һ�������ڸö���ı�
};
struct AMGraph
{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum,edgenum; //����ͼ��ǰ�Ķ������ͱ���
};

//main������������
int main()
{
}
	

