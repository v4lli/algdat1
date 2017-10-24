#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <cassert>

#define ITERATOR_END -2
#define SLOT_EMPTY -1

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

	void increment() {
		if (idx == ITERATOR_END)
			throw std::logic_error("Increment iterator end\n");

		idx = (data + getIdx())->next;
		if (idx < 0)
			idx = ITERATOR_END;
	}

public:
	typedef CursorIterator<T> iterator;

	CursorIterator(void *storage, int start_at = 0) {
		// XXX unschoen, keine opaque pointer sondern struct item
		data = (struct item *)storage;
		idx = start_at;
	}

	int getIdx() const {
		return idx;
	}

	struct item *getDataPtr() const {
		return data;
	}

	T& operator* () {
		if (idx == ITERATOR_END)
			throw std::logic_error("Dereferenced iterator end\n");
		else
			return (data + getIdx())->data;
	}

	iterator& operator= (const iterator& rhs) {
		auto itr = new CursorIterator<T>(rhs.getDataPtr(), rhs.getIdx());
		return itr;
	}

	bool operator!= (const iterator& rhs) const {
		return (getIdx() != rhs.getIdx()) || (getDataPtr() != rhs.getDataPtr());
	}

	bool operator== (const iterator& rhs) const {
		return (getIdx() == rhs.getIdx()) && (getDataPtr() == rhs.getDataPtr());
	}

	iterator& operator++ () { // prefix increment operator
		increment();
		return *this;
	}

	iterator operator++ (int) { // postfix increment operator
		increment();
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
	List() : start_data(SLOT_EMPTY), start_free(0) {
		// initialize list with correct, empty valyes
		struct item empty;
		empty.next = SLOT_EMPTY;
		empty.prev = SLOT_EMPTY;
		empty.data = 0;
		for(int i = 0; i < SIZE; i++)
			memcpy(&data[i], &empty, sizeof(struct item));

#ifdef DEBUG
		printf("Initialized new List with %d elements; sizeof(data)=%ld\n",
			SIZE, sizeof(data));
#endif
	}

	typedef T value_type;
	bool empty() const {
		if (start_data == SLOT_EMPTY)
			return true;
		else
			return false;
	}

	int size() const
	{
		if (start_data == SLOT_EMPTY)
			return 0;

		const struct item *current = &data[start_data];
		int counter = 1;
		while (current->next != SLOT_EMPTY) {
			counter++;
			assert(current->next <= SIZE);
			current = &data[current->next];
		}

		return counter;
	}

	T& front() const {
		int foo = data[start_data].data;
		return foo;
		// XXX richtig schlecht
	}

private:
	int find_free() {
		int free = SLOT_EMPTY;
		for (int i = 0; i < SIZE; i++) {
			struct item *current = &data[i];
			if (current->next == SLOT_EMPTY
			    && current->prev == SLOT_EMPTY
			    && i != start_data) {
				free = i;
				break;
			}
		}
		return free;
	}

	int getLastElem() const
	{
		if (start_data == SLOT_EMPTY)
			return 0;

		const struct item *current = &data[start_data];
		int last = 0;
		while (current->next != SLOT_EMPTY) {
			last = current->next;
			assert(current->next <= SIZE);
			current = &data[current->next];
		}

		return last;
	}

public:

	void push_front(const T &param) // add a new value to the front of a list
	{

		if (start_free == SLOT_EMPTY)
			throw std::runtime_error("List full");

		if (empty()) {
			data[start_free].next = SLOT_EMPTY;
			data[start_free].prev = SLOT_EMPTY;
			data[start_free].data = param;
		} else {
			data[start_free].next = start_data;
			data[start_free].prev = SLOT_EMPTY;
			data[start_free].data = param;
			data[start_data].prev = start_free;
		}

		start_data = start_free;
		start_free = find_free();
	}

	void pop_front() {
		int deleted = start_data;

		start_data = data[deleted].next;

		data[deleted].data = 0;
		data[deleted].prev = SLOT_EMPTY;
		data[deleted].next = SLOT_EMPTY;

		start_free = deleted;
	}

	iterator begin() const {
		int iterator_start;
		if (start_data == SLOT_EMPTY)
			iterator_start = ITERATOR_END;
		else
			iterator_start = start_data;

		return iterator((void*)&data, iterator_start);
	}

	iterator end() const {
		return iterator((void*)&data, ITERATOR_END);
	}

	// sollen constant-time benoetigen:
	iterator insert(iterator itr, const T& value) // insert before itr
	{
		if (start_free < 0)
			throw std::runtime_error("List full");

		int idx = itr.getIdx();
		assert(idx <= SIZE);

		struct item *current = &data[idx];
		struct item *prev = &data[current->prev];
		struct item *free = &data[start_free];

		free->prev = current->prev;
		free->next = idx;
		free->data = value;

		prev->next = start_free;
		current->prev = start_free;

		start_free = find_free();

		return itr;
	}

	iterator erase(iterator start, iterator stop) // stop exclusive
	{
		int start_idx = start.getIdx();
		assert(start_idx >= 0);
		int stop_idx = stop.getIdx();

		// XXX handle specialcases:
		// - start = start of list
		// - end = end of list
		//
		// XXX asserts

		struct item *start_item = &data[start_idx];
		struct item *prev_to_start = &data[start_item->prev];
		int next = start_idx;
		start_item->prev = SLOT_EMPTY;

		if (stop_idx == ITERATOR_END) {
			prev_to_start->next = SLOT_EMPTY;
		} else {
			struct item *end_item = &data[stop_idx];
			prev_to_start->next = end_item->next;

			end_item->prev = start_item->prev;
			end_item->next = SLOT_EMPTY;
		}

		// mark possibly new emptuy slots as such
		struct item *current = NULL;
		while (true) {
			current = &data[next];

			next = current->next;
			current->next = SLOT_EMPTY;
			current->prev = SLOT_EMPTY;
			current->data = 0;

			if (next == SLOT_EMPTY)
				break;
		}
		return stop;
	}

	iterator erase(iterator itr) // return ++itr
	{
		return erase(itr, ++itr);
	}
};

// XXX iterator invalidation bei insert bzw erase
