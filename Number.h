#include <iostream>
#include <string>

using namespace std;
const int MAXNUMSIZE = 50;

class Number
{
private:
	int number[MAXNUMSIZE];
	int length;
public:
	Number();	
	int getElement(int index) const;
	void setElement(int index, int newElement);
	int getLength() const;
	void setLength(int newLength);
	void displayNum() const;
};


void displayWelcome();
void getNumber(string& number);
bool isValidNumber(string number);
bool isValidSize(string number);
bool isNegative(string number);
void setWholeNumber(Number& numberOb, string newNum);
bool firstIsLarger(Number num1, Number num2);
Number subtract2Nums(Number num1, Number num2, bool firstIsLarger);

