#include <cstdio>
#include "Trie.h"

int main(void) {
	auto t = Trie<string>();

	printf("t.empty()=%d\n", t.empty());

	auto print_later_kuh = t.insert(std::make_pair(string("kuh"), string("muh")));
	auto print_later = t.insert(std::make_pair(string("kuhl"), string("cool")));
	auto print_later_test = print_later;
	auto kuku = t.insert(std::make_pair(string("kuku"), string("🦉")));
	auto new_branch = t.insert(std::make_pair(string("xuxu"), string("🤬")));
	t.print();

	printf("t.empty()=%d\n", t.empty());
	printf("iterator deref for key 'kuhl': %s\n", (*print_later).c_str());
	printf("iterator++ deref for key 'kuhl': %s\n", (*(++print_later)).c_str());
	printf("iterator++ deref for key 'kuh': %s\n", (*(++print_later_kuh)).c_str());
	printf("begin() deref: %s\n", (*t.begin()).c_str());
	printf("iterator deref for key 'xuxu': %s\n", (*new_branch).c_str());
	printf("iterator++ for key 'kuku', should jump to 'xuxu' accross root node: %s\n", (*(++kuku)).c_str());
	printf("iterator++ for key 'kuhl', should still jump to 'kuku': %s\n", (*(++print_later_test)).c_str());

	t.clear();

	return 0;
}
