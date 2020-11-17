#include "../include/Queue.h"
#include<iostream>
using namespace std;
extern const char* TestQueue(int& s);
int main(void) {
	int s = 0;
	const char* e = TestQueue(s);
	cout << e << endl;
	cout << s << endl;
	return 0;
}