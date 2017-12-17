#include "stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;


int number_of_digits(unsigned long int n) {
	int d = 0;
	while (n) { n /= 10; d++; }
	return d;
}

int expand_digit(unsigned long int n, int d) {
	return (n % (unsigned long int)pow(10, d)) / (unsigned long int)pow(10, d - 1);
}

int main() {
	unsigned long int n;
	int d;
	cout << "Введите натуральное число: ";
	cin >> n;
	cout << "Введено число:" << n << endl;
	int digits = number_of_digits(n);
	do {
		cout << "Введите номер извлекаемой цифры (1-" <<
			digits << ", нумерация справа налево): ";
		cin.clear(); cin.sync(); cin >> d;
	} while (d<1 || d>digits);
	cout << "Получена цифра: " << expand_digit(n, d) << endl;
	cin.sync(); cin.get();
	return 0;
}