#include <iostream>
#include <Windows.h>
#include <regex>
#include <limits>

using namespace std;

int input_vertex(const int);

int** Fill_matrix_of_vertex(const int, const int);

int** Fill_matrix_of_zero(const int, const int);

int** matrix_of_adjacency(int**, const int, const int, const bool);

int** matrix_of_adj_with_null(int**, const int);

void degree(int**, int**, const int n);

int** matrix_of_distance(int**, const int);

int** matrix_of_reachability(int**, const int);

int** the_reach_matrix_of_undirected_graph(int**, const int, const int);

bool unilaterally_bound(int**, const int);

int** create_copy_matrix(int**, const int, const int);

int menu(int**, int**, int**, int**, const int);

bool check_matrix(int**, const int, const int); //повертає true, якщо вся матриця заповнена одним числом

void Show_matrix(int**, const int, const int);

void clear_arr(int**, const int);

double  check_number();

int get_natural_int(const double number);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введіть кількість вершин та ребер графу орієнтованого графу:" << endl;

	int n = get_natural_int(check_number()); //кількість вершин
	int m = get_natural_int(check_number()); //кількість ребр

	cout << "Введіть вершини ребер графу:" << endl;
	int** vertex = Fill_matrix_of_vertex(m, n); //заповнюємо матрицю розміру mx2 вершинами

	int** adjacency_matrix = matrix_of_adjacency(vertex, n, m, 1); //будуємо матрицю суміжності

	int** distance_matrix = matrix_of_distance(adjacency_matrix, n); //будуємо матрицю відстаней

	int** reachability_matrix = matrix_of_reachability(distance_matrix, n); //будуємо матрицю досяжностей орієнтованого графу

	int** reach_undirected_graph_matrix = the_reach_matrix_of_undirected_graph(vertex, m, n);//будуємо матрицю досяжностей неорієнтованого графу

	menu(adjacency_matrix, distance_matrix, reachability_matrix, reach_undirected_graph_matrix, n);

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

int** matrix_of_adjacency(int** vertex, const int n, const int m, const bool choice) {
	int** matrix_of_adjacency = Fill_matrix_of_zero(n, n); //створюємо та заповнюємо матрицю розміру nxn нулями
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 0; k < m; k++) {
				if (choice == 0) {
					if ((vertex[k][0] == j && vertex[k][1] == i) || (vertex[k][0] == i && vertex[k][1] == j)) {
						matrix_of_adjacency[j - 1][i - 1] = 1;
						break;
					}
				}
				else {
					if ((vertex[k][0] == j && vertex[k][1] == i)) {
						matrix_of_adjacency[j - 1][i - 1] = 1;
						break;
					}
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

void degree(int** matrix_temp, int** arr_adj, const int n) {
	int** matrix = Fill_matrix_of_zero(n, n);
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
	clear_arr(matrix, n);
}

int** matrix_of_distance(int** arr_adj, const int n) {

	int** matrix_in_degree = create_copy_matrix(arr_adj, n, n);
	int** distance_matrix = matrix_of_adj_with_null(arr_adj, n);
	int m = 1;

	for (int i = 0; i < n; i++) {
		if (check_matrix(matrix_in_degree, n, 0) == 0) {
			for (int j = 0; j < n; j++) {
				if (i != j && distance_matrix[i][j] == 0) {
					degree(matrix_in_degree, arr_adj, n);
					m++;
					for (int k = 0; k < n; k++) {
						for (int l = 0; l < n; l++) {
							if (k != l && distance_matrix[k][l] == 0 && matrix_in_degree[k][l] != 0) {
								distance_matrix[k][l] = m;
							}
						}
					}
				}
				else continue;
			}
		}
		else break;
	}

	clear_arr(matrix_in_degree, n);
	return distance_matrix;
}

int** matrix_of_reachability(int** arr_dist, const int n) {
	int** arr_reach = create_copy_matrix(arr_dist, n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((i == j) || arr_reach[i][j] != 0) {
				arr_reach[i][j] = 1;
			}
		}
	}
	return arr_reach;
}

int menu(int** adjacency_matrix, int** distance_matrix, int** reachability_matrix, int** reach_undirected_graph_matrix, const int n) {
	cout << "Виберіть потрібний вам пункт меню." << endl;
	cout << "Меню:" << endl
		<< "0. Завершити виконання програми." << endl
		<< "1. Вивести матрицю відстаней." << endl
		<< "2. Вивести матрицю досяжностей." << endl
		<< "3. Вивести тип зв'язності." << endl;
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
			cout << "Матриця відстаней:" << endl;
			Show_matrix(distance_matrix, n, n);
			break;
		}
		case 2: {
			cout << "Матриця досяжності:" << endl;
			Show_matrix(reachability_matrix, n, n);
			break;
		}
		case 3: {
			cout << "Тип зв'язності графу:" << endl;
			if (check_matrix(reachability_matrix, n, 1)) {
				cout << "Граф сильнозв'язаний." << endl;
			}
			else if (unilaterally_bound(reachability_matrix, n)) {
				cout << "Граф однобічно-зв'язаний." << endl;
			}

			else if (check_matrix(reach_undirected_graph_matrix, n, 1)) {
				cout << "Граф слабкозв'язаний." << endl;
			}
			else {
				cout << "Граф не є зв'язним." << endl;
			}
			break;
		}
		default: {
			cout << "Оберіть один із пунктів меню." << endl;
			break;
		}
		}
	}
}

int** the_reach_matrix_of_undirected_graph(int** vertex, const int m, const int n) {
	int** adj_matrix = matrix_of_adjacency(vertex, n, m, 0); //будуємо матрицю суміжності
	clear_arr(vertex, m);
	int** dist_matrix = matrix_of_distance(adj_matrix, n); //будуємо матрицю відстаней
	int** reach_matrix = matrix_of_reachability(dist_matrix, n); //будуємо матрицю досяжностей
	return reach_matrix;
}

int** create_copy_matrix(int** matrix, const int rows, const int cols) {
	int** new_matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		new_matrix[i] = new int[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			new_matrix[i][j] = matrix[i][j];
		}
	}
	return new_matrix;
}

bool unilaterally_bound(int** matrix, const int n) {
	int count = 0;
	int rezult = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (matrix[i][j] == 1 || matrix[j][i] == 1)
				count += 1;
		}
	}
	for (int i = n - 1; i > 0; i--)
	{
		rezult += i;
	}
	if (count == rezult)
		return true;
	return false;
}

bool check_matrix(int** matrix, const int n, const int number) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] != number) {
				return 0;
			}
		}
	}
	return 1;
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

