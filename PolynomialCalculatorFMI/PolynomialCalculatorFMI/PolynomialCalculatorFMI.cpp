// Project04.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <windows.h> 
#include <vector>

const int MAX_BUFFER_SIZE = 512;

int mathAbs(int num)
{
	if (num < 0)
	{
		return -num;
	}
	return num;

}

int mathPow(int num, int degree)
{
	int numByDegree = 1;
	for (size_t i = 0; i < degree; i++)
	{
		numByDegree = numByDegree * num;
	}
	return numByDegree;
}

void chooseFunctionText()
{
	std::cout << std::endl;
	std::cout << "Choose one of the following functionalities:" << std::endl;
	std::cout << "1) Sum of polynomials" << std::endl;
	std::cout << "2) Substraction of polynomials" << std::endl;
	std::cout << "3) Multiplication of polynomials" << std::endl;
	std::cout << "4) Division of polynomials" << std::endl;
	std::cout << "5) Multiply polynomial by scalar" << std::endl;
	std::cout << "6) Find value of polynomial at a given number" << std::endl;
	std::cout << "7) Find GCD of two polynomials" << std::endl;
	std::cout << "8) Display Vieta's formulas for a given polynomial" << std::endl;
	std::cout << "9) Represent a polynomial in powers of (x+a)" << std::endl;
	std::cout << "10) Factor polynomial and find its rational roots" << std::endl;
	std::cout << "11) Quit program" << std::endl;
}

int gcd(int a, int b) {
	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}
	return mathAbs(a);
}

int lcm(int a, int b) 
{
	return (a / gcd(a, b)) * b;
}

void simplifyFraction(int& numerator, int& denominator)
{
	int commonDivisor = gcd(numerator, denominator);
	numerator /= commonDivisor;
	denominator /= commonDivisor;
}

std::pair<int, int> addFractions(std::pair<int, int>& a,std::pair<int, int>& b) 
{
	int numerator = a.first * b.second + b.first * a.second;
	int denominator = a.second * b.second;
	simplifyFraction(numerator, denominator);
	return std::pair<int,int>(numerator, denominator);
}

std::pair<int, int> subtractFractions(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	int numerator = a.first * b.second - b.first * a.second;
	int denominator = a.second * b.second;
	simplifyFraction(numerator, denominator);
	return std::pair<int, int>(numerator, denominator);
}

std::pair<int, int> multiplyFractions(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	int numerator = a.first * b.first;
	int denominator = a.second * b.second;
	simplifyFraction(numerator, denominator);
	return std::pair<int, int>(numerator, denominator);
}

std::pair<int, int> divideFractions(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	int numerator = a.first * b.second;
	int denominator = a.second * b.first;
	simplifyFraction(numerator, denominator);
	return std::pair<int, int>(numerator, denominator);
}

void processingCoefficients(char input[MAX_BUFFER_SIZE], std::pair<int, int>& ratCoef)
{
	int c = 0, firstCoef = 0, secondCoef = 0, digitMove = 1, isNegative = 1;

	if (input[c] == 0)
	{
		firstCoef = 0;
		secondCoef = 1;
	}

	if (input[c] == '-')
	{
		isNegative = -1;
		c++;
	}

	while (input[c] != '/' && input[c] != '\0')
	{
		int currentDigit = input[c] - '0';
		firstCoef = firstCoef * digitMove + currentDigit;
		digitMove = 10;
		c++;
	}
	//putValue - denominator
	if (input[c++] == '/')
	{
		while (input[c] != '\0')
		{
			int currentDigit = input[c] - '0';
			secondCoef = secondCoef * digitMove + currentDigit;
			digitMove = 10;
			c++;
		}
	}
	else
	{
		secondCoef = 1;
	}

	firstCoef *= isNegative;

	simplifyFraction(firstCoef, secondCoef);

	ratCoef.first = firstCoef;
	ratCoef.second = secondCoef;
}

void enterPolynomialCoeff(const int polynomialDegree, std::vector<std::pair<int, int>>& polynom)
{
	for (size_t i = 0; i <= polynomialDegree; i++)
	{
		std::cout << "Enter coefficient before x^" << polynomialDegree - i << " = ";
		char input[MAX_BUFFER_SIZE];
		std::cin >> input;

		std::pair<int, int>ratCoef;
		processingCoefficients(input, ratCoef);

		polynom.push_back(ratCoef);
	}
}

void printPolynomial(std::vector<std::pair<int, int>>& polynom1, int polynomialDegree)
{
	std::cout << "This is the input polynomial: ";
	for (int i = 0; i < polynom1.size(); ++i)
	{
		if (i > 0 && polynom1[i].first > 0)
		{
			std::cout << "+";
		}
		if (polynom1[i].second == 1)
		{
			if (polynom1[i].first != 0)
			{
				if (i == polynom1.size() - 1)
				{
					std::cout << polynom1[i].first;
				}
				else
				{
					if (polynom1[i].first != 1)
					{
						std::cout << polynom1[i].first << "x^" << polynomialDegree - i;
					}
					else
					{
						std::cout << "x^" << polynomialDegree - i;
					}
				}
			}
		}
		else
		{
			if (i == polynom1.size() - 1)
			{
				std::cout << polynom1[i].first << "/" << polynom1[i].second;
			}
			else
			{
				std::cout << polynom1[i].first << "/" << polynom1[i].second << "x^" << polynomialDegree - i;
			}
		}
	}
	std::cout << std::endl;
}

void printValueOfPolynom(std::pair<int, int> scalar, std::pair<int, int> valueOfPolynomial)
{
	if (scalar.second == 1)
	{
		if (valueOfPolynomial.second == 1)
		{
			std::cout << "P(" << scalar.first << ") = " << valueOfPolynomial.first;
		}
		else
		{
			std::cout << "P(" << scalar.first << ") = " << valueOfPolynomial.first << "/" << valueOfPolynomial.second;
		}
	}
	else
	{
		if (valueOfPolynomial.second == 1)
		{
			std::cout << "P(" << scalar.first << "/" << scalar.second << ") = " << valueOfPolynomial.first;
		}
		else
		{
			std::cout << "P(" << scalar.first << "/" << scalar.second << ") = " << valueOfPolynomial.first << "/" << valueOfPolynomial.second;
		}
	}
}

int  findLcmOfDenominators(std::vector<std::pair<int, int>>& polynom1)
{
	int currentLcm = 1;
	for (size_t i = 0; i < polynom1.size(); i++)
	{
		currentLcm = lcm(polynom1[i].second, currentLcm);
	}

	return currentLcm;
}

std::vector<int> findDivisors(int n)
{
	std::vector<int> divisors;
	for (int i = 1; i <= n; ++i)
	{
		if (n % i == 0)
		{
			divisors.push_back(i);
			divisors.push_back(-i);
		}
	}
	return divisors;
}

void changeRoot(int& numerator, int& denominator)
{
	if (numerator < 0 && denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}
	else if (numerator > 0 && denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}
}

bool checkIfAlreadyRootExists(std::vector<std::pair<int, int>> allPossibleRoots, std::pair<int, int> possibleRoot)
{
	for (size_t i = 0; i < allPossibleRoots.size(); i++)
	{
		if (allPossibleRoots[i].first == possibleRoot.first &&
			allPossibleRoots[i].second == possibleRoot.second)
		{
			return true;
		}
	}  
	return false;
}

std::vector<std::pair<int, int>> findAllPossibleRoots(int firstCoef, int lastCoef)
{
	std::vector<std::pair<int, int>> allPossibleRoots;

	std::vector<int>possibleRootsFromFirstCoef=findDivisors(firstCoef);
	std::vector<int>possibleRootsFromSecondCoef = findDivisors(lastCoef);

	for (size_t i = 0; i < possibleRootsFromSecondCoef.size(); i++)
	{
		for (size_t j = 0; j < possibleRootsFromFirstCoef.size(); j++)
		{
			std::pair<int, int>possibleRoot;

			changeRoot(possibleRootsFromSecondCoef[i], possibleRootsFromFirstCoef[j]);

			possibleRoot.first = possibleRootsFromSecondCoef[i];
			possibleRoot.second = possibleRootsFromFirstCoef[j];

			if (checkIfAlreadyRootExists(allPossibleRoots, possibleRoot)==false)
			{
				allPossibleRoots.push_back(possibleRoot);
			}	
		}
	}
	
	return allPossibleRoots;
}

//1 function - ready
void sumOfPolynomials(std::vector<std::pair<int, int>>& polynom1, std::vector<std::pair<int, int>>& polynom2, int degree1, int degree2)
{
	std::vector<std::pair<int, int>> newPolynom;

	int startFromSameDegree = degree1, difference = 0;;

	if (degree1 > degree2)
	{
		difference = degree1 - degree2;
		for (size_t i = 0; i < difference; i++)
		{
			newPolynom.push_back(polynom1[i]);
		}
		startFromSameDegree = degree2;
	}
	if (degree2 > degree1)
	{
		difference = degree2 - degree1;
		for (size_t i = 0; i < difference; i++)
		{
			newPolynom.push_back(polynom2[i]);
		}
	}
	for (int j = 0; j <= startFromSameDegree; j++)
	{
		int numerator, denominator;
		std::pair<int, int>newCoef;

		if (degree1 > degree2)
		{
			newCoef = addFractions(polynom1[j + difference], polynom2[j]);
		}
		else
		{
			newCoef = addFractions(polynom1[j], polynom2[j + difference]);
		}

		newPolynom.push_back(newCoef);
	}

	printPolynomial(newPolynom, startFromSameDegree + difference);
}

//2 function - ready
void substractionOfPolynomials(std::vector<std::pair<int, int>>& polynom1, std::vector<std::pair<int, int>>& polynom2, int degree1, int degree2)
{
	std::vector<std::pair<int, int>> newPolynom;

	int startSameDegree = degree1, difference = 0;;

	if (degree1 > degree2)
	{
		difference = degree1 - degree2;
		for (size_t i = 0; i < difference; i++)
		{
			newPolynom.push_back(polynom1[i]);
		}
		startSameDegree = degree2;
	}
	if (degree2 > degree1)
	{
		difference = degree2 - degree1;
		for (size_t i = 0; i < difference; i++)
		{
			polynom2[i].first *= -1;
			newPolynom.push_back(polynom2[i]);
		}
	}
	for (int j = 0; j <= startSameDegree; j++)
	{
		int numerator, denominator;
		std::pair<int, int>newCoef;

		if (degree1 > degree2)
		{
			newCoef = subtractFractions(polynom1[j + difference], polynom2[j]);
		}
		else
		{
			newCoef = subtractFractions(polynom1[j], polynom2[j + difference]);
		}

		newPolynom.push_back(newCoef);
	}

	printPolynomial(newPolynom, startSameDegree + difference);
}

//3 function - ready
void multiplicationOfPolynomials(std::vector<std::pair<int, int>>& polynom1, std::vector<std::pair<int, int>>& polynom2, int degree1, int degree2)
{
	std::vector<std::pair<int, int>> newPolynom(polynom1.size() + polynom2.size() - 1);

	for (size_t i = 0; i <= degree1; i++) {
		for (size_t j = 0; j <= degree2; j++) {

			std::pair<int, int>newCoef;

			newCoef = multiplyFractions(polynom1[i], polynom2[j]);

			if (newPolynom[i + j].first != 0)
			{
				newCoef = addFractions(newPolynom[i + j], newCoef);
			}

			newPolynom[i + j].first = newCoef.first;
			newPolynom[i + j].second = newCoef.second;
		}
	}
	printPolynomial(newPolynom, polynom1.size() + polynom2.size() - 2);
}

//4 function
void dividePolynomials(std::vector<std::pair<int, int>>& dividend, std::vector<std::pair<int, int>>& divisor,int degree1,int degree2) 
{	
	std::vector<std::pair<int, int>> remainder;
	std::vector<std::pair<int, int>> quotient;

	while (!remainder.empty() /* && remainder[0] >= divisor[0].second*/)
	{
		// ����������� �� ������� ���������� � ������ �� ������� ������ ����
		int coefQuot = dividend[0].first / divisor[0].first;
		int degreeQuot = dividend.size() - divisor.size();

		// �������� �� ������� ���� ��� ��������
		quotient.push_back({ coefQuot, degreeQuot });

		// ��������� �� ��� �������: ������� ���� �� �������� ������� �� ��������
		std::vector<std::pair<int, int>> currentTerm;
		for (const auto& term : divisor) {
			currentTerm.push_back({ term.first * coefQuot, term.second + degreeQuot });
		}

		// ��������� �� ������� ���� �� ��������
		std::vector<std::pair<int, int>> newRemainder;
		size_t i = 0, j = 0;
		while (i < remainder.size() || j < currentTerm.size())
		{
			if (i < remainder.size() && (j >= currentTerm.size() || remainder[i].second > currentTerm[j].second)) {
				newRemainder.push_back(remainder[i]);
				i++;
			}
			else if (j < currentTerm.size() &&(i >= remainder.size() || remainder[i].second < currentTerm[j].second))
			{
				newRemainder.push_back({ -currentTerm[j].first, currentTerm[j].second });
				j++;
			}
			else 
			{
				int newCoef = remainder[i].first - currentTerm[j].first;
				if (newCoef != 0) {
					newRemainder.push_back({ newCoef, remainder[i].second });
				}
				i++;
				j++;
			}
		}
		remainder = newRemainder;
	}

	printPolynomial(quotient, quotient.size()-1);
	printPolynomial(remainder, remainder.size());
}

//5 function - ready
void multiplicationWithScalar(std::vector<std::pair<int, int>>& polynom1, int degree1, std::pair<int, int>scalar)
{
	std::vector<std::pair<int, int>> newPolynom;

	for (int j = 0; j <= degree1; j++)
	{
		int numerator, denominator;
		std::pair<int, int>newCoef;

		numerator = polynom1[j].first * scalar.first;
		denominator = polynom1[j].second * scalar.second;

		simplifyFraction(numerator, denominator);
		newCoef = std::make_pair(numerator, denominator);

		newPolynom.push_back(newCoef);
	}

	printPolynomial(newPolynom, degree1);
}

//6 function - ready
void findValueWithGivenNum(std::vector<std::pair<int, int>>& polynom1, int degree1)
{
	char input[MAX_BUFFER_SIZE];
	std::cout << "Enter value of the x: ";
	std::cin >> input;

	std::pair<int, int>scalar;

	processingCoefficients(input, scalar);

	std::pair<int, int>valueOfPolynomial(0,1);	//it is (0,1) in order not to make the denominator 0 while adding

	for (int j = 0; j <= degree1; j++)
	{
		int newNumerator, newDenominator;

		newNumerator = polynom1[j].first * mathPow(scalar.first, degree1 - j);
		newDenominator = polynom1[j].second * mathPow(scalar.second, degree1 - j);

		std::pair<int, int>newCoef;
		newCoef.first = newNumerator;
		newCoef.second = newDenominator;

		valueOfPolynomial = addFractions(valueOfPolynomial, newCoef);
	}												

	printValueOfPolynom(scalar, valueOfPolynomial);
}

//10 function
void factorPolynomial(std::vector<std::pair<int, int>>& polynom1, int degree1)
{
	int lcm =findLcmOfDenominators(polynom1);

	std::pair<int, int>scalarToRemoveDenominators;
	scalarToRemoveDenominators.first = lcm;
	scalarToRemoveDenominators.second = 1;

	std::cout << "--Removing denominators to work with whole nums--"<<std::endl;
	multiplicationWithScalar(polynom1, degree1, scalarToRemoveDenominators);

	int firstCoef = polynom1[0].first;
	int lastCoef = polynom1[degree1].first;

	std::vector<std::pair<int, int>> allPossibleRoots;

	allPossibleRoots = findAllPossibleRoots(firstCoef, lastCoef);

}

// 11 function
void quitProgram()
{
	std::cout << "Have a nice day :)";
	return;
}

void runPolynomialCalculations()
{
	int function;
	chooseFunctionText();
	std::cin >> function;

	if (function < 1 || function>11)
	{
		std::cout << "Invalid input, you have to enter number between 1 and 11.";
		return;
	}

	if (function == 11)
	{
		return quitProgram();
	}

	int polynomialDegree, polynomialDegree2;
	std::cout << "Enter Polynomial P(X): " << std::endl;
	std::cout << "Enter degree of your polynomial: ";
	std::cin >> polynomialDegree;
	std::vector<std::pair<int, int>> polynom1;
	enterPolynomialCoeff(polynomialDegree, polynom1);
	printPolynomial(polynom1, polynomialDegree);
	std::cout << std::endl;

	std::vector<std::pair<int, int>> polynom2;
	//check if function needs second polynomial
	if (function == 1 || function == 2 || function == 3 || function == 4)
	{
		std::cout << "Enter Polynomial Q(X): " << std::endl;
		std::cout << "Enter degree of your polynomial: ";
		std::cin >> polynomialDegree2;
		enterPolynomialCoeff(polynomialDegree2, polynom2);
		printPolynomial(polynom2, polynomialDegree2);
	}
	
	char input[MAX_BUFFER_SIZE];
	std::pair<int, int>scalar;

	switch (function)
	{
	case 1:
		sumOfPolynomials(polynom1, polynom2, polynomialDegree, polynomialDegree2);
		break;
	case 2:
		substractionOfPolynomials(polynom1, polynom2, polynomialDegree, polynomialDegree2);
		break;
	case 3:
		multiplicationOfPolynomials(polynom1, polynom2, polynomialDegree, polynomialDegree2);
		break;
	case 4:
		dividePolynomials(polynom1, polynom2, polynomialDegree, polynomialDegree2);
		break;
	case 5:
		std::cout << "Enter value of the scalar: ";
		std::cin >> input;

		processingCoefficients(input, scalar);
		multiplicationWithScalar(polynom1, polynomialDegree,scalar);
		break;
	case 6:
		findValueWithGivenNum(polynom1, polynomialDegree);
		break;
	case 7:

		break;
	case 8:

		break;
	case 9:

		break;
	case 10:
		factorPolynomial(polynom1, polynomialDegree);
		break;
	default:
		break;
	}

}

int main()
{
	system("Color 0A");
	std::cout << "       Welcome to my final project for this course - Polynomial Calculator" << std::endl;
	std::cout << "It is a mini project intended to work with polynomials with rational coefficients." << std::endl;

	runPolynomialCalculations();

}