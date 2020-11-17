#include"STACK.h"

STACK::STACK(int m) :QUEUE(m), q(m) {};                  		//初始化栈：最多存放2m-2个元素
STACK::STACK(const STACK& s) :QUEUE(s), q(s.q) {};         		//用栈s深拷贝初始化栈
STACK::STACK(STACK&& s)noexcept :QUEUE(move(s)), q(move(s.q)) {};     		//用栈s移动拷贝初始化栈
int  STACK::size()const noexcept {		  		//返回栈的容量即2m
	return  2 * q.QUEUE::size();
}
STACK::operator int() const noexcept {	   		//返回栈的实际元素个数
	return this->QUEUE::operator int() + q.QUEUE::operator int();
}
STACK& STACK::operator<<(int e) {	     		//将e入栈，并返回当前栈
	try {
		this->QUEUE::operator<<(e);
	}
	catch(...){									//若基类队列已满，则从中弹出一个元素填入q队列中再进行操作
		if (q.QUEUE::operator int() == q.QUEUE::size()-1) {//若q亦满，则栈已满，抛出错误信息
			throw("STACK is full!");
			return *this;
		}
		else {
			int te;
			this->QUEUE::operator>>(te);
			q.QUEUE::operator<<(te);
			this->operator<<(e);
		}
	}
	return *this;
}
STACK& STACK::operator>>(int& e) {     		//出栈到e，并返回当前栈
	int n = operator int();
	int m = q.QUEUE::size();
	if (n == 0) throw("STACK is empty!");
	else if (n < m) {							//此时只有基类队列中有元素
		for (n; n > 1; n--) {
			this->QUEUE::operator>>(e);
			this->QUEUE::operator<<(e);		//出列再入列，相当于整体前移一位
		}
		this->QUEUE::operator>>(e);
	}
	else {
		for (n; n > 1; n--) {
			q.QUEUE::operator>>(e);
			this->operator<<(e);
		}
		q.QUEUE::operator>>(e);
	}
	return *this;
}
STACK& STACK::operator=(const STACK& s) {	//深拷贝赋值并返回被赋值栈
	if (this == &s) return *this;
	this->QUEUE::operator=(s);
	q.QUEUE::operator=(s.q);
	return *this;
}
STACK& STACK::operator=(STACK&& s)noexcept {//移动赋值并返回被赋值栈
	if (this == &s) return *this;
	q.operator=(move(s.q));
	this->QUEUE::operator=(move(s));		//调用move函数，将左值转化为右值
	return *this;
}
char* STACK::print(char* b)const noexcept {	//从栈底到栈顶打印栈元素 
	char* s1 = q.QUEUE::print(b);
	if (strlen(s1)!=0) {
		char* temp = new char[strlen(s1) + 2];
		strncpy(temp, s1, strlen(s1) + 1);
		temp[strlen(s1)] = ',';
		temp[strlen(s1) + 1] = '\0';
		char* s2 = this->QUEUE::print(b);
		strncat(temp, s2, strlen(s2) + 1);
		strncpy(b, temp, strlen(temp) + 1);
	}
	else {
		char* s2 = this->QUEUE::print(b);
		strncpy(b, s2, strlen(s2) + 1);
	}
	return b;
}
STACK::~STACK()noexcept { }          	//销毁栈