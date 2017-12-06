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
		//~Node();
		virtual void print(int depth) = 0;
		E getId(){return id;};
		virtual void clear() = 0;
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
		void clear()
		{
			// XXX evtl. value l�schen.
			delete value;
		};
	private:
		T value;
	};

	class InnerNode : public Node
	{
	public:
		InnerNode(E my_id) : Node(my_id) {};
		// XXX: Destruktoren kl�ren.
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
			// XXX Evtl. map noch l�schen.
			//delete children;
		};
		void attach(Node* child)
		{
			children.insert(make_pair(child->id, child));
		};
		bool has_children() const
		{
			return !children.empty();
		};
	private:
		map<E, Node*> children;		// evtl. auch austauschen in Sortierte Liste.
	};

public:
	typedef basic_string<E> key_type;	// string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
	//typedef ... iterator;	// ...: keine C/C++ Ellipse, sondern von Ihnen zu entwickeln�
	bool empty() const
	{
		return !rootNode.has_children();
	};
	//iterator insert(const value_type& value);
	//XXX muss iterator returnen
	void insert(const value_type& value);
	void erase(const key_type& value);
	void clear() // erase all
	{
		rootNode.clear();
	};
	void print()
	{
		rootNode.print();
	};
//	iterator lower_bound(const key_type& testElement);	// first element >= testElement
//	iterator upper_bound(const key_type& testElement);	// first element > testElement
//	iterator find(const key_type& testElement);			// first element == testElement
//	iterator begin();									// returns end() if not found
//	iterator end();

private:
	InnerNode rootNode = InnerNode(0);

public:
	Trie() {};

};

#endif /* TRIE_H_ */
