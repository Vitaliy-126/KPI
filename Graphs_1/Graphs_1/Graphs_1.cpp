#include <iostream>
#include <iomanip>
#include <regex>
#include <Windows.h>
#include <limits>

using namespace std;

double  check_number(const char promt_message[], const char fail_message[]);

int get_natural_int(const double number);

int** arr_create(const int, const int);

void Show_arr(int**, const int, const int);

void massage_arr(int&, int&, int);

void adjacency_graph(int**&, const int, const int, int, int);

void incidence_graph(int**&, const int, const int, int, int, int);

void incidence_and_adjacency_graphs_output(int**, int**, const int, const int);

void clear_arr(int**, const int);

int menu(int, int, int**, int**);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n = get_natural_int(check_number("Введіть кількість вершин та ребер графу(натуральне число):", "Перевірте правильність ввідних даних"));
	int m = get_natural_int(check_number("", "Перевірте правильність ввідних даних"));
	int** arr = arr_create(n, m);
	int** arr_adj = arr_create(n, n);
	incidence_and_adjacency_graphs_output(arr, arr_adj, n, m);
	menu(n, m, arr, arr_adj);
	system("pause");
	return 0;
}

int menu(int n, int m, int** arr, int** arr_adj) {
	cout << "Виберіть потрібний вам пункт меню." << endl;
	cout << "Меню:" << endl << "0. Ввести новий граф." << endl << "1. Вивести матрицю інцидентності" << endl << "2. Вивести матрицю суміжності." << endl << "3. Зупинити виконання програми" << endl;;
	while (true) {
		int temp_menu;
		cin >> temp_menu;
		switch (temp_menu) {
		case 0: {
			clear_arr(arr, n);
			clear_arr(arr_adj, n);
			int n = get_natural_int(check_number("Введіть кількість вершин та ребер графу(натуральні числа):", "Перевірте правильність ввідних даних"));
			int m = get_natural_int(check_number("", "Перевірте правильність ввідних даних"));
			int** arr = arr_create(n, m);
			int** arr_adj = arr_create(n, n);
			incidence_and_adjacency_graphs_output(arr, arr_adj, n, m);
			break;
		}
		case 1: {
			cout << "Тримайте матрицю інцидентності:" << endl;
			Show_arr(arr, n, m);
			break;
		}
		case 2: {
			cout << "Тримайте матрицю суміжності:" << endl;
			Show_arr(arr_adj, n, n);
			break;
		}
		case 3: {
			cout << "Дякую за користування" << endl;
			clear_arr(arr, n);
			clear_arr(arr_adj, n);
			return 0;
			break;
		}
		default: {
			cout << "Оберіть один із пунктів меню." << endl;
			break;
		}
		}
	}
}

int** arr_create(const int n, const int m) {
	int** arr = new int* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[m];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = 0;
		}
	}
	return arr;
}

void Show_arr(int** arr, const int n, const int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << setw(3) << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

void massage_arr(int& v, int& u, int m) {
	v = get_natural_int(check_number("Введіть початкову вершину ребра графу та кінцеву:", "Перевірте ввід"));
	u = get_natural_int(check_number(" ", "Перевірте ввід"));
	while (v > m || u > m) {
		cout << "Вершина ребра графу повинна бути <= кількості висот." << endl;
		v = get_natural_int(check_number("Введіть початкову вершину ребра графу та кінцеву:", "Перевірте ввід"));
		u = get_natural_int(check_number(" ", "Перевірте ввід"));
	}
}

void adjacency_graph(int**& arr_adj, const int n, const int m, int v, int u) {
	for (int k = 0; k < n; k++) {
		for (int m = 0; m < n; m++) {
			arr_adj[v - 1][u - 1] = 1;
			if (u == v) {
				arr_adj[v - 1][u - 1] = 1;
			}
		}
	}
}

void incidence_graph(int**& arr, const int n, const int m, int v, int u, int e) {
	for (int j = 0; j < m; j++) {
		arr[v - 1][e] = -1;
		arr[u - 1][e] = 1;
		if (u == v) {
			arr[u - 1][e] = 2;
		}
	}
}

void incidence_and_adjacency_graphs_output(int** arr, int** arr_adj, const int n, const int m) {
	int v = 0, u = 0, e = -1;
	for (int i = 0; i < m; i++) {
		massage_arr(v, u, n);
		e++;
		incidence_graph(arr, n, m, v, u, e);
		adjacency_graph(arr_adj, n, m, v, u);
	}
}

void clear_arr(int** arr, const int n) {
	for (int i = 0; i < n; i++) {
		delete[]arr[i];
	}
	delete[]arr;
}

double  check_number(const char promt_message[], const char fail_message[])
{
	cout << promt_message << "\n";
	string str;
	cin >> str;
	regex regular("([\\-]?)"
		"([\\d]+)"
		"([\\.]?)"
		"([\\d]*)");
	while ((regex_match(str.c_str(), regular)) == 0)
	{
		cout << fail_message << "\n";
		cout << "------------------------------------" << "\n";
		cout << promt_message << "\n";
		cin >> str;
		if (regex_match(str.c_str(), regular))
		{
			return stod(str.c_str());
		}
	}
	return stod(str.c_str());
}

int get_natural_int(const double number)
{
	if ((double)INT_MAX >= number && (double)INT_MIN <= number)
	{
		if (number == (int)number && number > 0)
		{
			return (int)number;
		}
		else
		{
			cout << "Ви ввели не натуральне число" << endl;
			cout << "----------------------------" << endl;
			return get_natural_int(check_number("Введіть натуральне число:", "Перевірте ввід."));
		}
	}
	else
	{
		cout << "int не вічний(" << endl;
		cout << "-------------" << endl;
		return get_natural_int(check_number("Введіть натуральне число:", "Перевірте ввід."));
	}
}
