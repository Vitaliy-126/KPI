#include <iostream>
#include <Windows.h>
#include <regex>
#include <limits>

using namespace std;

int input_vertex(const int);

int** Fill_matrix_of_vertex(const int, const int);

int** Fill_matrix_of_zero(const int, const int);

int** adjacency_graph(int**, const int, const int);

int** matrix_of_adj_with_null(int**, const int);

void degree(int**, int**, int**, const int n);

int** matrix_of_distance(int**, const int n);

int** matrix_of_reachability(int**, const int);

int* list_of_eccentricity(int**, const int);

void characteristics_of_graph(int**, const int n);

int menu(int**, int**, int**, const int);

void Show_matrix(int**, const int, const int);

void clear_arr(int**, const int);

double  check_number();

int get_natural_int(const double number);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введіть кількість вершин та ребер неорієнтованого графу :" << endl;

	int n = get_natural_int(check_number()); //кількість вершин
	int m = get_natural_int(check_number()); //кількість ребр

	cout << "Введіть вершини ребер графу:" << endl;
	int** vertex = Fill_matrix_of_vertex(m, n); //заповнюємо матрицю розміру mx2 вершинами

	int** adjacency_matrix = adjacency_graph(vertex, n, m); //будуємо матрицю суміжності

	clear_arr(vertex, m);

	int** distance_matrix = matrix_of_distance(adjacency_matrix, n); //будуємо матрицю відстаней

	int** reachability_matrix = matrix_of_reachability(adjacency_matrix, n); //будуємо матрицю досяжностей

	menu(adjacency_matrix, distance_matrix, reachability_matrix, n);

	system("pause");
	return 0;
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

int** matrix_of_adj_with_null(int** arr_adj, const int n) {
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = arr_adj[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				matrix[i][j] = 0;
			}
		}
	}
	return matrix;
}

void degree(int** matrix, int** matrix_temp, int** arr_adj, const int n) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				matrix[i][j] += (matrix_temp[i][k]) * (arr_adj[k][j]);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix_temp[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}
}

int** matrix_of_distance(int** arr_adj, const int n) {

	int** matrix_in_degree = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix_in_degree[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix_in_degree[i][j] = arr_adj[i][j];
		}
	}

	int** matrix_of_zero = Fill_matrix_of_zero(n, n);

	int** distance_matrix = matrix_of_adj_with_null(arr_adj, n);

	int m = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && distance_matrix[i][j] == 0) {
				degree(matrix_of_zero, matrix_in_degree, arr_adj, n);
				m++;
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i != j) {
						if (distance_matrix[i][j] == 0 && matrix_in_degree[i][j] != 0) {
							distance_matrix[i][j] = m;
						}
					}
				}
			}
		}
	}
	clear_arr(matrix_in_degree, n);
	clear_arr(matrix_of_zero, n);
	return distance_matrix;
}

int** matrix_of_reachability(int** arr_adj, const int n) {
	int** arr_dist = matrix_of_distance(arr_adj, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((i == j) || arr_dist[i][j] != 0) {
				arr_dist[i][j] = 1;
			}
		}
	}
	return arr_dist;
}

int* list_of_eccentricity(int** arr_dist, const int n) {
	int* list_temp = new int[n];
	int* list = new int[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			list_temp[j] = arr_dist[i][j];
		}
		int max = 0;
		for (int k = 0; k < n; k++)
		{
			if (list_temp[k] > max)
			{
				max = list_temp[k];
			}
		}
		list[i] = max;
	}
	delete[]list_temp;
	return list;
}

void characteristics_of_graph(int** distance_matrix, const int n) {
	int* eccentricity_list = list_of_eccentricity(distance_matrix, n); //робимо список ексцентриситет вершин
	cout << "Для початку сформуємо список ексцентриситет:" << endl;
	for (int i = 0; i < n; i++) {
		cout << "e(v" << i + 1 << ") = " << eccentricity_list[i] << endl;
	}
	int diameter_of_graph, radius_of_graph;
	diameter_of_graph = radius_of_graph = eccentricity_list[0];
	for (int i = 0; i < n; i++) {
		if (eccentricity_list[i] > diameter_of_graph) {
			diameter_of_graph = eccentricity_list[i];
		}
		if (eccentricity_list[i] < radius_of_graph) {
			radius_of_graph = eccentricity_list[i];
		}
	}
	cout << "Діаметр графу: " << diameter_of_graph << endl;
	cout << "Радіус графу: " << radius_of_graph << endl;
	cout << "Центральні вершини графу: ";
	for (int i = 0; i < n; i++) {
		if (radius_of_graph == eccentricity_list[i]) {
			cout << "v" << i + 1 << "  ";
		}
	}
	cout << endl;
	cout << "Яруси графу: " << endl;
	int* arr_temp = new int[n];
	for (int i = 0; i < n; i++) {
		cout << "-------" << endl;
		cout << "Для v" << i + 1 << ":" << endl;
		cout << "-------" << endl;
		for (int j = 0; j < n; j++) {
			arr_temp[j] = distance_matrix[i][j];
		}

		for (int k = 1; k <= eccentricity_list[i]; k++) {
			cout << k << "-й ярус:  ";
			for (int m = 0; m < n; m++) {
				if (k == arr_temp[m]) {
					cout << "v" << m + 1 << "   ";
				}
			}
			cout << endl;
		}
	}
	delete[]eccentricity_list;
	delete[]arr_temp;
}

int menu(int** adjacency_matrix, int** distance_matrix, int** reachability_matrix, const int n) {
	cout << "Виберіть потрібний вам пункт меню." << endl;
	cout << "Меню:" << endl
		<< "0. Завершити виконання програми." << endl
		<< "1. Вивести матрицю суміжності." << endl
		<< "2. Вивести матрицю відстаней." << endl
		<< "3. Вивести матрицю досяжностей." << endl
		<< "4. Вивести метричні характеристики графу." << endl;
	while (true) {
		int temp_menu;
		cout << "Ваш вибір: ";
		temp_menu = (int)check_number();
		switch (temp_menu) {
		case 0: {
			clear_arr(adjacency_matrix, n);
			clear_arr(distance_matrix, n);
			clear_arr(reachability_matrix, n);
			cout << "Дякую за користування." << endl;
			return 0;
			break;
		}
		case 1: {
			cout << "Матриця суміжності:" << endl;
			Show_matrix(adjacency_matrix, n, n);
			break;
		}
		case 2: {
			cout << "Матриця відстаней:" << endl;
			Show_matrix(distance_matrix, n, n);
			break;
		}
		case 3: {
			cout << "Матриця досяжності:" << endl;
			Show_matrix(reachability_matrix, n, n);
			break;
		}
		case 4: {
			cout << "Метричні характеристики графу:" << endl;
			characteristics_of_graph(distance_matrix, n);
			break;
		}
		default: {
			cout << "Оберіть один із пунктів меню." << endl;
			break;
		}
		}
	}
}

void Show_matrix(int** arr, const int rows, const int cols) {
	cout << "    ";
	for (int p = 1; p <= cols; p++) {
		cout << "v" << p << " ";
	}
	cout << endl;
	for (int i = 0; i < rows; i++) {
		cout << "v" << i + 1 << "  ";
		for (int j = 0; j < cols; j++) {
			cout << arr[i][j] << "  ";
		}
		cout << endl;
	}
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

