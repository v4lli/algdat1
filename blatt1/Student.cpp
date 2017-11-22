/* Student.cpp
 *
 * Loesung Algorithmen & Datenstrukturen, WS17/18, Blatt 1
 * Angelika Walter, Valentin Dornauer
 *
 */

#include "Student.h"
#include <iostream>
#include <cstring>
using namespace std;

/**
 * Konstruktor.
 */
Student::Student() {
#ifdef DEBUG
	printf("DEBUG: Empty constructor called\n");
#endif
}

/**
 * Voller Eingabe-Konstruktor.
 * Kopiert die eingegebenen Werte.
 */
Student::Student(int matNr, char* name, char* vorname, char*gebTag) : Matrikelnummer(matNr)
{
	if (name != NULL)
		strncpy(Name, name, 10);
	if (vorname != NULL)
		strncpy(Vorname, vorname, 10);
	if (gebTag != NULL)
		strncpy(Geburtstag, gebTag, 9);
}

/**
 * Copy-Konstruktor.
 * Kopiert die Werte vom anderen Student.
 */
Student::Student(const Student &from)
{
	Student s = (Student)from;
#ifdef DEBUG
	printf("DEBUG: CopyConstructor called\n");
#endif
	Matrikelnummer = s.getMatNummer();
	strncpy(Name, s.getName(), 10);
	strncpy(Vorname, s.getVorname(), 10);
	strncpy(Geburtstag, s.getGebTag(), 9);
}

/**
 * Destruktor.
 */
Student::~Student() {}

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
	strncpy(Name, neuName, 10);
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
	strncpy(Vorname, neuVorname, 10);
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
void Student::write(ostream& ostr)
{
	ostr << "Student: " << getMatNummer()
		 << ", " << getName()
		 << ", " << getVorname()
		 << ", " << getGebTag();
}
// Stream-Operatoren
ostream& operator<< (ostream& ostr, const Student& stud)
{
	((Student)stud).write(ostr);
	return ostr;
}

istream& operator>> (istream& istr, Student& stud)
{
	stud.read(istr);
	return istr;
}
