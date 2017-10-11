/*
 * Student.h
 *
 *  Created on: 11.10.2017
 *      Author: Angelika
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>

class Student {
private:
	int Matrikelnummer;
	char[10] Name;
	char[10] Vorname;
	char[9] Geburtstag;

public:
	Student();
	virtual ~Student();
	bool operator==(const Student &s1, const Student &s2);
	bool operator!=(const Student &s1, const Student &s2);
	bool operator>=(const Student &s1, const Student &s2);
	bool operator<=(const Student &s1, const Student &s2);
	bool operator>(const Student &s1, const Student &s2);
	bool operator<(const Student &s1, const Student &s2);
	write(ostream& ostr)const;
	read(istream& istr);
};

#endif /* STUDENT_H_ */
