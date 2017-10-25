/*
 * Student.cpp
 *
 *  Created on: 11.10.2017
 *      Author: Angelika
 */

#include "Student.h"
#include <iostream>
#include <cstring>
using namespace std;

int Matrikelnummer;
char Name[10];
char Vorname[10];
char Geburtstag[9];

/**
 * Konstruktor.
 * Setzt alle Attribute auf 0;
 */
Student::Student()
{
	Matrikelnummer = 0;
}

/**
 * Destruktor.
 * Setzt alle Attribute auf 0.
 */
Student::~Student()
{
	Matrikelnummer = 0;
}

/**
 * Getter fuer die Matrikelnummer.
 */
int Student::getMatNummer()
{
	return Matrikelnummer;
}

/**
 * Setter fuer die Matrikelnummer.
 */
void Student::setMatNummer(int neuMatNum)
{
	Matrikelnummer = neuMatNum;
}

/**
 * Getter fuer den Namen.
 */
char* Student::getName()
{
	return Name;
}

/**
 * Setter fuer den Namen.
 * Uebernimmt die ersten 9 Zeichen des Input-Arrays
 * und setzt das letzte Zeichen = '\0'.
 */
void Student::setName(char neuName[])
{
	strncpy(neuName, Name, 10);
	Name[9] = '\0';
}

/**
 * Getter fuer den Vornamen.
 */
char* Student::getVorname()
{
	return Vorname;
}

/**
 * Setter fuer den Vornamen.
 * Uebernimmt die ersten 9 Zeichen des Input-Arrays
 * und setzt das letzte Zeichen = '\0'.
 */
void Student::setVorname(char neuVorname[])
{
	strncpy(neuVorname, Vorname, 10);
	Vorname[9] = '\0';
}

/**
 * Getter fuer den Geburtstag.
 */
char* Student::getGebTag()
{
	return Geburtstag;
}

/**
 * Setter fuer den Geburtstag.
 * Uebernimmt die ersten 8 Zeichen des Input-Arrays
 * und setzt das letzte Zeichen = '\0'.
 */
void Student::setGebTag(char neuGebTag[])
{
	strncpy(neuGebTag, Geburtstag, 9);
	Geburtstag[8] = '\0';
}

/**
 * Vergleicht zwei Studenten anhand ihrer Matrikelnummern auf Gleichheit.
 */
bool Student::operator==(Student &s2)
{
	return this->getMatNummer() == s2.getMatNummer();
}

/**
 * Vergleicht zwei Studenten anhand ihrer Matrikelnummern auf Ungleichheit.
 */
bool Student::operator!=(Student &s2)
{
	return this->getMatNummer() != s2.getMatNummer();
}

/**
 * Vergleicht zwei Studenten anhand ihrer Matrikelnummer auf Groesser oder Gleich.
 */
bool Student::operator>=(Student &s2)
{
	return this->getMatNummer() >= s2.getMatNummer();
}

/**
 * Vergleicht zwei Studenten anhand ihrer Matrikelnummer auf Kleiner oder Gleich.
 */
bool Student::operator<=(Student &s2)
{
	return this->getMatNummer() <= s2.getMatNummer();
}

/**
 * Vergleicht zwei Studenten anhand ihrer Matrikelnummer auf Groesser.
 */
bool Student::operator>(Student &s2)
{
	return this->getMatNummer() > s2.getMatNummer();
}

/**
 * Vergleicht zwei Studenten anhand ihrer Matrikelnummer auf Kleiner.
 */
bool Student::operator<(Student &s2)
{
	return this->getMatNummer() < s2.getMatNummer();
}

/**
 * Liest aus einem eingehenden Stream alle Attribute aus.
 */
void read(istream& istr)
{
	istr >> Matrikelnummer;
	istr >> Name;
	istr >> Vorname;
	istr >> Geburtstag;
}

/**
 * Schreibt auf einen ausgehenden Stream alle Attribute.
 */
void Student::write(ostream& ostr) const
{
	ostr << this->getMatNummer() << getName() << getVorname() << getGebTag();
}

// Stream-Operatoren
ostream& operator << (ostream& ostr, const Student& stud)
{
	stud.write(ostr);
	return ostr;
}
istream& operator >> (istream& istr, Student& stud)
{
	stud.read(istr);
	return istr;
}
