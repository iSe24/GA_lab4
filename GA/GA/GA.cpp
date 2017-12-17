
#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <conio.h>

using namespace std;

const int N = 10;
int startN = 0;
int endN = N - 1;
int A[N][N];
const int L = 500;


int fitness(int *arr) { //работает верно
	int sum = 0;
	int prev = startN;
	int num;

	for (int i = 0; i < (N - 2); i++) {
		num = arr[i];
		sum = sum + A[prev][num];
		prev = num;

	}
	sum = sum + A[prev][endN];

	return sum;
}

int main()
{

	//srand(time(0));
	//создаю начальный массив случайных чисел + проходы
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i != j)
			{
				if ((1 + rand() % 100) < 20)
				{
					A[i][j] = 1000;
				}
				else
				{
					A[i][j] = 1 + rand() % 100;
				}
			}
			else
			{
				A[i][j] = 0;
			}
			cout << A[i][j] << " ";

		}
		cout << endl;
	}
	//генератор работает, далее
	system("pause");
	//тест fitness - работает
	//int B[3] = {1, 2, 3};
	//cout << fitness(B) << endl;

	//Генерируем первое поколение - чекнул и при N=5 и при N=10  все норм 1,2...8
	int parents[L][N - 2];		//
	int j = 0;
	while (j < L) {
		for (int i = 0; i < (N - 2); i++) {
			parents[j][i] = 1 + rand() % (N - 2);
			//cout << parents[j][i];
		}
		//cout << "  fitness" << "=" << fitness(parents[j]) << endl;
		j++;
	}

	//Есть поколение - дальше уже цикл с отбором 
	// отфильтровать 
	int pokolenie = 0;
	while (pokolenie < 20) {

		cout << "Pokolenie #" << pokolenie << endl;
		// генерация детей 
		int g = (N - 2) / 2;
		int son_list[2 * L - 2][N - 2];
		int son_l = 0;
		int son1[N - 2];
		int son2[N - 2];
		for (int n = 0; n < L - 1; n++) {

			int randn = 0 + rand() % L;
			for (int i = 0; i < g; i++) {

				son_list[son_l][i] = parents[n][i];
				son_list[son_l][i + g] = parents[randn][i + g];

				son_list[son_l + 1][i] = parents[randn][i];
				son_list[son_l + 1][i + g] = parents[n][i + g];

			}
			if (fmod((N - 2) / 2, 2) > 0) {
				son_list[son_l][N - 2] = parents[n + 1][N - 2];
				son_list[son_l + 1][N - 2] = parents[n][N - 2];
			}
			son_l = son_l + 2;
		}
		//мутировать будет son_list - еще раз его обойдем и с вероятностю будем
		//менять элементы на фулл рандом - типо приемный, хах
		//плюс с вероятностью будем менять рандомный ген - аля чернобыль
		srand(time(0));
		int muta1 = 0;
		int muta2 = 0;
		for (int j = 0; j < 2 * L - 2; j++) {
			int rand1 = 0 + rand() % (200);
			if (rand1 < 10) {
				for (int i = 0; i < (N - 2); i++) {
					son_list[j][i] = 1 + rand() % (N - 2);
				}
				muta1++;
			}
			if ((rand1 > 10)&(rand1 <= 20)) {

				int pp = fmod(rand1, 10);
				son_list[j][pp] = 1 + rand() % (N - 2);
				muta2++;

			}
		}
		// имеем родителей(L)=parents и детей(2*(L-1))=son_list ->
		//надо как то в новых родителей(L)=population
		int population[3 * L - 2][N - 2];
		for (int i = 0; i <= (3 * L - 2); i++) {
			if (i < L) {
				for (int p = 0; p < N - 2; p++) {
					population[i][p] = parents[i][p];
				}
			}
			else
			{
				for (int p = 0; p < N - 2; p++) {
					population[i][p] = son_list[i - L][p];
				}
			}
		}
		cout << "tekuchya populyachiya" << endl;

		for (int o = 0; o < (3 * L - 2); o++) {
			for (int i = 0; i < N - 2; i++) {
				cout << population[o][i];
			}
			cout << "=" << fitness(population[o]) << endl;
		}

		//получил population = parents+son_list, теперь накая сортировка чтобы оставить лучших L штук (время московское 3-35) хех мда
		//сортировка выбором разве что - РАБОТАЕТ  ЛЕЛ
		cout << "tipo sortirovka" << endl;
		for (int i = 0; i < (3 * L - 2); i++) {
			int minP = i;
			for (int j = i + 1; j < (3 * L - 2); j++) {
				if (fitness(population[minP]) > fitness(population[j]))

					minP = j;
			}
			int tmp[N - 2];
			for (int p = 0; p < N - 2; p++) {
				tmp[p] = population[minP][p];
			}
			for (int p = 0; p < N - 2; p++) {
				population[minP][p] = population[i][p];
			}
			for (int p = 0; p < N - 2; p++) {
				population[i][p] = tmp[p];
			}
		}

		// Теперь надо из сортированной популяции вытащить первые L генов - ez
		j = 0;
		while (j < L) {
			for (int i = 0; i < (N - 2); i++) {
				parents[j][i] = population[j][i];
				
			}
			j++;
		}
		cout << "5 lushih" << endl;
		for (int o = 0; o < 5; o++) {
			for (int i = 0; i < N - 2; i++) {
				cout << parents[o][i];
			}
			cout << "=" << fitness(parents[o]) << endl;
		}
		cout << "priemnih=" << muta1 << endl;
		cout << "mutantov=" << muta2 << endl;
		pokolenie++;
		system("pause");
	}
	cout << "dct" << endl;
	system("pause");
	return 0;
}