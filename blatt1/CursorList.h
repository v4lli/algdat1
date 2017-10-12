#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag

template <class T> class CursorIterator : public std::iterator<std::input_iterator_tag, int>
{
private:
	int* p;
public:

	CursorIterator(int* x) :p(x) {}
	CursorIterator(const CursorIterator<T>& mit) : p(mit.p) {}
	CursorIterator& operator++() {++p;return *this;}
	CursorIterator operator++(int) {CursorIterator tmp(*this); operator++(); return tmp;}
	bool operator==(const CursorIterator& rhs) const {return p==rhs.p;}
	bool operator!=(const CursorIterator& rhs) const {return p!=rhs.p;}
	int& operator*() {return *p;}
};

template <class T, unsigned int SIZE> class List {
private:
	unsigned int start_data;
	unsigned int start_free;

	struct item {
		T data;
		int next;
		int prev;
	};

	struct item data[SIZE];

	typedef CursorIterator<T> iterator;

public:
		List();
		typedef T value_type;
		bool empty() const;
		int size() const;
		T& front() const;
		void push_front(const T &); // add a new value to the front of a list
		void pop_front();
		iterator begin() const;
		iterator end() const;
		iterator insert(iterator itr, const T& value); // insert before itr
		iterator erase(iterator start, iterator stop); // stop exclusive
		iterator erase(iterator itr); // return ++itr
};
