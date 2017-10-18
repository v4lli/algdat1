#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <cassert>

template <class T> class CursorIterator : public std::iterator<std::input_iterator_tag, int>
{
private:
	int* p;
public:

	CursorIterator(int* x) : p(x) {}
	CursorIterator(const CursorIterator<T> &mit) : p(mit.p) {}
	CursorIterator& operator++() {
		++p;
		return *this;
	}
	CursorIterator operator++(int) {
		CursorIterator tmp(*this);
		operator++();
		return tmp;
	}
	bool operator==(const CursorIterator& rhs) const {
		return p==rhs.p;
	}
	bool operator!=(const CursorIterator& rhs) const {
		return p!=rhs.p;
	}
	int& operator*() {
		return *p;
	}
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
	List() : start_data(0), start_free(0) {
		// initialize list with correct, empty valyes
		struct item empty;
		empty.next = -1;
		empty.prev = -1;
		empty.data = 0;
		for(int i = 0; i < SIZE; i++)
			memcpy(&data[i], &empty, sizeof(struct item));

		printf("Initialized new List with %d elements; sizeof(data)=%ld\n",
			SIZE, sizeof(data));
	}

	typedef T value_type;
	bool empty() const {
		if (data[start_data].next == -1)
			return true;
		else
			return false;
	}

	int size() const
	{
		const struct item *current = &data[start_data];
		int counter = 0;
		while (current->next != -1) {
			counter++;
			assert(current->next <= SIZE);
			current = &data[current->next];
		}

		return counter;
	}

	T& front() const {
		int foo = data[start_data].data;
		return foo;
	}

	void push_front(const T &param) // add a new value to the front of a list
	{

		if (start_free == -1) {
			// XXX exception?
			return;
		}

		data[start_free].next = start_data;
		data[start_free].data = *param;
		data[start_free].prev = -1;

		data[start_data].prev = start_free;
		start_data = start_free;

		// find next free element XXX make more efficient
		start_free = -1;
		for (int i = 0; i < SIZE; i++) {
			struct item *current = data[i];
			if (current->next == -1 && current->prev == -1) {
				start_free = i;
				break;
			}
		}
	}

	void pop_front()
	{
		int deleted = start_data;

		start_data = data[deleted].next;

		data[deleted].data = 0;
		data[deleted].prev = -1;
		data[deleted].next = -1;

		start_free = 0;
	}

	iterator begin() const;
	iterator end() const;
	iterator insert(iterator itr, const T& value); // insert before itr
	iterator erase(iterator start, iterator stop); // stop exclusive
	iterator erase(iterator itr); // return ++itr
};
