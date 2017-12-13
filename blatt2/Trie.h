#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <map>
#include <cassert>
#include <typeinfo>

using namespace std;

#define TERMINAL 0xff

template <class T, class E=char>
class Trie
{
protected:
	class Node
	{
	public:
		Node(E my_id, Node *my_parent): id(my_id), parent(my_parent) {};
		~Node() {};
		virtual void print(int depth) = 0;
		E getId(){return id;};
		virtual void clear() = 0;
		Node *get_parent() const {
			return parent;
		}
	protected:
		E id;
	private:
		Node *parent;
	};

	class Leaf : public Node
	{
	public:
		Leaf(T param, Node *my_parent) : Node(TERMINAL, my_parent) {
			// XXX sollte evtl reference sein?
			value = param;
		}

		void print(int depth){
			printf("%*s", depth * 2, "");
			// XXX Wert mit ausgeben... %s evtl falsch, lieber mit << >>
			printf("\"%s\" (this=%p p=%p)\n", value.c_str(), this, Node::get_parent());
		}

		T& get() {
			return value;
		}

		void clear()
		{
			// XXX evtl. value löschen.
			//delete value;
		}

		// return pointer to next leaf, or NULL if last element
		Leaf* find_next() const {
			// find the fist node of the next branch of the tree
			// (will be in next).
			Node *next = NULL;
			// 1.) go up by one
			InnerNode *parent = (InnerNode*)Node::get_parent();

#ifdef DEBUG
			printf("%s: %p: find_next()\n", __func__, this);
#endif

			InnerNode *search_from = (InnerNode*)this;

			while (1) {
#ifdef DEBUG
				printf("%s: %p: next=%p\t parent=%p\n", __func__, this, next, parent);
#endif

				// 2a) (!= null) get next branch and be happy
				next = parent->next_or_null(search_from);
				if (next != NULL)
					break;

				// 2b) (== null) go up one more parent and just get the first element
				search_from = parent;
				// XXX remove null logic from next_or_null()
				parent = (InnerNode*)parent->get_parent();

				if (parent == NULL) {
					printf("parent==NULL\n");
					return NULL;
				}
			}

			// now check if this is a leaf, then we're done
			if (dynamic_cast<Leaf*>(next) == nullptr) {
				InnerNode *n = (InnerNode*)next;
				return (Leaf*)n->get_first_leaf();
			} else {
				return (Leaf*)next;
			}
		}
	private:
		T value;
	};

	class InnerNode : public Node
	{
	public:
		InnerNode(E my_id, Node *my_parent) : Node(my_id, my_parent) {};
		// XXX: Destruktoren klären.
		~InnerNode() {};
		void print(int depth){
			if (depth > 0)
				printf("%*s⌙", depth * 2 - 1, "");
			printf("%c (this=%p parent=%p):\n", Node::id == 0 ? 'R' : Node::id, this, Node::get_parent());
			for(auto itr = children.begin(); itr != children.end(); ++itr)
			{
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
				}
				// Geht schneller als einzelne Elemente mit erase entfernen.
				children.clear();
			}
			// XXX Evtl. map noch löschen.
			//delete children;
		};

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
				children.insert(std::make_pair(part, new InnerNode(part, this)));
			}
			// XXX unschoen... dynamic_cast
			return (InnerNode*)children[part];
		}

		bool has_children() const {
			return !children.empty();
		}

		InnerNode* get_first_leaf() const {
			auto n = (*(children.begin())).second;
			if (dynamic_cast<Leaf*>(n) == nullptr) {
#ifdef DEBUG
				printf("%s: n is not a leaf (%s), calling %p->get_first_leaf()\n", __func__, typeid(n).name(), n);
#endif
				// not a leaf
				return ((InnerNode*)n)->get_first_leaf();
			} else {
#ifdef DEBUG
				printf("%s: a leaf, returning %p\n", __func__, n);
#endif
				return (InnerNode*)n;
			}
			// assert map not empty
		}
	private:
		map<E, Node*> children;		// evtl. auch austauschen in Sortierte Liste.
	};

public:
	Trie() {};
	typedef basic_string<E> key_type;	// string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;

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
	public:
		TrieIterator(Leaf *start) : current(start) {}
		TrieIterator& operator++() {
			// preincrement
			if (current == NULL)
				throw std::logic_error("Increment iterator end\n");
			current = current->find_next();
			return *this;
		}
		TrieIterator operator++(int) {
			if (current == NULL)
				throw std::logic_error("Increment iterator end\n");
			// implement me
			return this;
		}
		bool operator==(TrieIterator other) const {
			// implement me
			return true;
		}

		bool operator!=(TrieIterator other) const {
			// implement me
			return false;
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
		return *(new iterator(new_leaf));
	}

	void erase(const key_type& value){
		// XXX Ablauf:
		// 1. Blatt finden (hier lohnt sich find())
		// 2. Blatt löschen
		// 3. für alle Eltern-Knoten (von unten nach oben):
		//	  wenn ihr letztes Kind gelöscht wurde, auch den Eltern-Knoten löschen
		// Evtl: Den Eltern-Knoten suchen (vom Blatt aus),
		//		 der mehr als ein Kind hat und dort den
		//		 entsprechenden Teilbaum mit clear löschen.
	}

	void clear() { // erase all
		root_node.clear();
	}

	void print() {
		root_node.print(0);
	}

//	iterator lower_bound(const key_type& testElement);	// first element >= testElement
//	iterator upper_bound(const key_type& testElement);	// first element > testElement
//	iterator find(const key_type& testElement);			// first element == testElement

	iterator begin() { // returns end() if not found
		if (!root_node.has_children()) {
			return end();
		}
		return *(new iterator((Leaf*)root_node.get_first_leaf()));
	}

	iterator end() {
		// XXX maybe don't allocate one on the heap
		return *(new iterator(NULL));
	}

private:
	InnerNode root_node = InnerNode(0, NULL);
};

#endif /* TRIE_H_ */
