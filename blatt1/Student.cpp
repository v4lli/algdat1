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
 * Voller Eingabe-Konstruktor.
 * Kopiert die eingegebenen Werte.
 */
Student::Student(int matNr, char* name, char* vorname, char*gebTag)
{
	Matrikelnummer = matNr;
	strncpy(Name, name, 10);
	strncpy(Vorname, vorname, 10);
	strncpy(Geburtstag, gebTag, 9);
}

/**
 * Copy-Konstruktor.
 * Kopiert die Werte vom anderen Student.
 */
Student::Student(Student from)
{
	Matrikelnummer = from.getMatNummer();
	strncpy(Name, from.getName(), 10);
	strncpy(Vorname, from.getVorname(), 10);
	strncpy(Geburtstag, from.getGebTag(), 9);
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
int Student::getMatNummer() const
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
char* Student::getName() const
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
	strncpy(Name, neuName, 10);
	Name[9] = '\0';
}

/**
 * Getter fuer den Vornamen.
 */
char* Student::getVorname() const
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
	strncpy(Vorname, neuVorname, 10);
	Vorname[9] = '\0';
}

/**
 * Getter fuer den Geburtstag.
 */
char* Student::getGebTag() const
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
	strncpy(Geburtstag, neuGebTag, 9);
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
void Student::read(istream& istr)
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
	ostr << "Student: " << getMatNummer()
		 << ", " << getName()
		 << ", " << getVorname()
		 << ", " << getGebTag();
}

// Stream-Operatoren
ostream& operator << (ostream& ostr, const Student& stud)
{
	cout << "Hier";
	stud.write(ostr);
	return ostr;
}
istream& operator >> (istream& istr, Student& stud)
{
	stud.read(istr);
	return istr;
}
