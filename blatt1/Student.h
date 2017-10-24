/*
 * Student.h
 *
 *  Created on: 11.10.2017
 *      Author: Angelika
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
using namespace std;

class Student {
public:
	// Konstruktor und Destruktor
	Student();
	virtual ~Student();
	// Getter
	int getMatNummer();
	char* getName();
	char* getVorname();
	char* getGebTag();
	// Setter
	void setMatNummer(int);
	void setName(char*);
	void setVorname(char*);
	void setGebTag(char*);
	// Vergleichsoperatoren
	bool operator==(Student &s2);
	bool operator!=(Student &s2);
	bool operator>=(Student &s2);
	bool operator<=(Student &s2);
	bool operator>(Student &s2);
	bool operator<(Student &s2);
	// Read und Write
	virtual void write(ostream& ostr);
	virtual void read(istream& istr);

};

// Stream-Operatoren
ostream& operator << (ostream& ostr, Student& stud)
{
	stud.write(ostr);
	return ostr;
}
istream& operator >> (istream& istr, Student& stud)
{
	stud.read(istr);
	return istr;
}

#endif /* STUDENT_H_ */
