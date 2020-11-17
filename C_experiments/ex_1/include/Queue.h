#pragma once
#pragma comment (lib,"../include/TestQueue.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int* const elems;                                   /*elems申请内存用于存放队列的元素*/
	const int max;	                                  /*elems申请的最大元素个数max*/
	int head, tail;										/*队列头head和尾tail，队空head=tail;初始head=tail=0*/
} Queue;

void initQueue(Queue* const p, int m)                   //初始化p指队列：最多申请m个元素
{
	p->head = 0;
	p->tail = 0;
	*(int*)&p->max = m;                                 //获取p->max的地址，将其强制类型转化为 int* 类型，再取值进行操作改变p-max的值
	*(int**)&(p->elems) = (int*)malloc(sizeof(int) * m);//原理同p->max的赋值
	return;
}

void initQueue(Queue* const p, const Queue& s)          //用s深拷贝初始化p指队列
{
	p->head = s.head;
	p->tail = s.tail;
	*(int*)&(p->max) = s.max;                          //拷贝s.max
	int** pelems = (int**)&(p->elems);
	*pelems = (int*)malloc(sizeof(int) * s.max);
	if (s.head > s.tail) {
		for (int i = s.head; i < s.max; i++)
			(*pelems)[i] = s.elems[i];                       //逐一拷贝s.elems后半部分内容
		for (int i = 0; i < s.tail; i++)
			(*pelems)[i] = s.elems[i];                       //逐一拷贝s.elems前半部分内容
	}                                                   //若s.head在s.tail之后，则队列处理成循环队列
	else {
		for (int i = s.head; i < s.tail; i++)
			(*pelems)[i] = s.elems[i];                     //逐一拷贝s.elems中的内容（*的优先度较[]低，需加括号）
	}
}

void initQueue(Queue* const p, Queue&& s)               //用s移动初始化p指队列；传递的参数s是右值引用，调用函数时应临时构造匿名变量：如 Queue{t,10,0,0}
{
	p->head = s.head;
	p->tail = s.tail;
	*(int*)&(p->max) = s.max;
	*(int**)&(p->elems) = s.elems;                       //浅拷贝s.elems至*p->elems
	*(int**)&(s.elems) = NULL;                            //将s.elems“清空”，实现s.elems中的数据移动到p->elems中
	s.head = 0;
	s.tail = 0;
	*(int*)&(s.max) = 0;
	return;
}

int number(const Queue* const p)                        //返回p指队列的实际元素个数
{
	if (p->head == p->tail) return 0;//队列为空
	if (p->head > p->tail) return p->tail + p->max - p->head; //处理成循环队列
	else return p->tail - p->head;
}
int size(const Queue* const p) { return p->max; }		    //返回p指队列申请的最大元素个数max

Queue* const enter(Queue* const p, int e)		          //将e入队列尾部，并返回p
{
	int** pelems = (int**)&(p->elems);                   //要对p->elems进行操作，定义一新指针
	if ((p->tail + 1) % p->max == p->head) {                    //此时队列p已经存满，应对其存储空间进行扩展
		throw("Queue is full!");
		return p;
	}                                  
	(*pelems)[p->tail] = e;						//队列未存满，直接向原队列尾位置插入e
	p->tail = (p->tail + 1) % p->max;                         //尾位置后移
	return p;
}

Queue* const leave(Queue* const p, int& e)		           //从队首出元素到e，并返回p
{
	if (p->head == p->tail) throw("Queue is empty!");
	else {
		int** pelems = (int**)&(p->elems);                   //定义新指针用以改变p->elems
		e = (*pelems)[p->head];                               //弹出首元素
		p->head = (p->head + 1) % p->max;                     //将p->head后移一位
	}
	return p;
}

Queue* const assign(Queue* const p, const Queue& s)     //深拷贝赋s给队列并返回p
{
	if (p == &s) return p;
	int** pelems = (int**)&(p->elems);                   //定义一指针对p->elems进行操作
	if (p->elems) {
		free(*pelems);
		*pelems = NULL;
	}                                                   //若p->elems中有内容，则释放p->elems内存并将其指向空

	*pelems = (int*)malloc(sizeof(int) * s.max - 1);            //分配p->elems内存与s->elems相同
	if (s.head > s.tail) {
		for (int i = 0; i < s.tail; i++)
			(*pelems)[i] = s.elems[i];                       //逐一拷贝s.elems前半部分
		for (int i = s.head; i < s.max - 1; i++)
			(*pelems)[i] = s.elems[i];                       //逐一拷贝s.elems后半部分
	}                                                   //此时队列已开始循环
	else {
		for (int i = s.head; i < s.tail; i++)
			(*pelems)[i] = s.elems[i];                       //逐一拷贝s.elems中的内容至p->elems
	}
	*(int*)&(p->max) = s.max;
	p->head = s.head;
	p->tail = s.tail;
	return p;
}

Queue* const assign(Queue* const p, Queue&& s)		       //移动赋s给队列并返回p
{
	if (p->elems != s.elems) {
		int** pelems = (int**)&(p->elems);                   //定义一指针对p->elems进行操作
		if (p->elems) {
			free(*pelems);
			*pelems = NULL;
		}                                                   //若p->elems中有内容，则释放p->elems内存并将其指向空

		*pelems = s.elems;                                    //浅拷贝s.elems至p->elems
		*(int**)&(s.elems) = NULL;                            //将s.elems指向空，实现数据的移动
		p->head = s.head;
		p->tail = s.tail;
		*(int*)&(p->max) = s.max;                             //将s中各种数据赋值给p
		s.head = 0;
		s.tail = 0;
		*(int*)&(s.max) = 0;								//将s中各种数据变为0，实现“清空”
	}
	return p;
}

char* print(const Queue* const p, char* s)			       //打印p指队列至s并返回s
{
	int slen = 0;                                         //定义slen表示s的长度
	if (p->head < p->tail) {
		for (int i = p->head; i < p->tail; i++) {
			slen += sprintf(s + slen, "%d,", p->elems[i]);       //因为sprintf的返回值是输入的字符串的长度,故每次从s+slen开始输入新的数据恰好将上一回末尾的空字符覆盖
		}
	}                                                   //此时队列可处理成非循环队列
	else {
		for (int i = p->head; i < p->max; i++)
			slen += sprintf(s + slen, "%d,", p->elems[i]);       //先打印后半部分
		for (int i = 0; i < p->tail; i++)
			slen += sprintf(s + slen, "%d,", p->elems[i]);       //后打印前半部分
	}
	s[slen - 1] = '\0';                                     //将字符串末尾多余的空格改为空字符
	return s;
}

void destroyQueue(Queue* const p)					          //销毁p指向的队列
{
	int** pelems = (int**)&(p->elems);
	free(*pelems);
	*pelems = NULL;                                       //释放p->elems的空间
	p->head = 0;
	p->tail = 0;
	*(int*)&p->max = 0;
	return;
}
