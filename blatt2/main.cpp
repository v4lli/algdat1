#include <cstdio>
#include "Trie.h"

int main(void) {
	auto t = Trie<string>();

	//printf("t.empty()=%d\n", t.empty());


	t.insert(std::make_pair(string("kuh"), string("muh")));
	t.print();
	return 0;
}
