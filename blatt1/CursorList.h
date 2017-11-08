#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <cassert>

#define ITERATOR_END -2
#define SLOT_EMPTY -1

template <class T, unsigned int SIZE>
class CursorList {
private:
	int start_data;
	int start_free;

protected:
	struct item {
		T data;
		int next;
		int prev;
	};

	struct item data[SIZE];

public:

	const class CursorIterator {
	private:
		int idx;
		struct item *parent_data;

		void increment() {
			if (idx == ITERATOR_END)
				throw std::logic_error("Increment iterator end\n");

			idx = (parent_data+getIdx())->next;
			if (idx < 0)
				idx = ITERATOR_END;
		}

	public:

		CursorIterator(const CursorList& parent, int start_at = 0)
		    : idx(start_at), parent_data((struct item*)(&parent.data[0])) { }

		int getIdx() const {
			return idx;
		}

		const struct item *getDataPtr() const {
			return parent_data;
		}

		T& operator* () {
			if (idx == ITERATOR_END)
				throw std::logic_error("Dereferenced iterator end\n");
			else
				return (parent_data+getIdx())->data;
		}

		CursorIterator& operator= (const CursorIterator& rhs) {
			return new CursorIterator(rhs.getDataPtr(), rhs.getIdx());
		}

		bool operator!= (const CursorIterator& rhs) const {
			return (getIdx() != rhs.getIdx()) || (getDataPtr() != rhs.getDataPtr());
		}

		bool operator== (const CursorIterator& rhs) const {
			return (getIdx() == rhs.getIdx()) && (getDataPtr() == rhs.getDataPtr());
		}

		CursorIterator& operator++ () { // prefix increment operator
			increment();
			return *this;
		}

		CursorIterator operator++ (int) { // postfix increment operator
			increment();
			return *this;
		}
	};

public:
	typedef CursorIterator iterator;

	CursorList() : start_data(SLOT_EMPTY), start_free(0) {
		// initialize free-list with correct connections.
		for(int i = 0; i < SIZE; i ++)
		{
			data[i].next = i + 1;
			data[i].prev = i - 1;
			data[i].data = 0;
		}
		data[0].prev = SLOT_EMPTY;
		data[SIZE - 1].next = SLOT_EMPTY;

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

	typedef T value_type; // XXX unused

	bool empty() const {
		if (start_data == SLOT_EMPTY)
			return true;
		else
			return false;
	}

	int size() const {
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

	T& front() {
		return data[start_data].data;
	}

private:
	void free_push_front(int index)
	{
		data[index].next = start_free;
		data[start_free].prev = index;
		start_free = index;
	}

	int free_pop_front()
	{
		int index = start_free;
		start_free = data[index].next;
		data[index].next = SLOT_EMPTY;
		data[start_free].prev = SLOT_EMPTY;

		return index;
	}

	int get_free()
	{
		return start_free;
	}

	// XXX muss weg, ist eigentlich unnoetig wenn eine freelist gepflegt wird
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

		return iterator(*this, iterator_start);
	}

	iterator end() const {
		return iterator(*this, ITERATOR_END);
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

	// XXX stop ist nicht exclusive sondern inclusive
	iterator erase(iterator start, iterator stop) // stop exclusive
	{
		int start_idx = start.getIdx();
		assert(start_idx >= 0);
		int stop_idx = stop.getIdx();

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
