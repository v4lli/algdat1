#include <cstdio>
#include "CursorList.h"

#define DUMP() {\
	printf("lst.empty() = %d\n", lst.empty()); \
	printf("lst.size() = %d\n", lst.size()); \
	printf("lst.front() = %d\n", lst.front());\
}

int main(void) {
	auto lst = List<int, 128>();

	DUMP();

	return 0;
}
