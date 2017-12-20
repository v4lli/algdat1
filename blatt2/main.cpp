#include <cstdio>
#include "Trie.h"

#define DUMP() {\
	printf("############### DUMP BGN ###############\n"); \
	for (auto it=t.begin(); it != t.end(); ++it) \
		printf("%s, ", (*it).c_str()); \
	printf("\n############### DUMP END ###############\n"); \
}

Trie<string, char> trie = new Trie<string, char>();

void test(void)
{
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

	//DUMP();

	auto found = t.find(string("kuhl"));
	auto found2 = t.find(string("xuxu"));

	printf("t.find('kuhl') = '%s'\n", (*found).c_str());
	printf("t.find('xuxu') = '%s'\n", (*found2).c_str());

	t.clear();
}

void insertElement(void)
{
	printf("Element angeben in der Form:\n");
	printf("Key Value\n");
	string key_value;
	cin >> key_value;
	string::size_type found = key_value.find(" ");
	if(found != string::npos)
	{
		string key = key_value.substr(0, found);
		string value = key_value.substr(found + 1, string::npos);
		trie.insert(std::make_pair(key, value));
		printf("Erfolgreich eingefügt\n");
	}
	else
	{
		printf("Eingabe war nicht in der Form: Key Value");
	}
}

void findElement(void)
{
	if(trie.empty())
	{
		printf("In einem leeren Trie kann nicht gesucht werden.\n");
		return;
	}
	printf("Nach welchem Key wollen Sie suchen?\n");
	string key;
	cin << key;
	auto found = trie.find(key);
	if(found == trie.end())
	{
		printf("Der Key wurde nicht gefunden.\n");
	}
	else
	{
		cout << "Gefunden: " << (*found) << endl;
	}
}

void deleteElement(void)
{
	if(trie.empty())
	{
		printf("Aus einem leeren Trie kann nichts geloescht werden.\n");
		return;
	}
	printf("Welchen Key wollen Sie loeschen?\n");
	string key;
	cin << key;
	trie.erase(key);
}

void findLowerBound(void)
{
	if(trie.empty())
	{
		printf("In einem leeren Trie kann nicht gesucht werden.\n");
		return;
	}
	printf("Nach welchem Key wollen Sie suchen?\n");
	string key;
	cin << key;
	auto found = trie.lower_bound(key);
	if(found == trie.end())
	{
		printf("Der Key wurde nicht gefunden.\n");
	}
	else
	{
		cout << "Gefunden: " << (*found) << endl;
	}
}

void findUpperBound(void)
{
	if(trie.empty())
	{
		printf("In einem leeren Trie kann nicht gesucht werden.\n");
		return;
	}
	printf("Nach welchem Key wollen Sie suchen?\n");
	string key;
	cin << key;
	auto found = trie.upper_bound(key);
	if(found == trie.end())
	{
		printf("Der Key wurde nicht gefunden.\n");
	}
	else
	{
		cout << "Gefunden: " << (*found) << endl;
	}
}

void menu(void)
{
	bool run = true;
	while(run)
	{
		// Menü anzeigen.
		printf("Was wollen Sie tun?\n");
		printf("i -> Eingabe von Elementen\n");
		printf("f -> Suche nach Element\n");
		printf("d -> Ein Element loeschen\n");
		printf("c -> Alle Elemente loeschen\n");
		printf("p -> Alle Elemente ausgeben\n");
		printf("e -> Ist der Trie leer?\n");
		printf("l -> Finde LowerBound\n");
		printf("u -> Finde UpperBound\n");
		printf("q -> Programm beenden\n");

		// Eingabe lesen.
		char c = 0;
		cin >> c;
		switch(c)
		{
			case 'i':	// Eingabe von Blättern
			case 'I':
				insertElement();
				break;
			case 'f':	// Element suchen.
			case 'F':
				findElement();
				break;
			case 'd':	// Element löschen.
			case 'D':
				deleteElement();
				break;
			case 'c':	// Trie leeren.
			case 'C':
				trie.clear();
				break;
			case 'p':	// Trie ausgeben.
			case 'P':
				trie.print();
				break;
			case 'e':	// Ist der Trie leer?
			case 'E':
				cout << trie.empty();
				break;
			case 'l':	// LowerBound ausgeben.
			case 'L':
				findLowerBound();
				break;
			case 'u':	// UpperBound ausgeben.
			case 'U':
				findUpperBound();
				break;
			case 'q':	// Programm beenden.
			case 'Q':
				run = false;
				break;
			default:	// Falsche Eingabe.
				break;
		}
	}
}

int main(void) {
	test();
	//menu();

	return 0;
}
