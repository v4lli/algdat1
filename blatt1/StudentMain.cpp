/*
 * StudentMain.cpp
 *
 *  Created on: 25.10.2017
 *      Author: Angelika
 */

#include "StudnetMain.h";
#include "Student.h";
#include <cstdio>;
#include <iostream>;
using namespace std;

int main(void)
{
	// Testen, ob die Setter und Getter funktionieren.
	Student* s1 = new Student();
	s1->setMatNummer(12345);
	cout << "Should be '12345' and is:" << s1->getMatNummer() << endl;
	s1->setName("Walter");
	cout << "Should be 'Walter' and is:" << s1->getName() << endl;
	s1->setVorname("Angelika");
	cout << "Should be 'Angelika' and is:" << s1->getVorname() << endl;
	s1->setGebTag("01.01.93");
	cout << "Should be '01.01.93' and is:" << s1->getGebTag() << endl;

	Student s2 = Student();
	s2.setMatNummer(23456);
	s2.setName("Wurst");
	s2.setVorname("Hans");
	s2.setGebTag("02.02.02");

	// Testen, ob die 'ToString' funktioniert.
	cout << &s2 << endl;

	// Vergleiche Testen.
	/*cout << "Should be 'true' and is:" << (s2 > s1) << endl;
	cout << "Should be 'true' and is:" << (s1 < s2) << endl;
	cout << "Should be 'true' and is:" << (s2 >= s1) << endl;
	cout << "Should be 'true' and is:" << (s1 <= s2) << endl;
	cout << "Should be 'true' and is:" << (s2 != s1) << endl;
	cout << "Should be 'true' and is:" << (s2 == s2) << endl;
	cout << "Should be 'true' and is:" << (s1 >= s1) << endl;
	cout << "Should be 'true' and is:" << (s1 <= s1) << endl;
	cout << "Should be 'false' and is:" << (s2 == s1) << endl;
	cout << "Should be 'false' and is:" << (s1 > s1) << endl;
	cout << "Should be 'false' and is:" << (s1 < s1) << endl;
	cout << "Should be 'false' and is:" << (s1 != s1) << endl;*/
}
