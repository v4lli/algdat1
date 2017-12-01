#include <cstdio>
#include "Trie.h"

int main(void) {
	auto t = Trie<char*>();

	printf("t.empty()=%d\n", t.empty());

	t.insert(std::make_pair("kuh", "muh"));
	return 0;
}
