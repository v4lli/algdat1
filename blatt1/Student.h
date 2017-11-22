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
private:
	int Matrikelnummer;
	char Name[10];
	char Vorname[10];
	char Geburtstag[9];
public:
	// Konstruktor und Destruktor
	Student();
	Student(int, char*, char*, char*);
	Student(const Student&);
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

ostream& operator << (ostream& ostr, const Student& stud);
istream& operator >> (istream& istr, Student& stud);

#endif /* STUDENT_H_ */
