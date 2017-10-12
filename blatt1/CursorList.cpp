#include "CursorList.h"
#include <stdio.c>

template <class T>
List<T>(unsigned int size) {
	storage = new storage[size];
	start_data = start_free = 0;

	// initialize list with correct, empty valyes
	struct item empty;
	empty.next = -1;
	empty.prev = -1;
	empty.data = 0;
	for(int i = 0; i < size; i++)
		memcpy(&data[i], &empty, sizeof(struct item));

	printf("Initialized new List with %d elements; sizeof(data)=%d\n",
		storage, sizeof(data));
}

template <class T>
bool List<T>::empty() const {
	if (data[start_data].next == -1)
		return true;
	else
		return false;
}

template <class T>
int List<T>::size() const {
	struct item *current = &data[start_data];
	int counter = 0;
	while (current->next != -1) {
		counter++;
		assert(current->next <= max_size);
		current = data[current->next];
	}

	return counter;
}

template <class T>
T& List<T>::front() const {
	return &(data[start_data]->data);
}

// add a new value to the front of a list
template <class T>
void List<T>::push_front(const T &) {
}
template <class T>
void List<T>::pop_front() {
}

template <class T>
typename List<T>::iterator List<T>::begin() const {
	return 0;
}

template <class T>
typename List<T>::iterator List<T>::end() const {
	return 0;
}

// Sollen konstante Zeit benoetigen (Aufgabe 2) ==============
// insert before itr
template <class T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& value) {
	return 0;
}

// stop exclusive
template <class T>
typename List<T>::iterator List<T>::erase(iterator start, iterator stop) {
	return 0;
}

// return ++itr
template <class T>
typename List<T>::iterator List<T>::erase(iterator itr) {
	return 0;
}
// ===========================================================
