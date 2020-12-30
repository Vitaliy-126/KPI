//Винник лаба3
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <regex>
#include <limits>
#include <queue>
#include <stack>

using namespace std;

int input_vertex(const int);

int** Fill_matrix_of_vertex(const int, const int);

int** Fill_matrix_of_zero(const int, const int);

int* create_vector(const int n);

int** adjacency_graph(int**, const int, const int);

void search_in_width(int**, const int);

void search_in_depth(int**, const int);

void clear_arr(int**, const int);

void print_queue(queue <int>);

void print_stack(stack <int>);

int menu(int**, const int);

double  check_number();

int get_natural_int(const double number);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введіть кількість вершин та ребер графу:" << endl;

	int n = get_natural_int(check_number()); //кількість вершин

	int m = get_natural_int(check_number()); //кількість ребр

	cout << "Введіть вершини ребер графу:" << endl;
	int** vertex = Fill_matrix_of_vertex(m, n); //заповнюємо матрицю розміру mx2 вершинами

	int** adjacency_matrix = adjacency_graph(vertex, n, m); //будуємо матрицю суміжності

	clear_arr(vertex, m);

	menu(adjacency_matrix, n);

	system("pause");
	return 0;
}

int menu(int** matrix_adj, const int n) {
	cout << "Виберіть потрібний вам пункт меню." << endl;
	cout << "Меню:" << endl
		<< "0. Завершити виконання програми." << endl
		<< "1. Вивести протокол обходу графу пошуком вшир." << endl
		<< "2. Вивести протокол обходу графу пошуком углиб" << endl;
	while (true) {
		int temp_menu;
		cout << "[Меню 0-2]Ваш вибір: ";
		temp_menu = (int)check_number();
		switch (temp_menu) {
		case 0: {
			clear_arr(matrix_adj, n);
			cout << "Дякую за користування." << endl;
			return 0;
			break;
		}
		case 1: {
			search_in_width(matrix_adj, n);
			break;
		}
		case 2: {
			search_in_depth(matrix_adj, n);
			break;
		}
		default: {
			cout << "Оберіть один із пунктів меню." << endl;
			break;
		}
		}
	}
}

int input_vertex(const int n) {
	int v;
	v = get_natural_int(check_number());
	while (v > n) {
		cout << "Вершина ребра графу повинна бути <= кількості вершин." << endl;
		v = get_natural_int(check_number());
	}
	return v;
}

int** Fill_matrix_of_vertex(const int m, const int n) {
	int** arr = new int* [m];
	for (int i = 0; i < m; i++) {
		arr[i] = new int[2];
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 2; j++) {
			arr[i][j] = input_vertex(n);
		}
	}
	return arr;
}

int** Fill_matrix_of_zero(const int rows, const int cols) {
	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++) {
		arr[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			arr[i][j] = 0;
		}
	}
	return arr;
}

void search_in_width(int** arr_adj, const int n) {
	int initial_vertex;
	cout << "Введіть вершину, з якої почнемо обхід: ";
	initial_vertex = get_natural_int(check_number());
	cout << endl;
	while (initial_vertex > n) {
		cout << "Вершина повинна бути <= загальній к-ті вершин" << endl;
		initial_vertex = get_natural_int(check_number());
	}
	cout << "Вершина" << setw(15) << "BFS-номер" << setw(17) << "Вміст черги" << endl;
	queue <int> Q; //створюємо чергу
	int* bypassed_vertex = create_vector(n); //створюємо масив для позначення пройдених вершин
	bypassed_vertex[initial_vertex - 1] = 1;
	Q.push(initial_vertex);
	int k = 1;
	cout << initial_vertex << setw(13) << k << setw(15) << initial_vertex << endl;
	while (!Q.empty()) {
		int v = Q.front();
		for (int i = 0; i < n; i++) {
			if (arr_adj[v - 1][i] == 1 && bypassed_vertex[i] == 0) //
			{
				k = k + 1;
				cout << i + 1 << setw(13) << k << setw(15);
				bypassed_vertex[i] = 1;
				Q.push(i + 1);
				print_queue(Q);
			}
		}
		Q.pop();
		cout << "-" << setw(13) << "-" << setw(15);
		print_queue(Q);
	}
	delete[]bypassed_vertex;
}

void search_in_depth(int** arr_adj, const int n) {
	int initial_vertex;
	cout << "Введіть вершину, з якої почнемо обхід: ";
	initial_vertex = get_natural_int(check_number());
	cout << endl;
	while (initial_vertex > n) {
		cout << "Вершина повинна бути <= загальній к-ті вершин" << endl;
		initial_vertex = get_natural_int(check_number());
	}
	cout << "Вершина" << setw(15) << "DFS-номер" << setw(17) << "Вміст стеку" << endl;
	stack <int> S; //створюємо стек
	int* bypassed_vertex = create_vector(n); //створюємо масив для позначення пройдених вершин
	bypassed_vertex[initial_vertex - 1] = 1;
	S.push(initial_vertex);
	int k = 1;
	cout << initial_vertex << setw(13) << k << setw(15) << initial_vertex << endl;
	while (!S.empty()) {
		int v = S.top();
		for (int i = 0; i < n; i++) {
			if (arr_adj[v - 1][i] == 1 && bypassed_vertex[i] == 0) //
			{
				k = k + 1;
				cout << i + 1 << setw(13) << k << setw(15);
				bypassed_vertex[i] = 1;
				S.push(i + 1);
				print_stack(S);
				v = i + 1;
				i = -1;
			}
		}
		S.pop();
		cout << "-" << setw(13) << "-" << setw(15);
		print_stack(S);
	}
	delete[]bypassed_vertex;
}

int* create_vector(const int n) {
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = 0;
	}
	return arr;
}

void print_queue(queue<int> queue) {
	while (!queue.empty()) {
		int val = queue.front();
		cout << val << " ";
		queue.pop();
	}
	cout << endl;
}

void print_stack(stack<int> stack) {
	while (!stack.empty()) {
		int val = stack.top();
		cout << val << " ";
		stack.pop();
	}
	cout << endl;
}

int** adjacency_graph(int** vertex, const int n, const int m) {
	int** matrix_of_adjacency = Fill_matrix_of_zero(n, n); //створюємо та заповнюємо матрицю розміру nxn нулями
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < m; k++) {
				if ((vertex[k][0] == j && vertex[k][1] == i) || (vertex[k][0] == i && vertex[k][1] == j)) {
					matrix_of_adjacency[j - 1][i - 1] = 1;
					break;
				}
			}
		}
	}
	return matrix_of_adjacency;
}

void clear_arr(int** arr, const int n) {
	for (int i = 0; i < n; i++) {
		delete[]arr[i];
	}
	delete[]arr;
}

double  check_number()
{
	string str;
	cin >> str;
	regex regular("([\\-]?)"
		"([\\d]+)"
		"((\\.)(\\d)+|(\\d)*)");
	while ((regex_match(str.c_str(), regular)) == 0)
	{
		cout << "Проверьте ввод." << "\n";
		cout << "---------------" << "\n";
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
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
			cout << "Вы ввели не натуральное число" << endl;
			cout << "-----------------------------" << endl;
			cout << "Введите натуральное число:" << endl;
			return get_natural_int(check_number());
		}
	}
	else
	{
		cout << "int не вечен(" << endl;
		cout << "-------------" << endl;
		return get_natural_int(check_number());
	}
}
