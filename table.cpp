#include <iostream>
using namespace std;

#include "table.h"

Matrix::Matrix(int row, int column) : m_row(row), m_column(column) {
	m_matrix = new string * [m_row];
	for (int i = 0; i < m_row; i++) {
		m_matrix[i] = new string[m_column];
	}
}
void Matrix::set_row(int row) {
	if (row > 1) {
		m_row = row;
	}
}
void Matrix::set_column(int column) {
	if (column > 1) {
		m_column = column;
	}
}

Table::Table() : Matrix(10, 10) {};

int Table::cln_vrt() {
	return 0;
}

void Table::fill() {
	for (int i = 1; i < m_row - 1; i++) {
		for (int g = 1; g < m_column - 1; g++) {
			if ((i + g) % 2 == 0) {
				m_matrix[i][g] = "###";
			}
			else {
				m_matrix[i][g] = "   ";
			}
		}
	}
	m_matrix[0][0] = m_matrix[9][0] = "   ";
	string next;

	char ch = 'A';
	for (int i = 1; i < m_row - 1; i++) {
		next = "  ";
		next.insert(1, 1, ch);
		m_matrix[0][i] = next;
		m_matrix[i][0] = " " + to_string(9 - i) + " ";
		m_matrix[i][9] = " " + to_string(9 - i) + " ";
		m_matrix[9][i] = next;
		ch++;
	}
}

void Table::draw() {
	cout << endl;
	for (int i = 0; i < m_row; i++) {
		for (int g = 0; g < m_column; g++) {
			cout << m_matrix[i][g] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Table::set_figure(Figure* figure, int position) {
	m_matrix[position / 10][position % 10] = figure->get_name();
}