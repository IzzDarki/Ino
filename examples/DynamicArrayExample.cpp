#include <Arduino.h>

#include <DynamicArray.h>
#include <IOStream.h>

void setup() {
	ino::out.begin(9600);

	ino::DynamicArray<int> DArray = { 0, 1, 2, 3 };

	DArray.PushBack(9);
	DArray.PushBack(2);
	DArray.PushBack(40);
	DArray.PushBack(3243);
	DArray.PushBack(38);
	DArray.PushBack(3841);
	DArray.PushBack(3218);
	DArray.PushBack(421);
	DArray.PushBack(1348);
	DArray.PushBack(26);

	DArray.Erase(2, 2);

	ino::out << "Length of DArray: " << DArray.GetLength() << ino::endl;

	for (const int Number : DArray)
		ino::out << Number << ino::tab;
	ino::out << ino::endl;
	for (int C = 0; C < DArray.GetLength(); C ++)
		ino::out << DArray[C] << ino::tab;
	ino::out << ino::endl;
}

void loop() {

}
