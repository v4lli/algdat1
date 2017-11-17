#include <cstdio>
#include "CursorList.h"

#define DUMP() {\
	printf("############### DUMP BGN ###############\n"); \
	printf("# lst.empty() = %d\n", lst.empty()); \
	printf("# lst.size() = %d\n# Content: ", lst.size()); \
	for (auto it=lst.begin(); it != lst.end(); ++it) \
		printf("%d, ", *it); \
	printf("\n############### DUMP END ###############\n"); \
}

int main(void) {
	auto lst = CursorList<int, 128>();

	// test push_front(), empty(), size() and pop_front(), iterator.begin()
	// iterator.end(), iterator* and iterator++
	DUMP();
	printf("push_front() 1\n");
	lst.push_front(1);
	printf("push_front() 2\n");
	lst.push_front(2);
	printf("push_front() 3\n");
	lst.push_front(3);
	// list should now be: 3, 2, 1
	DUMP();
	printf("pop_front()\n");
	lst.pop_front();
	DUMP();
	printf("pop_front()\n");
	lst.pop_front();
	printf("pop_front()\n");
	lst.pop_front();
	DUMP();
	printf("push_front([10, 20, 30, 40, 50])\n");
	lst.push_front(10);
	lst.push_front(20);
	lst.push_front(30);
	lst.push_front(40);
	lst.push_front(50);
	DUMP();
	auto ins = lst.begin();
	ins++;
	printf("insert at pos1\n");
	lst.insert(ins, 45);
	DUMP();
	printf("delete element 3-4 (only 40 b/c exclusive)\n");
	auto del = lst.begin();
	del++;
	del++;
	auto del_end = CursorList<int, 128>::CursorIterator(del);
	del_end++;
	lst.erase(del, del_end);
	DUMP();
	printf("delete all remaining elements\n");
	lst.erase(lst.begin(), lst.end());
	DUMP();
	lst.push_front(1);
	DUMP();
	printf("delete one element\n");
	lst.erase(lst.begin());
	DUMP();
	printf("\n\n");
	lst.front();

	// Test iterator copy constructor
	CursorList<int, 128>::CursorIterator it=lst.begin();
	CursorList<int, 128>::CursorIterator it2(it);
	CursorList<int, 128>::CursorIterator it_end=lst.end();
	CursorList<int, 128>::CursorIterator it2_end(it_end);
	printf("it==it2: %d (should be 1)\n", it == it2);
	printf("it2_end==it: %d (should be 0)\n", it2_end == it);

	return 0;
}
