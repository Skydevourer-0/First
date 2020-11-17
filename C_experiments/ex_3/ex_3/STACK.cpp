#include"STACK.h"

STACK::STACK(int m) :QUEUE(m), q(m) {};                  		//��ʼ��ջ�������2m-2��Ԫ��
STACK::STACK(const STACK& s) :QUEUE(s), q(s.q) {};         		//��ջs�����ʼ��ջ
STACK::STACK(STACK&& s)noexcept :QUEUE(move(s)), q(move(s.q)) {};     		//��ջs�ƶ�������ʼ��ջ
int  STACK::size()const noexcept {		  		//����ջ��������2m
	return  2 * q.QUEUE::size();
}
STACK::operator int() const noexcept {	   		//����ջ��ʵ��Ԫ�ظ���
	return this->QUEUE::operator int() + q.QUEUE::operator int();
}
STACK& STACK::operator<<(int e) {	     		//��e��ջ�������ص�ǰջ
	try {
		this->QUEUE::operator<<(e);
	}
	catch(...){									//�������������������е���һ��Ԫ������q�������ٽ��в���
		if (q.QUEUE::operator int() == q.QUEUE::size()-1) {//��q��������ջ�������׳�������Ϣ
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
STACK& STACK::operator>>(int& e) {     		//��ջ��e�������ص�ǰջ
	int n = operator int();
	int m = q.QUEUE::size();
	if (n == 0) throw("STACK is empty!");
	else if (n < m) {							//��ʱֻ�л����������Ԫ��
		for (n; n > 1; n--) {
			this->QUEUE::operator>>(e);
			this->QUEUE::operator<<(e);		//���������У��൱������ǰ��һλ
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
STACK& STACK::operator=(const STACK& s) {	//�����ֵ�����ر���ֵջ
	if (this == &s) return *this;
	this->QUEUE::operator=(s);
	q.QUEUE::operator=(s.q);
	return *this;
}
STACK& STACK::operator=(STACK&& s)noexcept {//�ƶ���ֵ�����ر���ֵջ
	if (this == &s) return *this;
	q.operator=(move(s.q));
	this->QUEUE::operator=(move(s));		//����move����������ֵת��Ϊ��ֵ
	return *this;
}
char* STACK::print(char* b)const noexcept {	//��ջ�׵�ջ����ӡջԪ�� 
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
STACK::~STACK()noexcept { }          	//����ջ