#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <cassert>

//template <class T> class CursorIterator : public std::iterator<std::input_iterator_tag, int>
//{
//private:
//	int* p;
//public:
//
//	CursorIterator(int* x) : p(x) {}
//	CursorIterator(const CursorIterator<T> &mit) : p(mit.p) {}
//	CursorIterator& operator++() {
//		++p;
//		return *this;
//	}
//	CursorIterator operator++(int) {
//		CursorIterator tmp(*this);
//		operator++();
//		return tmp;
//	}
//	bool operator==(const CursorIterator& rhs) const {
//		return p==rhs.p;
//	}
//	bool operator!=(const CursorIterator& rhs) const {
//		return p!=rhs.p;
//	}
//	int& operator*() {
//		return *p;
//	}
//};

template <class T> class CursorIterator
{
private:
	struct item {
		T data;
		int next;
		int prev;
	};
	int idx;
	struct item *data;

public:
	CursorIterator(void *storage, int start_at = 0) {
		data = (struct item *)storage;
		// XXX unschoen, keine voidpointer am besten
		idx = start_at;
		printf("new iterator with dataptr=%p\n", data);
	}

	typedef CursorIterator<T> iterator;

	T& operator* () {
		return (data + idx)->data;
	}

	iterator& operator= (const iterator& rhs) {
		return rhs;
	}

	int getIdx() const {
		return idx;
	}

	struct item *getDataPtr() const {
		return data;
	}

	bool operator!= (const iterator& rhs) const {
		return (getIdx() != rhs.getIdx()) || (getDataPtr() != rhs.getDataPtr());
	}
	bool operator== (const iterator& rhs) const {
		printf("getIdx() == rhs.getIdx() = %d\n", getIdx() == rhs.getIdx());
		printf("getDataPtr() == rhs.getDataPtr() = %d\n", getDataPtr() == rhs.getDataPtr());
		return (getIdx() == rhs.getIdx()) && (getDataPtr() == rhs.getDataPtr());
	}
	iterator& operator++ () {
		return this;
	}
	iterator operator++ (int) {// postfix operator, dummy parameter
		return this;
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
	List() : start_data(-1), start_free(0) {
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
		if (start_data == -1)
			return true;
		else
			return false;
	}

	int size() const
	{
		if (start_data == -1)
			return 0;

		const struct item *current = &data[start_data];
		int counter = 1;
		while (current->next != -1) {
			//printf("current->next=%d\n", current->next);
			counter++;
			assert(current->next <= SIZE);
			current = &data[current->next];
		}

		return counter;
	}

	T& front() const {
		int foo = data[start_data].data;
		return foo;
		// XXX
	}

private:
	int find_free() {
		// find next free element XXX make more efficient
		int free = -1;
		for (int i = 0; i < SIZE; i++) {
			struct item *current = &data[i];
			if (current->next == -1 && current->prev == -1 && i != start_data) {
				free = i;
				break;
			}
		}
		return free;
	}

public:

	void push_front(const T &param) // add a new value to the front of a list
	{

		if (start_free == -1) {
			// XXX exception?
			return;
		}

		if (empty()) {
			data[start_free].next = -1;
			data[start_free].prev = -1;
			data[start_free].data = param;
		} else {
			data[start_free].next = start_data;
			data[start_free].prev = -1;
			data[start_free].data = param;
			data[start_data].prev = start_free;
		}

		start_data = start_free;
		start_free = find_free();
		printf("Added new element to the front; start_free=%d, start_data=%d\n", start_free, start_data);
	}

	void pop_front() {
		int deleted = start_data;

		start_data = data[deleted].next;

		data[deleted].data = 0;
		data[deleted].prev = -1;
		data[deleted].next = -1;

		start_free = 0;
	}

	iterator begin() const {
		return new iterator((void*)&data, 0);
	}

	iterator end() const {
		// XXX passt?
		return new iterator((void*)&data, SIZE);
	}

	// sollen constant-time benoetigen:
	iterator insert(iterator itr, const T& value) // insert before itr
	{
		if (start_free < 0) {
			// XXX exception
			return NULL;
		}

		int idx = *itr; // via operator-overloading
		assert(idx <= SIZE);

		struct item *current = &data[idx];
		struct item *prev = &data[current->prev];
		struct item *free = &data[start_free];

		free->prev = current->prev;
		free->next = idx;
		free->data = *value;

		prev->next = start_free;
		current->prev = start_free;

		start_free = find_free();

		return itr;
	}

	iterator erase(iterator start, iterator stop) // stop exclusive
	{
		int start_idx = *start;
		int stop_idx = *stop;

		// XXX handle specialcases:
		// - start = start of list
		// - end = end of list
		//
		// XXX asserts

		struct item *start_item = &data[start_idx];
		int next = start_idx;
		struct item *end_item = &data[stop_idx];
		struct item *prev_to_start = &data[start_item->prev];

		prev_to_start->next = end_item->next;
		start_item->prev = -1;
		end_item->prev = start_item->prev;
		end_item->next = -1;

		struct item *current = NULL;
		while (true) {
			current = &data[next];

			next = current->next;
			current->next = -1;
			current->prev = -1;
			current->data = 0;

			if (next == -1)
				break;
		}
		return stop;
	}
	iterator erase(iterator itr) // return ++itr
	{
		return erase(itr, ++itr);
	}
};
