#include"STACK.h"
extern const char* TestSTACK(int& s);
int main(void) {
	int s = 0;
	const char* e = TestSTACK(s);
	cout << e << '\n' << s << endl;
	return 0;
}