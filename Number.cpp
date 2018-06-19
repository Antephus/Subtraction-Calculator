#include "Number.h"

Number::Number()
{
	for (int counter = 0; counter < MAXNUMSIZE; counter++)
		number[counter] = 0;
	length = 0;
}

int Number::getElement(int index) const
{
	return number[index];
}

void Number::setElement(int index, int newElement)
{
	number[index] = newElement;
}

int Number::getLength() const
{
	return length;
}

void Number::setLength(int newLength)
{
	length = newLength;
}

void Number::displayNum() const
{
	int counter = 0;
	
	// Skip any and all leading zeroes (e.g. in answer numbers that are smaller in length than the numbers they came from)
	while (number[counter] == 0 && counter < length)
			counter++;

	// If only zeroes were found, aka the answer was zero, make sure to display at least one.
	if (counter == length)
	{
		cout << 0;
	}
	
	// Display each digit actually part of the number
	while (counter < length)
	{
		cout << number[counter];
		counter++;
	}

	cout << endl << endl;
}