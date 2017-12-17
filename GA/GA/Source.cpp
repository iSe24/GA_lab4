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
	cout << "������� ����������� �����: ";
	cin >> n;
	cout << "������� �����:" << n << endl;
	int digits = number_of_digits(n);
	do {
		cout << "������� ����� ����������� ����� (1-" <<
			digits << ", ��������� ������ ������): ";
		cin.clear(); cin.sync(); cin >> d;
	} while (d<1 || d>digits);
	cout << "�������� �����: " << expand_digit(n, d) << endl;
	cin.sync(); cin.get();
	return 0;
}