
#include "QUEUE.h"

QUEUE::QUEUE(int m) :max(m > 0?m:0), elems{m > 0? new int[m] :nullptr}{	//��ʼ�����У��������m��Ԫ��
    
    head = 0;
    tail = 0;
}

QUEUE::QUEUE(const QUEUE& s) :
    max(s.max > 0 ? s.max : 0), 
    elems{ s.max > 0 ? new int[s.max] : nullptr }{ 			//��s�����ʼ������
    head = s.head;
    tail = s.tail;
    int** pelems = (int**)&elems;
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

QUEUE::QUEUE(QUEUE&& s) noexcept:
    max(s.max > 0 ? s.max : 0), 
    elems(s.elems){		//��s�ƶ���ʼ������
    head = s.head;
    tail = s.tail;
    
    *(int**)&(s.elems) = NULL;                            //��s.elems����ա���ʵ��s.elems�е������ƶ���elems��
    s.head = 0;
    s.tail = 0;
    *(int*)&(s.max) = 0;
    return;
}


QUEUE::operator int() const noexcept {	//���ض��е�ʵ��Ԫ�ظ���
    if (head == tail) return 0;//����Ϊ��
    if (head > tail) return tail + max - head; //�����ѭ������
    else return tail - head;
}
int QUEUE::size() const noexcept {		//���ض�����������Ԫ�ظ���max
    return max;
}
QUEUE& QUEUE::operator<<(int e) {  	//��e�����β���������ص�ǰ����
    if ((tail + 1) % max == head) {
        throw("QUEUE is full!");
        return *this;
    }
    (*(int**)&elems)[tail] = e;
    tail = (tail + 1) % max;
    return *this;
}
QUEUE& QUEUE::operator>>(int& e) { 	//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
    if (head == tail) throw("QUEUE is empty!");
    else {
        int** pelems = (int**)&(elems);
        e = (*pelems)[head];
        head = (head + 1) % max;
    }
    return *this;
}
QUEUE& QUEUE::operator=(const QUEUE& s) {//�����ֵ�����ر���ֵ����
    if (this == &s) return *this;
    int** pelems = (int**)&(elems);                   //����һָ���elems���в���
    if (elems) {
        free(*pelems);
        *pelems = NULL;
    }                                                   //��elems�������ݣ����ͷ�elems�ڴ沢����ָ���

    *pelems = new int[s.max];            //����elems�ڴ���s->elems��ͬ
    if (s.head > s.tail) {
        for (int i = 0; i < s.tail; i++)
            (*pelems)[i] = s.elems[i];                       //��һ����s.elemsǰ�벿��
        for (int i = s.head; i < s.max ; i++)
            (*pelems)[i] = s.elems[i];                       //��һ����s.elems��벿��
    }                                                   //��ʱ�����ѿ�ʼѭ��
    else {
        for (int i = s.head; i < s.tail; i++)
            (*pelems)[i] = s.elems[i];                       //��һ����s.elems�е�������elems
    }
    *(int*)&(max) = s.max;
    head = s.head;
    tail = s.tail;
    return *this;
}
QUEUE& QUEUE::operator=(QUEUE&& s)noexcept {//�ƶ���ֵ�����ر���ֵ����
    if (elems != s.elems) {
        int** pelems = (int**)&(elems);                   //����һָ���elems���в���
        if (elems) {
            free(*pelems);
            *pelems = NULL;
        }                                                   //��elems�������ݣ����ͷ�elems�ڴ沢����ָ���

        *pelems = s.elems;                                    //ǳ����s.elems��elems
        *(int**)&(s.elems) = NULL;                            //��s.elemsָ��գ�ʵ�����ݵ��ƶ�
        head = s.head;
        tail = s.tail;
        *(int*)&(max) = s.max;                             //��s�и������ݸ�ֵ��p
        s.head = 0;
        s.tail = 0;
        *(int*)&(s.max) = 0;								//��s�и������ݱ�Ϊ0��ʵ�֡���ա�
    }
    return *this;
}
char* QUEUE::print(char* s) const noexcept {//��ӡ������s������s
    int slen = 0;                                         //����slen��ʾs�ĳ���
    if (head < tail) {
        for (int i = head; i < tail; i++) {
            slen += sprintf(s + slen, "%d,", elems[i]);       //��Ϊsprintf�ķ���ֵ��������ַ����ĳ���,��ÿ�δ�s+slen��ʼ�����µ�����ǡ�ý���һ��ĩβ�Ŀ��ַ�����
        }
    }                                                   //��ʱ���пɴ���ɷ�ѭ������
    else {
        for (int i = head; i < max; i++)
            slen += sprintf(s + slen, "%d,", elems[i]);       //�ȴ�ӡ��벿��
        for (int i = 0; i < tail; i++)
            slen += sprintf(s + slen, "%d,", elems[i]);       //���ӡǰ�벿��
    }
    s[slen - 1] = '\0';                                     //���ַ���ĩβ����Ŀո��Ϊ���ַ�
    return s;
}
QUEUE::~QUEUE() {	 					//���ٵ�ǰ����
    if (elems) {
        delete elems;
        *(int**)&elems = NULL;
    }
    head = tail = 0;
    *(int*)&max = 0;
    return;
}
