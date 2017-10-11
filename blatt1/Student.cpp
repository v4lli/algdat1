/*
 * Student.cpp
 *
 *  Created on: 11.10.2017
 *      Author: Angelika
 */

#include "Student.h"
#include <iostream>

Student::Student() {
	Matrikelnummer = 0;
	Name = "";
	Vorname = "";
	Geburtsdatum = "";
}

Student::~Student() {
	// TODO Auto-generated destructor stub
}

bool operator==(const Student &s1, const Student &s2)
{
	return s1.Matrikelnummer == s2.Matrikelnummer;
}

bool operator!=(const Student &s1, const Student &s2)
{
	return s1.Matrikelnummer != s2.Matrikelnummer;
}

bool operator>=(const Student &s1, const Student &s2)
{
	return s1.Matrikelnummer >= s2.Matrikelnummer;
}

bool operator<=(const Student &s1, const Student &s2)
{
	return s1.Matrikelnummer <= s2.Matrikelnummer;
}

bool operator>(const Student &s1, const Student &s2)
{
	return s1.Matrikelnummer > s2.Matrikelnummer;
}

bool operator<(const Student &s1, const Student &s2)
{
	return s1.Matrikelnummer < s2.Matrikelnummer;
}
