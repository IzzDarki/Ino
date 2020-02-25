#include <Arduino.h>

#include <BitField.h>
#include <IOStream.h>

union ID
{
	ino::BitField<0, 1> State;
	ino::BitField<1, 2> Country;
	ino::BitField<3, 4> Location;
	ino::BitField<7, 9> Person;
};


void setup() {
	Serial.begin(9600);
	
	ID MaxMuster;
	MaxMuster.State = true;
	MaxMuster.Country = 1;
	MaxMuster.Location = 12;
	MaxMuster.Person = 428;

	ino::out << "MaxMuster: " << ino::endl
		<< "State: " << MaxMuster.State << ino::endl
		<< "Country: " << MaxMuster.Country << ino::endl
		<< "Location: " << MaxMuster.Location << ino::endl
		<< "Person: " << MaxMuster.Person << ino::endl
		<< ino::endl
		<< "There are: " << ino::endl
		<< MaxMuster.State.MaximalNumber << " States" << ino::endl
		<< MaxMuster.Country.MaximalNumber << " Countries" << ino::endl
		<< MaxMuster.Location.MaximalNumber << " Locations" << ino::endl
		<< MaxMuster.Person.MaximalNumber << " Persons" << ino::endl;
}

void loop() {
	
}