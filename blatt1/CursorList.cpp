#include "CursorList.h"
#include <cstdio>

template <class T, unsigned int SIZE>
List<T, SIZE>::List() : start_data(0), start_free(0) {
	// initialize list with correct, empty valyes
	struct item empty;
	empty.next = -1;
	empty.prev = -1;
	empty.data = 0;
	for(int i = 0; i < SIZE; i++)
		memcpy(&data[i], &empty, sizeof(struct item));

	printf("Initialized new List with %d elements; sizeof(data)=%d\n",
		data, sizeof(data));
}

template <class T, unsigned int SIZE>
bool List<T, SIZE>::empty() const {
	if (data[start_data].next == -1)
		return true;
	else
		return false;
}

template <class T, unsigned int SIZE>
int List<T, SIZE>::size() const {
	struct item *current = &data[start_data];
	int counter = 0;
	while (current->next != -1) {
		counter++;
		assert(current->next <= SIZE);
		current = data[current->next];
	}

	return counter;
}

template <class T, unsigned int SIZE>
T& List<T, SIZE>::front() const {
	return &(data[start_data]->data);
}

// add a new value to the front of a list
template <class T, unsigned int SIZE>
void List<T, SIZE>::push_front(const T & param) {

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

template <class T, unsigned int SIZE>
void List<T, SIZE>::pop_front() {
	int deleted = start_data;

	start_data = data[deleted].next;

	data[deleted].data = 0;
	data[deleted].prev = -1;
	data[deleted].next = -1;

	start_free = 0;
}

template <class T, unsigned int SIZE>
typename List<T, SIZE>::iterator List<T, SIZE>::begin() const {
	return 0;
}

template <class T, unsigned int SIZE>
typename List<T, SIZE>::iterator List<T, SIZE>::end() const {
	return 0;
}

// Sollen konstante Zeit benoetigen (Aufgabe 2) ==============
// insert before itr
template <class T, unsigned int SIZE>
typename List<T, SIZE>::iterator List<T, SIZE>::insert(iterator itr, const T& value) {
	return 0;
}

// stop exclusive
template <class T, unsigned int SIZE>
typename List<T, SIZE>::iterator List<T, SIZE>::erase(iterator start, iterator stop) {
	return 0;
}

// return ++itr
template <class T, unsigned int SIZE>
typename List<T, SIZE>::iterator List<T, SIZE>::erase(iterator itr) {
	return 0;
}
// ===========================================================
