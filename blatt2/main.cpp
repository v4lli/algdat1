#include <cstdio>
#include "Trie.h"

int main(void) {
	auto t = Trie<string>();

	printf("t.empty()=%d\n", t.empty());

	t.insert(std::make_pair(string("kuh"), string("muh")));
	t.insert(std::make_pair(string("kuhl"), string("cool")));
	t.insert(std::make_pair(string("kuku"), string("🦉")));
	t.print();

	printf("t.empty()=%d\n", t.empty());
	t.clear();
	//printf("t.clear(); t.empty()=%d\n", t.empty());

	return 0;
}
