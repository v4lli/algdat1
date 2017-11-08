#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <cassert>
#include <cstring>

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

	class CursorIterator {
	private:
		int idx;
		int prev_idx;
		struct item *parent_data;

		void increment() {
			if (idx == ITERATOR_END)
				throw std::logic_error("Increment iterator end\n");

			prev_idx = idx;
			idx = (parent_data+getIdx())->next;
			if (idx < 0)
				idx = ITERATOR_END;
		}

	public:

		CursorIterator(const CursorList& parent, int start_at = 0)
		    : idx(start_at), prev_idx(ITERATOR_END), parent_data((struct item*)(&parent.data[0])) {
			// prev_index korrekt setzen.
			if(start_at == ITERATOR_END)
			{
				int next = start_data;
				struct item* current = NULL;
				while (next >= 0) {
					next = &data[next];
					prev_idx = next;

					next = current->next;
				}
			}
		}

		int getIdx() const {
			return idx;
		}

		int getPrevIdx() const{
			return prev_idx;
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
		/*struct item empty;
		empty.next = SLOT_EMPTY;
		empty.prev = SLOT_EMPTY;
		empty.data = 0;
		for(int i = 0; i < SIZE; i++)
			memcpy(&data[i], &empty, sizeof(struct item));*/

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
	/**
	 * Hinzufuegen eines neuen freien Elements.
	 */
	void free_push_front(int index)
	{
		// Fehlerhafte Eingaben abfangen.
		if (index < 0)
			throw std::runtime_error("Bad parameter");

		// Einbinden des neuen Elements.
		data[index].next = start_free;
		if(start_free != SLOT_EMPTY)
			data[start_free].prev = index;

		// Start-Index neu setzen.
		start_free = index;
	}

/**
 * Hinzufügen einer Kette von neuen freien Elementen.
 */
	void free_push_front(int startIndex, int endIndex)
	{
		// Fehlerhafte Eingaben abfangen.
		if(startIndex < 0 || endIndex < 0)
			throw std::runtime_error("Bad parameters");

		//
		data[endIndex].next = start_free;
		if(start_free != SLOT_EMPTY)
			data[start_free].prev = endIndex;
		start_free = startIndex;
	}

	/**
	 * Entfernen (belegen) eines freien Elements.
	 */
	int free_pop_front()
	{
		int index = start_free;
		if (index == SLOT_EMPTY)
			throw std::runtime_error("No free items.");
		else
		{
			start_free = data[index].next;
			data[index].next = SLOT_EMPTY;
			data[start_free].prev = SLOT_EMPTY;
		}

		return index;
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

		int insert = free_pop_front();
		if (insert == SLOT_EMPTY)
			throw std::runtime_error("List full");

		if (empty()) {
			data[insert].next = SLOT_EMPTY;
			data[insert].prev = SLOT_EMPTY;
			data[insert].data = param;
		} else {
			data[insert].next = start_data;
			data[insert].prev = SLOT_EMPTY;
			data[insert].data = param;
			data[insert].prev = start_free;
		}

		start_data = insert;
	}

	void pop_front() {
		int deleted = start_data;

		start_data = data[deleted].next;

		data[deleted].data = 0;
		data[deleted].prev = SLOT_EMPTY;
		data[deleted].next = SLOT_EMPTY;

		//start_free = deleted;
		free_push_front(deleted);
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
		int idx = itr.getIdx();
		assert(idx <= SIZE);

		int freeIndex = free_pop_front();

		struct item *current = &data[idx];
		struct item *prev = &data[current->prev];
		struct item *free = &data[freeIndex];

		free->prev = current->prev;
		free->next = idx;
		free->data = value;

		prev->next = freeIndex;
		current->prev = freeIndex;

		return itr;
	}

	iterator erase(iterator start, iterator stop) // stop exclusive
	{
		int start_idx = start.getIdx();
		assert(start_idx >= 0);
		int stop_idx = stop.getIdx();
		int end_idx = stop.getPrevIdx();

		struct item *start_item = &data[start_idx];
		struct item *prev_to_start = &data[start_item->prev];
		start_item->prev = SLOT_EMPTY;

		if (stop_idx == ITERATOR_END) {
			prev_to_start->next = SLOT_EMPTY;
		} else {
			struct item *end_item = &data[stop_idx];

			prev_to_start->next = stop_idx;
			end_item->prev = start_item->prev;
		}

		free_push_front(start_idx, end_idx);
		return stop;
	}

	iterator erase(iterator itr) // return ++itr
	{
		return erase(itr, ++itr);
	}
};
