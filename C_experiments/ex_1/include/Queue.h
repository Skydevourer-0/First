#pragma once
#pragma comment (lib,"../include/TestQueue.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int* const elems;                                   /*elems�����ڴ����ڴ�Ŷ��е�Ԫ��*/
	const int max;	                                  /*elems��������Ԫ�ظ���max*/
	int head, tail;										/*����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0*/
} Queue;

void initQueue(Queue* const p, int m)                   //��ʼ��pָ���У��������m��Ԫ��
{
	p->head = 0;
	p->tail = 0;
	*(int*)&p->max = m;                                 //��ȡp->max�ĵ�ַ������ǿ������ת��Ϊ int* ���ͣ���ȡֵ���в����ı�p-max��ֵ
	*(int**)&(p->elems) = (int*)malloc(sizeof(int) * m);//ԭ��ͬp->max�ĸ�ֵ
	return;
}

void initQueue(Queue* const p, const Queue& s)          //��s�����ʼ��pָ����
{
	p->head = s.head;
	p->tail = s.tail;
	*(int*)&(p->max) = s.max;                          //����s.max
	int** pelems = (int**)&(p->elems);
	*pelems = (int*)malloc(sizeof(int) * s.max);
	if (s.head > s.tail) {
		for (int i = s.head; i < s.max; i++)
			(*pelems)[i] = s.elems[i];                       //��һ����s.elems��벿������
		for (int i = 0; i < s.tail; i++)
			(*pelems)[i] = s.elems[i];                       //��һ����s.elemsǰ�벿������
	}                                                   //��s.head��s.tail֮������д����ѭ������
	else {
		for (int i = s.head; i < s.tail; i++)
			(*pelems)[i] = s.elems[i];                     //��һ����s.elems�е����ݣ�*�����ȶȽ�[]�ͣ�������ţ�
	}
}

void initQueue(Queue* const p, Queue&& s)               //��s�ƶ���ʼ��pָ���У����ݵĲ���s����ֵ���ã����ú���ʱӦ��ʱ���������������� Queue{t,10,0,0}
{
	p->head = s.head;
	p->tail = s.tail;
	*(int*)&(p->max) = s.max;
	*(int**)&(p->elems) = s.elems;                       //ǳ����s.elems��*p->elems
	*(int**)&(s.elems) = NULL;                            //��s.elems����ա���ʵ��s.elems�е������ƶ���p->elems��
	s.head = 0;
	s.tail = 0;
	*(int*)&(s.max) = 0;
	return;
}

int number(const Queue* const p)                        //����pָ���е�ʵ��Ԫ�ظ���
{
	if (p->head == p->tail) return 0;//����Ϊ��
	if (p->head > p->tail) return p->tail + p->max - p->head; //�����ѭ������
	else return p->tail - p->head;
}
int size(const Queue* const p) { return p->max; }		    //����pָ������������Ԫ�ظ���max

Queue* const enter(Queue* const p, int e)		          //��e�����β����������p
{
	int** pelems = (int**)&(p->elems);                   //Ҫ��p->elems���в���������һ��ָ��
	if ((p->tail + 1) % p->max == p->head) {                    //��ʱ����p�Ѿ�������Ӧ����洢�ռ������չ
		throw("Queue is full!");
		return p;
	}                                  
	(*pelems)[p->tail] = e;						//����δ������ֱ����ԭ����βλ�ò���e
	p->tail = (p->tail + 1) % p->max;                         //βλ�ú���
	return p;
}

Queue* const leave(Queue* const p, int& e)		           //�Ӷ��׳�Ԫ�ص�e��������p
{
	if (p->head == p->tail) throw("Queue is empty!");
	else {
		int** pelems = (int**)&(p->elems);                   //������ָ�����Ըı�p->elems
		e = (*pelems)[p->head];                               //������Ԫ��
		p->head = (p->head + 1) % p->max;                     //��p->head����һλ
	}
	return p;
}

Queue* const assign(Queue* const p, const Queue& s)     //�����s�����в�����p
{
	if (p == &s) return p;
	int** pelems = (int**)&(p->elems);                   //����һָ���p->elems���в���
	if (p->elems) {
		free(*pelems);
		*pelems = NULL;
	}                                                   //��p->elems�������ݣ����ͷ�p->elems�ڴ沢����ָ���

	*pelems = (int*)malloc(sizeof(int) * s.max - 1);            //����p->elems�ڴ���s->elems��ͬ
	if (s.head > s.tail) {
		for (int i = 0; i < s.tail; i++)
			(*pelems)[i] = s.elems[i];                       //��һ����s.elemsǰ�벿��
		for (int i = s.head; i < s.max - 1; i++)
			(*pelems)[i] = s.elems[i];                       //��һ����s.elems��벿��
	}                                                   //��ʱ�����ѿ�ʼѭ��
	else {
		for (int i = s.head; i < s.tail; i++)
			(*pelems)[i] = s.elems[i];                       //��һ����s.elems�е�������p->elems
	}
	*(int*)&(p->max) = s.max;
	p->head = s.head;
	p->tail = s.tail;
	return p;
}

Queue* const assign(Queue* const p, Queue&& s)		       //�ƶ���s�����в�����p
{
	if (p->elems != s.elems) {
		int** pelems = (int**)&(p->elems);                   //����һָ���p->elems���в���
		if (p->elems) {
			free(*pelems);
			*pelems = NULL;
		}                                                   //��p->elems�������ݣ����ͷ�p->elems�ڴ沢����ָ���

		*pelems = s.elems;                                    //ǳ����s.elems��p->elems
		*(int**)&(s.elems) = NULL;                            //��s.elemsָ��գ�ʵ�����ݵ��ƶ�
		p->head = s.head;
		p->tail = s.tail;
		*(int*)&(p->max) = s.max;                             //��s�и������ݸ�ֵ��p
		s.head = 0;
		s.tail = 0;
		*(int*)&(s.max) = 0;								//��s�и������ݱ�Ϊ0��ʵ�֡���ա�
	}
	return p;
}

char* print(const Queue* const p, char* s)			       //��ӡpָ������s������s
{
	int slen = 0;                                         //����slen��ʾs�ĳ���
	if (p->head < p->tail) {
		for (int i = p->head; i < p->tail; i++) {
			slen += sprintf(s + slen, "%d,", p->elems[i]);       //��Ϊsprintf�ķ���ֵ��������ַ����ĳ���,��ÿ�δ�s+slen��ʼ�����µ�����ǡ�ý���һ��ĩβ�Ŀ��ַ�����
		}
	}                                                   //��ʱ���пɴ���ɷ�ѭ������
	else {
		for (int i = p->head; i < p->max; i++)
			slen += sprintf(s + slen, "%d,", p->elems[i]);       //�ȴ�ӡ��벿��
		for (int i = 0; i < p->tail; i++)
			slen += sprintf(s + slen, "%d,", p->elems[i]);       //���ӡǰ�벿��
	}
	s[slen - 1] = '\0';                                     //���ַ���ĩβ����Ŀո��Ϊ���ַ�
	return s;
}

void destroyQueue(Queue* const p)					          //����pָ��Ķ���
{
	int** pelems = (int**)&(p->elems);
	free(*pelems);
	*pelems = NULL;                                       //�ͷ�p->elems�Ŀռ�
	p->head = 0;
	p->tail = 0;
	*(int*)&p->max = 0;
	return;
}
