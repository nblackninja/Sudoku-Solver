// Sudoku-Solver.cpp: ���������� ����� ����� ��� ����������� ����������.
//

/*
*	����: Sudoku-Solver.exe
*
*		������: 05, ������� 2018
*		�����: ���� ������
*
*	��������:	��� ������� ������ ������ (��������: 9*9)
*				�������� ������������ � ��������� �������
*				� ���� ������ ���������� �������
*				������� ������������ ��������.
*/

//========= ���������� =========//
#include "stdafx.h"
#include <iostream>
#include <time.h>

//========= ������������ ���� ==========//
using namespace std;

//========= ��������� =========//
const size_t	N = 3;		// ������ ������ �������� 3 �� 3.
const size_t	EMPTY = 0;	// ���������� ������ ������.

							//====== ���������� ������� ======//
bool fill_sud(size_t sud[][N*N], size_t row, size_t col);
void print_sud(const size_t sud[][N*N]);
bool is_legal(const size_t sud[][N*N], size_t row, size_t col, size_t val);
bool is_row_ok(const size_t row[], size_t col, size_t val);
bool is_col_ok(const size_t sud[][N*N], size_t row, size_t col, size_t val);
bool is_sqr_ok(const size_t sud[][N*N], size_t row, size_t col, size_t val);

//========== Main ===========//
int main()
{
	setlocale(LC_ALL, "Russian");
	clock_t start = clock();

	size_t sud[N*N][N*N] = {
		0,0,5   ,3,0,0    ,0,0,0,
		8,0,0   ,0,0,0    ,0,2,0,
		0,7,0   ,0,1,0    ,5,0,0,

		4,0,0   ,0,0,5    ,3,0,0,
		0,1,0   ,0,7,0    ,0,0,6,
		0,0,3   ,2,0,0    ,0,8,0,

		0,6,0   ,5,0,0    ,0,0,9,
		0,0,4   ,0,0,0    ,0,3,0,
		0,0,0   ,0,0,9    ,7,0,0
	};  // ����� ������.

	fill_sud(sud, 0, 0);
	print_sud(sud);

	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "�����: " << seconds << " ���" << endl;

	cout << endl;
	return 0;
}

//======== ���������� ������ =========//
// ��������:	�������� �������� ��������� ������ � ������������ � ���������.
// ���������:	������, ������ ������� �� ������, ������ ������� �� ��������
// ����������:	������� �� ��������� ������ (true - �������, false - ���)
bool fill_sud(size_t sud[][N*N], size_t row, size_t col)
{
	// ��������� �� ����� ������ ��������� ������.
	size_t next_row = row;
	if (col == N*N - 1)
		++next_row;

	// ��������� �� ����� ������� ��������� ������.
	size_t next_col = (col + 1) % (N*N);

	// ���� ��� ������� �����, �� �� ������ ������.
	if (row == N*N)
		return true;

	// ���������, ��������� �� ������
	// ���� ���������, �� ����������
	// ���� �� ���������, �� ����� �������� ��� ������� ����������
	if (sud[row][col] != EMPTY)
		return fill_sud(sud, next_row, next_col);

	// �������� ����� ���������� � �������������� ��������
	// � ��������� � ������� ������.
	for (size_t value = 1; value <= N*N; ++value)
	{
		sud[row][col] = value;

		// ��������� ����� �� ��������(value) ���� � ������,
		// � ���������� true, ���� �����.
		if (is_legal(sud, row, col, value) && fill_sud(sud, next_row, next_col))
			return true;

		// �� ������� ��������� ������!
		sud[row][col] = EMPTY;
	}

	// ������ ������ �� ����������.
	return false;
}

//======== ����� ������ ========//
// ����� ������ � ���� �������� �������.
void print_sud(const size_t sud[][N*N])
{
	for (size_t i = 0; i < N*N; ++i)
	{
		for (size_t j = 0; j < N*N; ++j)
		{
			cout << sud[i][j] << ' ';
			if (j == 2 || j == 5)
				cout << "| ";
		}
		cout << endl;
		if (i == 2 || i == 5)
			cout << "------+-------+------" << endl;
	}
}

//========== ��������� �������� ==========//
// ��������� � ����������, ���� �������� value �������� � ���� ������
bool is_legal(const size_t sud[][N*N], size_t row, size_t col, size_t value)
{
	return (is_row_ok(sud[row], col, value) &&
		is_col_ok(sud, row, col, value) &&
		is_sqr_ok(sud, row, col, value));
}

//========= �������� ���� =========//
// ��������� � ���������� true, ���� �������� value �������� � ����
bool is_row_ok(const size_t row[], size_t col, size_t val)
{
	for (size_t i = 0; i < N*N; ++i)
		if (i != col && row[i] == val)
			return false;       // Found the same value again!

	return true;
}

//========= �������� ������� =========//
// ��������� � ���������� true, ���� �������� value �������� � ������
bool is_col_ok(const size_t sud[][N*N], size_t row, size_t col, size_t val)
{
	for (size_t i = 0; i < N*N; ++i)
		if (i != row && sud[i][col] == val)
			return false;       // Found the same value again!

	return true;
}

//========= �������� �������� =========//
// ��������� � ���������� true, ���� �������� value �������� � ��������
bool is_sqr_ok(const size_t sud[][N*N], size_t row, size_t col, size_t val)
{
	size_t row_corner = (row / N) * N;
	// ���������� ����� ������ ������� ���������� ������� ������.

	size_t col_corner = (col / N) * N;
	// ���������� ����� ������� ������� ���������� ������� ������.

	for (size_t i = row_corner; i < (row_corner + N); ++i)
		for (size_t j = col_corner; j < (col_corner + N); ++j)
			if ((i != row || j != col) && sud[i][j] == val)
				return false;       // ����� ���� �������� �����!

	return true;
}
