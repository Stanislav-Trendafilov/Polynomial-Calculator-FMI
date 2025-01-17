// Project04.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <windows.h> 
#include <vector>
#include "PolynomialCalculatorFMI.h"

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

//

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

double findRoot(const std::vector<double>& coefficients)
{
	int constantTerm = static_cast<int>(coefficients.back());
	int leadingCoefficient = static_cast<int>(coefficients.front());

	std::vector<int> possibleNumerators = findDivisors(constantTerm);
	std::vector<int> possibleDenominators = findDivisors(leadingCoefficient);

	for (int numerator : possibleNumerators)
	{
		for (int denominator : possibleDenominators)
		{
			double root = static_cast<double>(numerator) / denominator;

			double result = 0.0;
			for (size_t i = 0; i < coefficients.size(); ++i)
			{
				result = result * root + coefficients[i];
			}
			if (std::fabs(result) < 1e-6)
			{
				return root;
			}
		}
	}
	return NAN;
}

std::vector<double> syntheticDivision(const std::vector<double>& coefficients, double root)
{
	std::vector<double> newCoefficients;
	double temp = 0.0;

	for (double coef : coefficients) {
		temp = temp * root + coef;
		newCoefficients.push_back(temp);
	}

	newCoefficients.pop_back();
	return newCoefficients;
}

void factorizePolynomial(std::vector<double> coefficients) {
	std::cout << "Разлагане на полинома:" << std::endl;

	while (coefficients.size() > 2)
	{
		double root = findRoot(coefficients);
		if (std::isnan(root))
		{
			std::cout << "Не мога да намеря рационален корен." << std::endl;
			return;
		}

		std::cout << "(x - " << root << ")";
		coefficients = syntheticDivision(coefficients, root);
	}

	std::cout << "(" << coefficients[0] << "x + " << coefficients[1] << ")" << std::endl;
}

//

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

		simplifyFraction(numerator, denominator);

		newPolynom.push_back(newCoef);
	}

	printPolynomial(newPolynom, startFromSameDegree + difference);
}

//2 function 
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
			numerator = polynom1[j + difference].first * polynom2[j].second - polynom1[j + difference].second * polynom2[j].first;
			denominator = polynom1[j + difference].second * polynom2[j].second;
		}
		else
		{
			numerator = polynom1[j].first * polynom2[j + difference].second - polynom1[j].second * polynom2[j + difference].first;
			denominator = polynom1[j].second * polynom2[j + difference].second;
		}

		simplifyFraction(numerator, denominator);

		newCoef.first = numerator;
		newCoef.second = denominator;

		newPolynom.push_back(newCoef);
	}

	printPolynomial(newPolynom, startSameDegree + difference);
}

//3 function
void multiplicationOfPolynomials(std::vector<std::pair<int, int>>& polynom1, std::vector<std::pair<int, int>>& polynom2, int degree1, int degree2)
{
	std::vector<std::pair<int, int>> newPolynom(polynom1.size() + polynom2.size() - 1);

	for (size_t i = 0; i <= degree1; i++) {
		for (size_t j = 0; j <= degree2; j++) {

			int numerator = polynom1[i].first * polynom2[j].first;
			int denominator = polynom1[i].second * polynom2[j].second;

			simplifyFraction(numerator, denominator);

			if (newPolynom[i + j].first != 0)
			{
				int commonDenominator = newPolynom[i + j].second * denominator;
				numerator = numerator * (commonDenominator / denominator) + newPolynom[i + j].first * (commonDenominator / newPolynom[i + j].second);
				denominator = commonDenominator;
				simplifyFraction(numerator, denominator);
			}

			newPolynom[i + j].first = numerator;
			newPolynom[i + j].second = denominator;
		}
	}
	printPolynomial(newPolynom, polynom1.size() + polynom2.size() - 2);
}

//5 function - ready
void multiplicationWithScalar(std::vector<std::pair<int, int>>& polynom1, int degree1)
{
	std::vector<std::pair<int, int>> newPolynom;

	std::pair<int, int>scalar;

	char input[MAX_BUFFER_SIZE];
	std::cout << "Enter value of the scalar: ";
	std::cin >> input;

	processingCoefficients(input, scalar);

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

		break;
	case 5:
		multiplicationWithScalar(polynom1, polynomialDegree);
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