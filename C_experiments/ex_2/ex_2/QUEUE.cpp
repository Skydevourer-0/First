
#include "QUEUE.h"

QUEUE::QUEUE(int m) :max(m > 0?m:0), elems{m > 0? new int[m] :nullptr}{	//初始化队列：最多申请m个元素
    
    head = 0;
    tail = 0;
}

QUEUE::QUEUE(const QUEUE& s) :
    max(s.max > 0 ? s.max : 0), 
    elems{ s.max > 0 ? new int[s.max] : nullptr }{ 			//用s深拷贝初始化队列
    head = s.head;
    tail = s.tail;
    int** pelems = (int**)&elems;
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

QUEUE::QUEUE(QUEUE&& s) noexcept:
    max(s.max > 0 ? s.max : 0), 
    elems(s.elems){		//用s移动初始化队列
    head = s.head;
    tail = s.tail;
    
    *(int**)&(s.elems) = NULL;                            //将s.elems“清空”，实现s.elems中的数据移动到elems中
    s.head = 0;
    s.tail = 0;
    *(int*)&(s.max) = 0;
    return;
}


QUEUE::operator int() const noexcept {	//返回队列的实际元素个数
    if (head == tail) return 0;//队列为空
    if (head > tail) return tail + max - head; //处理成循环队列
    else return tail - head;
}
int QUEUE::size() const noexcept {		//返回队列申请的最大元素个数max
    return max;
}
QUEUE& QUEUE::operator<<(int e) {  	//将e入队列尾部，并返回当前队列
    if ((tail + 1) % max == head) {
        throw("QUEUE is full!");
        return *this;
    }
    (*(int**)&elems)[tail] = e;
    tail = (tail + 1) % max;
    return *this;
}
QUEUE& QUEUE::operator>>(int& e) { 	//从队首出元素到e，并返回当前队列
    if (head == tail) throw("QUEUE is empty!");
    else {
        int** pelems = (int**)&(elems);
        e = (*pelems)[head];
        head = (head + 1) % max;
    }
    return *this;
}
QUEUE& QUEUE::operator=(const QUEUE& s) {//深拷贝赋值并返回被赋值队列
    if (this == &s) return *this;
    int** pelems = (int**)&(elems);                   //定义一指针对elems进行操作
    if (elems) {
        free(*pelems);
        *pelems = NULL;
    }                                                   //若elems中有内容，则释放elems内存并将其指向空

    *pelems = new int[s.max];            //分配elems内存与s->elems相同
    if (s.head > s.tail) {
        for (int i = 0; i < s.tail; i++)
            (*pelems)[i] = s.elems[i];                       //逐一拷贝s.elems前半部分
        for (int i = s.head; i < s.max ; i++)
            (*pelems)[i] = s.elems[i];                       //逐一拷贝s.elems后半部分
    }                                                   //此时队列已开始循环
    else {
        for (int i = s.head; i < s.tail; i++)
            (*pelems)[i] = s.elems[i];                       //逐一拷贝s.elems中的内容至elems
    }
    *(int*)&(max) = s.max;
    head = s.head;
    tail = s.tail;
    return *this;
}
QUEUE& QUEUE::operator=(QUEUE&& s)noexcept {//移动赋值并返回被赋值队列
    if (elems != s.elems) {
        int** pelems = (int**)&(elems);                   //定义一指针对elems进行操作
        if (elems) {
            free(*pelems);
            *pelems = NULL;
        }                                                   //若elems中有内容，则释放elems内存并将其指向空

        *pelems = s.elems;                                    //浅拷贝s.elems至elems
        *(int**)&(s.elems) = NULL;                            //将s.elems指向空，实现数据的移动
        head = s.head;
        tail = s.tail;
        *(int*)&(max) = s.max;                             //将s中各种数据赋值给p
        s.head = 0;
        s.tail = 0;
        *(int*)&(s.max) = 0;								//将s中各种数据变为0，实现“清空”
    }
    return *this;
}
char* QUEUE::print(char* s) const noexcept {//打印队列至s并返回s
    int slen = 0;                                         //定义slen表示s的长度
    if (head < tail) {
        for (int i = head; i < tail; i++) {
            slen += sprintf(s + slen, "%d,", elems[i]);       //因为sprintf的返回值是输入的字符串的长度,故每次从s+slen开始输入新的数据恰好将上一回末尾的空字符覆盖
        }
    }                                                   //此时队列可处理成非循环队列
    else {
        for (int i = head; i < max; i++)
            slen += sprintf(s + slen, "%d,", elems[i]);       //先打印后半部分
        for (int i = 0; i < tail; i++)
            slen += sprintf(s + slen, "%d,", elems[i]);       //后打印前半部分
    }
    s[slen - 1] = '\0';                                     //将字符串末尾多余的空格改为空字符
    return s;
}
QUEUE::~QUEUE() {	 					//销毁当前队列
    if (elems) {
        delete elems;
        *(int**)&elems = NULL;
    }
    head = tail = 0;
    *(int*)&max = 0;
    return;
}
