#include <cstdio>
#include "Trie.h"

int main(void) {
	auto t = Trie<string>();

	printf("t.empty()=%d\n", t.empty());

	t.insert(std::make_pair(string("kuh"), string("muh")));
	auto print_later = t.insert(std::make_pair(string("kuhl"), string("cool")));
	t.insert(std::make_pair(string("kuku"), string("🦉")));
	t.print();

	printf("t.empty()=%d\n", t.empty());
	printf("iterator deref for key 'kuhl': %s\n", (*print_later).c_str());

	//t.clear();

	return 0;
}
