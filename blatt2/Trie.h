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
	class Node
	{
	public:
		Node(E my_id): id(my_id) { };
		~Node();
		virtual void print(int depth) = 0;
		E getId(){return id;};
	protected:
		E id;
	};

	class Leaf : public Node
	{
	public:
		void print(int depth){
			printf("%*s", depth * 2, "");
			// XXX Wert mit ausgeben...
			printf(value + "\n");
		};
	private:
		T value;
	};

	class InnerNode : public Node
	{
	public:
		void print(int depth){
			printf("%*s", depth * 2, "");
			printf("%c:\n", id);
			for(auto itr = children.begin(); itr != children.end(); ++itr)
			{
				(*itr).print(depth + 1);
			}
		};
		void attach(Node* child)
		{
			children.insert(make_pair(child->id, child));
		};
	private:
		map<E, Node*> children;		// evtl. auch austauschen in Sortierte Liste.
	};

public:
	typedef basic_string<E> key_type;	// string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
	//typedef ... iterator;	// ...: keine C/C++ Ellipse, sondern von Ihnen zu entwickeln…
	bool empty() const;
	//iterator insert(const value_type& value);
	void erase(const key_type& value);
	void clear(); // erase all
//	iterator lower_bound(const key_type& testElement);	// first element >= testElement
//	iterator upper_bound(const key_type& testElement);	// first element > testElement
//	iterator find(const key_type& testElement);			// first element == testElement
//	iterator begin();									// returns end() if not found
//	iterator end();
};

#endif /* TRIE_H_ */
