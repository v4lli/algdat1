/*
 *
 * Loesung Algorithmen & Datenstrukturen, WS17/18, Blatt 1
 * Angelika Walter, Valentin Dornauer
 *
 */

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
	int end_data;
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
		struct item *parent_data;

		/**
		 * Increment the local pointer to the current physical index
		 * inside our parent's storage array.
		 * @throws std::logic_error in case the iterator is already
		 *         past its end.
		 */
		void increment() {
			if (idx == ITERATOR_END)
				throw std::logic_error("Increment iterator end\n");

			idx = (parent_data+getIdx())->next;
			if (idx < 0)
				idx = ITERATOR_END;
		}

	public:

		/*
		 * The iterator remembers two values: the current index in the
		 * physical data array from the parent class.
		 */
		CursorIterator(const CursorList& parent, int start_at = 0)
		    : idx(start_at), parent_data((struct item*)(&parent.data[0])) {
		}

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

	CursorList() : start_data(SLOT_EMPTY), end_data(SLOT_EMPTY), start_free(0) {
		// initialize free-list with correct connections.
		for(int i = 0; i < SIZE; i ++)
		{
			data[i].next = i + 1;
			data[i].prev = i - 1;
		}
		data[0].prev = SLOT_EMPTY;
		data[SIZE - 1].next = SLOT_EMPTY;

#ifdef DEBUG
		printf("Initialized new List with %d elements; sizeof(data)=%ld\n",
				SIZE, sizeof(data));
#endif
	}

	/**
	 * Check whether the list is empty or not
	 *
	 * @return true/false if the list is empty
	 */
	bool empty() const {
		if (start_data == SLOT_EMPTY)
			return true;
		else
			return false;
	}

	/**
	 * Returns the number of elements actually stored inside the list
	 *
	 * @return Number of elements.
	 */
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

	void dump() const {
		if (start_data == SLOT_EMPTY) {
			printf("DUMP: List empty");
			return;
		}

		printf("DUMP: start_data=%d\n", start_data);

		int idx = start_data;
		const struct item *current = &data[idx];
		while (current->next != SLOT_EMPTY) {
			printf("DUMP: data[%d].prev=%d data[%d].next=%d\n", idx, current->prev, idx, current->next);
			assert(current->next <= SIZE);
			current = &data[current->next];
			idx = current->next;
		}
	}

	/**
	 * Returns the first element of the list.
	 *
	 * Undefined behaviour is list empty.
	 */
	T& front() {
		return data[start_data].data;
	}

private:
	/**
	 * Hinzufuegen eines neuen freien Elements.
	 * @param index Index des neuen Elements.
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
	 * Hinzufuegen einer Kette von neuen freien Elementen.
	 * @param startIndex Index des ersten Elements der Kette.
	 * @param endIndex Index des letzten Elements der Kette.
	 */
	void free_push_front(int startIndex, int endIndex)
	{
		// Fehlerhafte Eingaben abfangen.
		if(startIndex < 0 || endIndex < 0)
			throw std::runtime_error("Bad parameters");

		// Einbinden der Kette vor dem bisher ersten Element.
		data[startIndex].prev = SLOT_EMPTY;
		data[endIndex].next = start_free;
		if(start_free != SLOT_EMPTY)
			data[start_free].prev = endIndex;
		start_free = startIndex;
	}

	/**
	 * Entfernen (belegen) eines freien Elements.
	 * @return Index des freigegebenen Elements.
	 */
	int free_pop_front()
	{
		// Fehlerhafte Eingaben abfangen.
		int index = start_free;
		if (index == SLOT_EMPTY)
			throw std::runtime_error("No free items.");

		// Entfernen des ersten Elements aus den freien Elementen.
		start_free = data[index].next;
		data[index].next = SLOT_EMPTY;
		data[start_free].prev = SLOT_EMPTY;

		// Rückgabe des zu verwendenden Index.
		return index;
	}

public:
	/**
	 * Add an element to the front of the list
	 *
	 * @param param Element to add
	 */
	void push_front(const T &param) // add a new value to the front of a list
	{

		int insert = free_pop_front();
		if (insert == SLOT_EMPTY)
			throw std::runtime_error("List full");

		if (empty()) {
			end_data = insert;
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

	/**
	 * Remove the first element from the list
	 */
	void pop_front() {
		int deleted = start_data;

		start_data = data[deleted].next;

		data[deleted].data = 0;
		data[deleted].prev = SLOT_EMPTY;
		data[deleted].next = SLOT_EMPTY;

		free_push_front(deleted);
	}

	/*
	 * Return an iterator pointing to the first element in the list
	 */
	iterator begin() const {
		int iterator_start;
		if (start_data == SLOT_EMPTY)
			iterator_start = ITERATOR_END;
		else
			iterator_start = start_data;

		return iterator(*this, iterator_start);
	}

	/**
	 * Diese Iterator darf nicht dereferenziert werden,
	 * sondern er ist nur zum erkennen des Endes zulässig (getIdx() bzw != ==)
	 */
	iterator end() const {
		return iterator(*this, ITERATOR_END);
	}

	/**
	 * Insert elemente value before itr
	 *
	 * @return Unchanged itr
	 */
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

		if (itr.getIdx() == ITERATOR_END) {
			end_data = freeIndex;
		}

		return itr;
	}

	/**
	 * Erase elements starting at start until stop - 1 (i.e. stop is not
	 * removed and may be the end() iterator)
	 *
	 * @return stop itr (unchanged)
	 */
	iterator erase(iterator start, iterator stop) // stop exclusive
	{
		int start_idx = start.getIdx();
		assert(start_idx >= 0);
		int stop_idx = stop.getIdx();

		struct item *start_item = &data[start_idx];
		struct item *prev_to_start = &data[start_item->prev];

		if (stop_idx == ITERATOR_END) {
#ifdef DEBUG
			printf("Deleting up to last element, start_idx=%d "
			    "stop_idx=%d\n", start_idx, stop_idx);
#endif
			int delete_to = end_data;
			prev_to_start->next = SLOT_EMPTY;
			end_data = start_item->prev;
			start_item->prev = SLOT_EMPTY;
			free_push_front(start_idx, delete_to);

			if (start_idx == start_data) {
				start_data = SLOT_EMPTY;
			}
		} else {
			struct item *end_item = &data[stop_idx];
#ifdef DEBUG
			printf("Deleting non-last element, start_idx=%d "
			    "stop_idx=%d\n", start_idx, stop_idx);
#endif
			int delete_to = end_item->prev;

			prev_to_start->next = stop_idx;
			end_item->prev = start_item->prev;
			start_item->prev = SLOT_EMPTY;
			free_push_front(start_idx, delete_to);

			if (start_idx == start_data) {
				start_data = stop_idx;
			}
		}

		return stop;
	}

	/** Remove element pointed to by itr
	 *
	 * @return itr + 1
	 */
	iterator erase(iterator itr) // return ++itr
	{
		return erase(itr, ++itr);
	}
};

/**
 * Suchen eines bestimmten Wertes.
 * Wenn gefunden: Iterator zurückgeben, der auf den Wert zeigt;
 * wenn nicht gefunden: Iterator stop zurückgeben.
 * @param start Ab hier soll gesucht werden.
 * @param stop Bis hier soll gesucht werden.
 * @param value Dieser Wert soll gesucht werden.
 * @return Verweis auf den Wert oder stop.
 */
template<typename Iterator, typename T>
Iterator cursorFind(Iterator start, Iterator stop, T& value)
{
	// Prüfen, ob Wert gefunden oder am Ende angelangt.
	while((*start != value) && (start != stop))
	{
		// Wenn nicht: eins weiter.
		++start;
	}
	// Ergebnis zurückgeben (Iterator zeigend auf gesuchtem Wert oder Stop)
	return start;
}
