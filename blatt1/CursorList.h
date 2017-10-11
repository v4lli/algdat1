template <class T> class List {
	public:
		typedef T value_type;
		typedef ListIterator<T> iterator;
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
