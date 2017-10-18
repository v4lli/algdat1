#include <cstdio>
#include "CursorList.h"

#define DUMP() {\
	printf("############### DUMP BGN ###############\n"); \
	printf("# lst.empty() = %d\n", lst.empty()); \
	printf("# lst.size() = %d\n# Content: ", lst.size()); \
	for (CursorIterator<int> it=lst.begin(); it != lst.end(); it++) \
		printf("%d, ", *it); \
	printf("\n############### DUMP END ###############\n"); \
}
//printf("lst.front() = %d\n", lst.front());\

int main(void) {
	auto lst = List<int, 128>();

	//DUMP();
	printf("push_front()\n");
	lst.push_front(1);
	printf("push_front()\n");
	lst.push_front(2);
	printf("push_front()\n");
	lst.push_front(3);
	DUMP();
	printf("pop_front()\n");
	lst.pop_front();
	DUMP();
	printf("pop_front()\n");
	lst.pop_front();
	printf("pop_front()\n");
	lst.pop_front();
	DUMP();

	return 0;
}
