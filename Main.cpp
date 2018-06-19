#include "Number.h"

int main()
{
	string number1, number2;
	Number firstNum, secondNum, answer;
	char cont = 'y'; // "Continue?" variable

	displayWelcome();

	do
	{
		// Get the first number (to subtract from), validate it, and insert it into the first int array 
		cout << "Please enter a positive number you want to subtract from: ";
		getNumber(number1);
		firstNum.setLength(number1.length());
		setWholeNumber(firstNum, number1);

		// Get the second number (to subtract with), validate it, and insert it into the second int array 
		cout << endl << "Thank you, now please enter a positive number you want to subtract with: ";
		getNumber(number2);
		secondNum.setLength(number2.length());
		setWholeNumber(secondNum, number2);

		/* Subtract the smaller number from the larger number
		 1st param = "largerNum", 2nd = "smallerNum", 3rd = if 2nd input number is larger (i.e. answer will be negative) (T) or not (F)*/
		if (firstIsLarger(firstNum, secondNum))
			answer = subtract2Nums(firstNum, secondNum, false);
		else
			answer = subtract2Nums(secondNum, firstNum, true);

		// Display the answer details and ask user if they are done
		cout << endl << "Answer: ";
		answer.displayNum();
		cout << endl << "Continue subtracting? y/n: ";
		cin >> cont;

	} while (cont == 'y' || cont == 'Y');
}



// Display the program welcome message
void displayWelcome()
{
	cout << "***************************************************************************************" << endl;
	cout << "***                                    Welcome!                                     ***" << endl;
	cout << "***   This program will carry out subtraction calculations on very large numbers.   ***" << endl;
	cout << "***                                                                                 ***" << endl;
	cout << "***************************************************************************************" << endl << endl;
}



/* Keep displaying error messages and getting new numbers until a valid one is entered 
 (i.e. 50 or less digits, positive number, with no non-numerical chars)*/
void getNumber(string& number)
{
	cin >> number;
	
	while (isNegative(number) || !isValidSize(number) || !isValidNumber(number))
	{
		if (isNegative(number))
		{
			cout << endl << "Sorry, that is a negative number! Please enter a positive number: ";
		}
		else if (!isValidSize(number))
		{
			cout << endl << "Sorry, the number you entered is too large! Please enter a number that is 50 digits or less: ";
		}
		else
		{
			cout << endl << "Sorry, the number you entered contains invalid characters! Please take care as you type and try again: ";
		}

		cin >> number;
	}	
}



// Check if the number entered was a negative number; return true if so, false if not
bool isNegative(string number)
{
	return (number[0] == '-')
		? true : false;
}



// Check the length of the number is valid and within the bounds of the array; return true if so, false if not
bool isValidSize(string number)
{
	return (number.length() <= MAXNUMSIZE)
		? true : false;
}



// Check each char in the string and return false (number invalid) if a non-digit char is found or true if all are digits (valid)
bool isValidNumber(string number)
{
	int position = 0;
		
	while (position < number.length())
	{
		// Use range of ASCII codes for digits to test if chars are digits or not
		if (number[position] < 48 || number[position] > 57)
		{
			return false;
		}
		else
			position++;
	}

	return true;
}



// Convert the chars of the given number string to their int values and insert these into the number array
void setWholeNumber(Number& number, string newNum)
{
	for (int position = 0; position < number.getLength(); position++)
	{
		// Convert chars to ints by subtracting the offset from zero their ASCII code range has (e.g. '1'-'0' = 49-48 = 1)
		number.setElement(position, (newNum[position] - '0'));
	}
}



// Check if the first number entered is larger than the second number entered
bool firstIsLarger(Number num1, Number num2)
{
	int index = 0;

	// Compare number lengths first
	if (num1.getLength() > num2.getLength())
		return true;
	else if (num2.getLength() > num1.getLength())
		return false;
	else
	{
		// Find 1st unequivalent set of digits and return whether 1st num's digit larger or not 
		// (equal numbers will return "false" - 1st wasn't larger)
		while ((num1.getElement(index) == num2.getElement(index)) && (index < MAXNUMSIZE - 1))
			index++;
		return (num1.getElement(index) > num2.getElement(index))
			? true : false;
	}
}


 
/* Subtract the smaller number from the larger using long-subtraction method of subtracting each digit in 2nd number from
the digit of matching unit value in the 1st number and borrowing from a higher-unit-value digit when necessary,
and make the answer negative if the larger number was originally the 2nd input to be subtracted*/
Number subtract2Nums(Number largerNum, Number smallerNum, bool secondNumLarger)
{
	int position = largerNum.getLength() - 1;
	// Offset of array indexes for matching same-unit-value digits in nums of differing size
	int lengthDiffOffset = largerNum.getLength() - smallerNum.getLength();
	int borrowerPos;
	int digitsAnswer;
	Number answer;

	answer.setLength(largerNum.getLength());

	// As long as there are digits left in the smaller number to subtract from the larger...
	while ((position - lengthDiffOffset) >= 0)
	{
		borrowerPos = position - 1;
		
		// If the current digit to subtract from is smaller than the other
		if (largerNum.getElement(position) < smallerNum.getElement(position - lengthDiffOffset))
		{
			// Find the next non-0 digit and borrow/carry 1 down through any zeros till the current digit
			while (largerNum.getElement(borrowerPos) == 0)
				borrowerPos--;

			while (borrowerPos < position)
			{
				// (Carrying = digit -1, next digit +10)
				largerNum.setElement(borrowerPos, (largerNum.getElement(borrowerPos) - 1));
				largerNum.setElement((borrowerPos + 1), (largerNum.getElement(borrowerPos + 1) + 10));
				borrowerPos++;
			}
		}

		// Subtract smaller num's digit from larger num's matching-unit-value digit and put result in answer array
		digitsAnswer = largerNum.getElement(position) - smallerNum.getElement(position - lengthDiffOffset);
		answer.setElement(position, digitsAnswer);
		position--;
	}

	// Add any leftover digits from the larger num to the answer array when smaller num digits exhausted
	while (position >= 0)
	{
		answer.setElement(position, largerNum.getElement(position));
		position--;
	}

	// If 2nd num was larger i.e. answer is negative (or numbers were equal)
	if (secondNumLarger)
	{
		position = 0;

		// Find the 1st non-leading-zero digit
		while (answer.getElement(position) == 0 && position < answer.getLength())
		{
			position++;
		}
		// If there's nothing but zeroes (i.e. the numbers were actually equal) return the zero answer
		if (position == answer.getLength())
			return answer;
		
		// Otherwise, set the first non-zero digit to be negative
		answer.setElement(position, (answer.getElement(position) - (2 * answer.getElement(position))));
	}

	return answer;
}