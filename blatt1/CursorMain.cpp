#include <stdio.c>

#define DUMP() (\
	printf("lst.empty() = %b\n", lst.empty()); \
	printf("lst.size() = %b\n", lst.size()); \
	printf("lst.front() = %p\n", lst.front());)

int main(void) {
	auto lst = new CursorList<int>(128);

	DUMP();

	return 0;
}
