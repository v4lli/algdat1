/*
 * Main.cpp
 *
 *  Created on: 16.11.2017
 *      Author: Angelika
 */
#include <cstdio>
#include "CursorList.h"
#include "Student.h"

// Liste mit den eingegebenen Studenten.
CursorList<Student, 10> liste = CursorList<Student, 10>;

int main(void)
{
	bool run = true;
	while(run)
	{
		// Menü anzeigen.
		printf("Was wollen Sie tun?\n");
		printf("e -> Eingabe von Studenten\n");
		printf("s -> Suche nach Student\n");
		printf("c -> Alle Studenten aus der Liste löschen\n");
		printf("q -> Programm beenden\n");

		// Eingabe lesen.
		char c = 0;
		cin >> c;
		switch(c)
		{
			case 'e':	// Eingabe von Studentendaten.
			case 'E':
				enterStudent();
				break;
			case 's':	// Suche nach Student.
			case 'S':
				searchStudent();
				break;
			case 'c':	// Liste leeren.
			case 'C':
				liste = CursorList<Student>;
				break;
			case 'q':	// Programm beenden.
			case 'Q':
				run = false;
				break;
			default:	// Falsche Eingabe.
				break;
		}
	}
}


void enterStudent()
{
	printf("Wie viele Studenten wollen sie eingeben? (Maximal 10)\n");

	// Anzahl einlesen.
	int num = 0;
	cin >> num;
	for(int i = 0; i < num && i < 10; i ++)
	{
		// Jeden Studenten einlesen.
		printf("Studentendaten eingeben in der Form:\n");
		printf("Matrikelnummer Name Vorname Geburtstag\n");
		Student s;
		cin >> s;
		// An die Liste vorne anhängen.
		liste.push_front(s);
	}
}

void searchStudent()
{
	printf("Nach welcher Matrikelnummer wollen Sie suchen?\n");
	// Matrikelnummer einlesen.
	int suchNr = 0;
	cin >> suchNr;
	// Suchen.
	Student such = Student(suchNr, 0, 0, 0);
	CursorList<Student, 10>::CursorIterator erg = find(liste.begin(), liste.end(), such);
	// Ergebnis ausgeben.
	(*erg).write(cout << "Gefunden: ");
}
