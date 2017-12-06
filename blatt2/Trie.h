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
#include <cassert>
using namespace std;

#define TERMINAL 0xff

template <class T, class E=char>
class Trie
{
protected:
	class Node
	{
	public:
		Node(E my_id): id(my_id) { };
		~Node() {};
		virtual void print(int depth) = 0;
		E getId(){return id;};
		virtual void clear() = 0;
	protected:
		E id;
	};

	class Leaf : public Node
	{
	public:
		Leaf(T param) : Node(TERMINAL) {
			// XXX sollte evtl reference sein?
			value = param;
		}
		void print(int depth){
			printf("%*s", depth * 2, "");
			// XXX Wert mit ausgeben... %s evtl falsch, lieber mit << >>
			printf("%s\n", value.c_str());
		};
		T&  get() {
			return value;
		}
		void clear()
		{
			// XXX evtl. value löschen.
			//delete value;
		};
	private:
		T value;
	};

	class InnerNode : public Node
	{
	public:
		InnerNode(E my_id) : Node(my_id) {};
		// XXX: Destruktoren klären.
		~InnerNode() {};
		void print(int depth){
			printf("%*s", depth * 2, "");
			printf("%c:\n", Node::id);
			for(auto itr = children.begin(); itr != children.end(); ++itr)
			{
				(*(*itr).second).print(depth + 1);
			}
		};

		void clear()
		{
			if(has_children())
			{
				for(auto itr = children.begin(); itr != children.end();)
				{
					(*itr).second->clear();
					children.erase(itr);
				}
			}
			// XXX Evtl. map noch löschen.
			//delete children;
		};

		void attach(Leaf* child)
		{
			children.insert(make_pair(TERMINAL, child));
		};

		// Returns a pointer to a node (and possibly creates it)
		InnerNode& get_reference_or_create(E part) {
			assert(part != TERMINAL);
			if (!children.count(part)) {
				children.insert(std::make_pair(part, new InnerNode(part)));
			}
			// XXX unschoen... dynamic_cast
			return *((InnerNode*)children[part]);
		}

		bool has_children() const
		{
			return !children.empty();
		};
	private:
		map<E, Node*> children;		// evtl. auch austauschen in Sortierte Liste.
	};

public:
	Trie() {};
	typedef basic_string<E> key_type;	// string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
	//typedef ... iterator;	// ...: keine C/C++ Ellipse, sondern von Ihnen zu entwickeln…
	bool empty() const
	{
		return !root_node.has_children();
	};
	//iterator insert(const value_type& value);
	//XXX muss iterator returnen
	void insert(const value_type& value) {
		printf("Inserting value for key %s\n", value.first.c_str());
		InnerNode& n = root_node;
		for (int i = 0; i < value.first.length(); i++) {
			printf("Searching inner node for char '%c'\n", value.first[i]);
			n = n.get_reference_or_create(value.first[i]);
		}

		// We now have the InnerNode to attach the value (Leaf) to in n
		n.attach(new Leaf(value.second));
	}
	void erase(const key_type& value);
	void clear() // erase all
	{
		root_node.clear();
	};
	void print()
	{
		root_node.print();
	};
//	iterator lower_bound(const key_type& testElement);	// first element >= testElement
//	iterator upper_bound(const key_type& testElement);	// first element > testElement
//	iterator find(const key_type& testElement);			// first element == testElement
//	iterator begin();									// returns end() if not found
//	iterator end();

private:
	InnerNode root_node = InnerNode(0);
};

#endif /* TRIE_H_ */
