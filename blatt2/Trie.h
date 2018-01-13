// algorithmen und datenstrukturen, ws17/18, walter/dornauer
//
// https://github.com/v4lli/algdat1/tree/master/blatt2

#ifndef TRIE_H_
#define TRIE_H_

#include <cassert>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <typeinfo>

using namespace std;

#define TERMINAL 0xff

template <class T, class E=char>
class Trie
{
public:
	typedef basic_string<E> key_type;	// string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
protected:
	class Node {
	public:
		Node(E my_id, Node *my_parent): id(my_id), parent(my_parent) {};
		virtual ~Node() {};
		virtual void print(int depth) const = 0;

		E getId() const {
			return id;
		}

		virtual void clear() = 0;
		Node *get_parent() const {
			return parent;
		}
	protected:
		E id;
	private:
		Node *parent;
	};

	class Leaf : public Node {
	public:
		Leaf(T param, Node *my_parent) : Node(TERMINAL, my_parent) {
			value = param;
		}
		~Leaf() {};

		void print(int depth) const {
			printf("%*s", depth * 2, "");
			cout << "\"" << value << "\" (this=" << this
				 << "p=" << Node::get_parent() << endl;
		}

		T& get() {
			return value;
		}

		key_type get_key() const {
			std::list<char> keys;

			Node *parent = Node::get_parent();
			while (parent != NULL) {
				if (parent->getId() != 0)
					keys.push_back(parent->getId());
				parent = parent->get_parent();
			}

			char *out = new char[keys.size()+1];
			memset(out, 0, keys.size()+1);

			int i;
			auto rit = keys.rbegin();

			for (i = 0, rit = keys.rbegin(); rit != keys.rend(); ++rit, i++)
				out[i] = *rit;

			string ret(out);
			delete[] out;

			return ret;
		}

		// Nothing to do here, value is an object variable
		void clear() { }

		// return pointer to logical next leaf, or NULL if this is
		// the last element.
		Leaf* find_next() const {
			// find the fist node of the next branch of the tree
			// (will be in next after the while loop).
			Node *next = NULL;
			// 1.) go up by one
			InnerNode *parent = (InnerNode*)Node::get_parent();

#ifdef DEBUG
			printf("%s: %p: find_next()\n", __func__, this);
#endif

			InnerNode *search_from = (InnerNode*)this;

			while (1) {
#ifdef DEBUG
				printf("%s: %p: next=%p\t parent=%p\n",
				    __func__, this, next, parent);
#endif

				// 2a) (!= null) get next branch and be happy
				next = parent->next_or_null(search_from);
				if (next != NULL)
					break;

				// 2b) (== null) go up one more parent and just
				// get the first element
				search_from = parent;
				parent = dynamic_cast<InnerNode*>(parent->get_parent());

				// this means we tried to go up once more, but
				// were already at the root node -> no next
				// element.
				if (parent == NULL) {
#ifdef DEBUG
					printf("%s: parent==NULL\n", __func__);
#endif
					return NULL;
				}
			}

			// now check if 'next' is a leaf
			if (dynamic_cast<Leaf*>(next) == nullptr) {
				// It's not a leaf, we need to go down all the
				// way, always choosing the first branch option
				// at InnerNodes.
				return dynamic_cast<InnerNode*>(next)->get_first_leaf();
			} else {
				// we're done, 'next' is the next leaf
				return dynamic_cast<Leaf*>(next);
			}
		}
	private:
		T value;
	};

	class InnerNode : public Node {
	public:
		InnerNode(E my_id, Node *my_parent) : Node(my_id, my_parent) {};
		~InnerNode() {};
		void print(int depth) const {
			if (depth > 0)
				printf("%*s⌙", depth * 2 - 1, "");

			cout << (Node::id == 0 ? 'R' : Node::id) << " (this=" << this
				 << " parent=" << Node::get_parent() << endl;

			for(auto itr = children.begin(); itr != children.end(); ++itr) {
				(*(*itr).second).print(depth + 1);
			}
		}

		Node* next_or_null(InnerNode *element) {
			for(auto it = children.begin(); it != children.end(); ++it) {
#ifdef DEBUG
				printf("%s: %p: searching for %p <=> *it.second=%p\n", __func__, this, element, (*it).second);
#endif
				if ((*it).second == element) {
					it++;
					if (it == children.end()) {
#ifdef DEBUG
						printf("%s: next one is end...\n", __func__);
#endif
						return NULL;
					} else {
#ifdef DEBUG
						printf("%s: found next one @ %p\n", __func__, (*it).second);
#endif
						return (*it).second;
					}
				}
			}
			return NULL;
		}

		void clear()
		{
			if(has_children())
			{
				for(auto itr = children.begin(); itr != children.end(); ++itr)
				{
					(*itr).second->clear();
					delete (*itr).second;
				}
				// Geht schneller als einzelne Elemente mit erase entfernen.
				children.clear();
			}
		};

		void remove_child(E child_id)
		{
			children.erase(child_id);
		}

		void attach(Leaf* child)
		{
			children.insert(make_pair(TERMINAL, child));
		};

		// Returns a pointer to a node (and possibly creates it)
		InnerNode* get_reference_or_create(E part) {
			assert(part != TERMINAL);
			if (!children.count(part)) {
#ifdef DEBUG
				printf("create new\n");
#endif
				children.insert(std::make_pair(part,
				    new InnerNode(part, this)));
			}
			return dynamic_cast<InnerNode*>(children[part]);
		}

		bool has_children() const {
			return !children.empty();
		}

		Leaf* get_first_leaf() const {
			assert(children.size() > 0);
			auto n = (*(children.begin())).second;
			if (dynamic_cast<Leaf*>(n) == nullptr) {
#ifdef DEBUG
				printf("%s: n is not a leaf (%s), calling "
				    "%p->get_first_leaf()\n", __func__,
				    typeid(n).name(), n);
#endif
				// not a leaf
				return dynamic_cast<InnerNode*>(n)->get_first_leaf();
			} else {
#ifdef DEBUG
				printf("%s: a leaf, returning %p\n", __func__,
				    n);
#endif
				return dynamic_cast<Leaf*>(n);
			}
		}
	private:
		map<E, Node*> children;
	};

public:
	Trie() {};

	class TrieIterator : public	std::iterator<
				std::forward_iterator_tag,   // iterator_category
				T,                        // value_type
				int,                      // difference_type
				const T*,               // pointer
				T                       // reference
				>{
	private:
		// NULL means iterator is past the last element
		Leaf *current;
		// need parent trie association for compare
		Trie *trie;
	public:
		TrieIterator(Leaf *start, Trie *parent) : current(start), trie(parent) {}
		TrieIterator(TrieIterator *that) : current(that->get_current()), trie(that->get_parent()) {}

		Leaf *get_current() const {
			return current;
		}

		Trie *get_parent() const {
			return trie;
		}

		key_type get_key() {
			return current->get_key();
		}

		// preincrement
		TrieIterator& operator++() {
			if (current == NULL)
				throw std::logic_error("Increment iterator end\n");
			current = current->find_next();
			return *this;
		}

		// postincrement
		TrieIterator operator++(int) {
			TrieIterator clone(this);

			current = current->find_next();
			if (current == NULL)
				throw std::logic_error("Increment iterator end\n");

			return clone;
		}

		bool operator==(TrieIterator other) const {
			return (get_current() == other.get_current() &&
				get_parent() == other.get_parent());
		}

		bool operator!=(TrieIterator other) const {
			return (get_current() != other.get_current() ||
				get_parent() != other.get_parent());
		}

		T operator*() const {
			if (current == NULL)
				throw std::logic_error("Increment iterator end\n");
			return current->get();
		}
	};

	typedef TrieIterator iterator;

	bool empty() const {
		return !root_node.has_children();
	}

	iterator insert(const value_type& value) {
#ifdef DEBUG
		printf("Inserting value for key %s\n", value.first.c_str());
#endif
		InnerNode *n = &root_node;
#ifdef DEBUG
		printf("%s: root_node=%p\n", __func__, n);
#endif
		for (int i = 0; i < value.first.length(); i++) {
#ifdef DEBUG
			printf("Searching inner node for char '%c'\n", value.first[i]);
#endif
			n = n->get_reference_or_create(value.first[i]);
#ifdef DEBUG
			printf("%s: root_node=%p\n", __func__, n);
#endif
		}
		// We now have the InnerNode to attach the value (Leaf) to in n
		Leaf *new_leaf;
		n->attach(new_leaf = new Leaf(value.second, n));
		return iterator(new_leaf, this);
	}

	void erase(const key_type& value){
		// Das Kind finden, das zu löschen ist.
		auto it = find(value);
		if(it == end())
		{
			throw std::invalid_argument("Element not found.");
		}
		Leaf *current = it.get_current();
		// Id merken und Eltern-Knoten suchen.
		E id = current->getId();
		InnerNode* parent = (InnerNode*)(current->get_parent());
		// Das Kind im Eltern-Knoten löschen
		parent->remove_child(id);
		while (!parent->has_children())
		{
			// Wenn es das letzte Kind war, auch den Eltern-Knoten löschen.
			id = parent->getId();
			parent = (InnerNode*)(parent->get_parent());
			parent->remove_child(id);
		}

		delete current;

		// alternativ Evtl:
		//		Den Eltern-Knoten suchen (vom Blatt aus),
		//		der mehr als ein Kind hat und dort den
		//		entsprechenden Teilbaum mit clear löschen.
	}

	void clear() { // erase all
		root_node.clear();
	}

	void print() {
		root_node.print(0);
	}

	// first element >= testElement
	iterator lower_bound(const key_type& testElement){
		iterator it = begin();
		while(it != end() && it.get_key().compare(testElement) < 0)
		{
			it ++;
		}
		return it;
	}

	// first element > testElement
	iterator upper_bound(const key_type& testElement){
		iterator it = begin();
		while(it != end() && it.get_key().compare(testElement) <= 0)
		{
			it ++;
		}
		return it;
	}

	iterator find(const key_type &testElement) {			// first element == testElement
		auto it = begin();
		while (it != end() && it.get_key().compare(testElement) != 0) {
			it++;
		}
		return it;
	}

	iterator begin() { // returns end() if not found
		if (!root_node.has_children()) {
			return end();
		}
		return iterator((Leaf*)root_node.get_first_leaf(), this);
	}

	iterator end() {
		return iterator(NULL, this);
	}

private:
	InnerNode root_node = InnerNode(0, NULL);
};

#endif /* TRIE_H_ */
