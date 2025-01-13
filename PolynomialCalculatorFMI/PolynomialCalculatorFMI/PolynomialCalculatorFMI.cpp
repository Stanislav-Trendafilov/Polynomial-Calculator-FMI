// Project04.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <windows.h> 
#include <utility>
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

void simplifyFraction(int& numerator, int& denominator) {
    int commonDivisor = gcd(numerator, denominator);
    numerator /= commonDivisor;
    denominator /= commonDivisor;
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
                    std::cout << polynom1[i].first << "x^" << polynomialDegree - i;
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
}
//1 function
void sumOfPolynomials(std::vector<std::pair<int, int>>& polynom1, std::vector<std::pair<int, int>>& polynom2, int degree1, int degree2)
{
    if (degree1 > degree2)
    {
        for (size_t i = 0; i < degree1; i++)
        {

        }
    }
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

    std::cout << "Enter Polynomial Q(X): " << std::endl;
    std::cout << "Enter degree of your polynomial: ";
    std::cin >> polynomialDegree2;
    std::vector<std::pair<int, int>> polynom2;
    enterPolynomialCoeff(polynomialDegree2, polynom2);
    printPolynomial(polynom2, polynomialDegree2);

    if (function == 1)
    {
        //  sumOfPolynomials(polynom1, polynom2,polynomialDegree,polynomialDegree2);
    }
}

int main()
{
    system("Color 0A");
    std::cout << "       Welcome to my final project for this course - Polynomial Calculator" << std::endl;
    std::cout << "It is a mini project intended to work with polynomials with rational coefficients." << std::endl;

    runPolynomialCalculations();

}