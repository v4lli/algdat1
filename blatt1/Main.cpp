/* Main.cpp
 *
 * Loesung Algorithmen & Datenstrukturen, WS17/18, Blatt 1
 * Angelika Walter, Valentin Dornauer
 *
 */

#include <cstdio>
#include "CursorList.h"
#include "Student.h"

// Liste mit den eingegebenen Studenten.
CursorList<Student, 128> liste = CursorList<Student, 128>();

void enterStudent()
{
	printf("Wie viele Studenten wollen sie eingeben?\n");

	// Anzahl einlesen.
	int num = 0;
	cin >> num;
	for(int i = 0; i < num; i ++)
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
	if(liste.empty())
	{
		printf("In einer leeren Liste kann nicht gesucht werden.\n");
		return;
	}
	printf("Nach welcher Matrikelnummer wollen Sie suchen?\n");
	// Matrikelnummer einlesen.
	int suchNr = 0;
	cin >> suchNr;
	// Suchen.
	Student such = Student(suchNr, NULL, NULL, NULL);
	auto erg = cursorFind(liste.begin(), liste.end(), such);
	// Ergebnis ausgeben.
	cout << "-----------------\n";
	(*erg).write(cout << "Gefunden:\n");
	cout << "\n-----------------\n";
}

void deleteStudent()
{
	if(liste.empty())
	{
		printf("Kein Student vorhanden\n");
		return;
	}
	printf("Welchen Studenten (Matrikelnummer) wollen Sie loeschen?\n");
	// Matrikelnummer einlesen.
	int suchNr = 0;
	cin >> suchNr;
	// Suchen.
	Student such = Student(suchNr, NULL, NULL, NULL);
	auto erg = cursorFind(liste.begin(), liste.end(), such);
	// Student löschen.
	liste.erase(erg);
}

void alleAusgeben()
{
	if(liste.empty())
	{
		printf("Keine Studenten in der Liste.\n");
		return;
	}
	auto iterator = liste.begin();
	while(iterator != liste.end())
	{
		(*iterator).write(cout);
		cout << "\n";
		++iterator;
	}
}

int main(void)
{
	bool run = true;
	while(run)
	{
		// Menü anzeigen.
		printf("Was wollen Sie tun?\n");
		printf("e -> Eingabe von Studenten\n");
		printf("s -> Suche nach Student\n");
		printf("l -> Einen Studenten loeschen\n");
		printf("c -> Alle Studenten aus der Liste loeschen\n");
		printf("a -> Alle Studenten aus der Liste ausgeben\n");
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
			case 'l':	// Einen Studenten löschen.
			case 'L':
				deleteStudent();
				break;
			case 'c':	// Liste leeren.
			case 'C':
				liste = CursorList<Student, 128>();
#ifdef DEBUG
				liste.dump();
#endif
				break;
			case 'a':	// Alle Studenten ausgeben.
			case 'A':
				alleAusgeben();
#ifdef DEBUG
				liste.dump();
#endif
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
