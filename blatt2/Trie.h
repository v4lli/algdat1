/*
 * Trie.h
 *
 *  Created on: 29.11.2017
 *      Author: Angelika
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <cstring>
using namespace std;

template <class T, class E=char>
class Trie
{
public:
	typedef basic_string<E> key_type;	// string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
	typedef ... iterator;	// ...: keine C/C++ Ellipse, sondern von Ihnen zu entwickeln…
	bool empty() const;
	iterator insert(const value_type& value);
	void erase(const key_type& value);
	void clear(); // erase all
	iterator lower_bound(const key_type& testElement);	// first element >= testElement
	iterator upper_bound(const key_type& testElement);	// first element > testElement
	iterator find(const key_type& testElement);			// first element == testElement
	iterator begin();									// returns end() if not found
	iterator end();
	//typedef std::reverse_iterator<iterator> reverse_iterator;
	//reverse_iterator rbegin();						//wenn Sie Lust und Zeit haben…
	//reverse_iterator rend();							//wenn Sie Lust und Zeit haben…
};

#endif /* TRIE_H_ */
