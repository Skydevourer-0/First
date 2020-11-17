#include "QUEUE.h"
#pragma comment(lib,"E:\\Projects\\MY\\C_experiments\\Test\\Test_2\\TestQUEUE.lib")
extern const char* TestQUEUE(int& s);
int main(void) {
	int s = 0;
	const char* e = TestQUEUE(s);
	cout << e << endl;
	cout << s << endl;
	return 0;
}