#include <cstdio>
#include "CursorList.h"

#define DUMP() {\
	printf("############### DUMP BGN ###############\n"); \
	printf("# lst.empty() = %d\n", lst.empty()); \
	printf("# lst.size() = %d\n# ", lst.size()); \
	for (CursorIterator<int> it=lst.begin(); it != lst.end(); it++) \
		printf("%d, ", *it); \
	printf("############### DUMP END ###############\n"); \
}
//printf("lst.front() = %d\n", lst.front());\

int main(void) {
	auto lst = List<int, 128>();

	printf("YYYYYYYYYYYYY\n");
	CursorIterator<int> it=lst.begin();
	CursorIterator<int> it2=lst.begin();
	printf("XXXXXXXXXXXXXXXXXXXX=%d\n", it == it2);

	DUMP();
	printf("push_front()\n");
	lst.push_front(1337);
	printf("push_front()\n");
	lst.push_front(1337);
	DUMP();

	return 0;
}
