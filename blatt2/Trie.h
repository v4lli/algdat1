/*
 * Trie.h
 *
 *  Created on: 29.11.2017
 *      Author: Angelika
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <map>
using namespace std;

template <class T, class E=char>
class Trie
{
	const uint8_t TERMINAL = 0xFF;

	class Node
	{
	public:
		Node(E my_id): id(my_id) { };
		~Node() {};
		virtual void print(int depth) = 0;
		E getId(){return id;};
	protected:
		E id;
	};

	class Leaf : public Node
	{
	public:
		Leaf(T param) {
			// XXX sollte evtl reference sein?
			value = param;
		}
		void print(int depth){
			printf("%*s", depth * 2, "");
			// XXX Wert mit ausgeben...
			printf(value + "\n");
		};
		T&  get() {
			return value;
		}
	private:
		T value;
	};

	class InnerNode : public Node
	{
	public:
		InnerNode(E my_id) : Node(my_id) {};
		~InnerNode() {};
		void print(int depth){
			printf("%*s", depth * 2, "");
			printf("%c:\n", Node::id);
			for(auto itr = children.begin(); itr != children.end(); ++itr)
			{
				(*(*itr).second).print(depth + 1);
			}
		};
		void attach(Leaf* child)
		{
			children.insert(make_pair(TERMINAL, child));
		};
		// Returns a pointer to a node (and possibly creates it)
		Node& get_reference_or_create(E part) {
			if (!children.count(part)) {
				children.insert(std::make_pair(part, new InnerNode()));
			}
			return *(children[part]);
		}
	private:
		map<E, Node*> children;		// evtl. auch austauschen in Sortierte Liste.
	};

public:
	Trie() {};
	typedef basic_string<E> key_type;	// string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
	//typedef ... iterator;	// ...: keine C/C++ Ellipse, sondern von Ihnen zu entwickeln…
	bool empty() const;
	//iterator insert(const value_type& value);
	//XXX muss iterator returnen
	void insert(const value_type& value) {
		printf("Inserting value for key %s\n", value.first.c_str());
		Node& n = root_node;
		for (int i = 0; i < value.first.length(); i++) {
			printf("Searching inner node for char '%c'\n", value.first[i]);
			n = get_reference_or_create(value.first[i]);
		}

		// We now have the InnerNode to attach the value (Leaf) to in n
		n.attach(new Leaf(value.second));
	}
	void erase(const key_type& value);
	void clear(); // erase all
//	iterator lower_bound(const key_type& testElement);	// first element >= testElement
//	iterator upper_bound(const key_type& testElement);	// first element > testElement
//	iterator find(const key_type& testElement);			// first element == testElement
//	iterator begin();									// returns end() if not found
//	iterator end();

private:
	InnerNode rootNode = InnerNode(0);
};

#endif /* TRIE_H_ */
