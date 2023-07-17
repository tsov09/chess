#include <iostream>
using namespace std;

#include "table.h"
#include "figure.h"

bool Table::line_is_free(Moving_Type type, int row_current, int col_current, int row_aim, int col_aim) {
	if (m_matrix[row_current][col_current][2] == m_matrix[row_aim][col_aim][2]) {
		return false;
	}
	bool is_free = true;

	switch (type)
	{
	case left_row:
		for (int i = col_current - 1; i > col_aim; i--) {
			if (m_matrix[row_current][i] != "   " && m_matrix[row_current][i] != "###") {
				cout << "lr" << endl;
				is_free = false;
				break;
			}
		}
		break;
	case right_row:
		for (int i = col_current + 1; i < col_aim; i++) {
			if (m_matrix[row_current][i] != "   " && m_matrix[row_current][i] != "###") {
				is_free = false;
				break;
			}
		}
		break;
	case up_col:
		for (int i = row_current - 1; i > row_aim; i--) {
			if (m_matrix[i][col_current] != "   " && m_matrix[i][col_current] != "###") {
				is_free = false;
				break;
			}
		}
		break;
	case down_col:
		for (int i = row_current + 1; i < row_aim; i++) {
			if (m_matrix[i][col_current] != "   " && m_matrix[i][col_current] != "###") {
				is_free = false;
				break;
			}
		}
		break;
	case up_left:
		for (int i = 1; i > row_current - row_aim; i++) {
			if (m_matrix[row_current - i][col_current - i] != "   " && m_matrix[row_current - i][col_current - i] != "###") {
				is_free = false;
				break;
			}
		}
		break;
	case up_right:
		for (int i = 1; i < row_current - row_aim; i++) {
			if (m_matrix[row_current - i][col_current + i] != "   " && m_matrix[row_current - i][col_current + i] != "###") {
				is_free = false;
				break;
			}
		}
		break;
	case down_right:
		for (int i = 1; i < row_aim - row_current; i++) {
			if (m_matrix[row_current + i][col_current + i] != "   " && m_matrix[row_current + i][col_current + i] != "###") {
				is_free = false;
				break;
			}
		}
		break;
	case down_left:
		for (int i = 1; i < row_aim - row_current; i++) {
			if (m_matrix[row_current + i][col_current - i] != "   " && m_matrix[row_current + i][col_current - i] != "###") {
				is_free = false;
				break;
			}
		}
		break;
	case 8 ... 15:
		is_free = true;
		break;
	case no_way:
		is_free = false;
		break;
	default:
		break;
	}

	return is_free;

}

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

Table::Table() : Matrix(8, 8) {};

int Table::cln_vrt() {
	return 0;
}

void Table::fill() {
	for (int i = 0; i < m_row; i++) {
		for (int g = 0; g < m_column; g++) {
			if ((i + g) % 2 == 0) {
				m_matrix[i][g] = "###";
			}
			else {
				m_matrix[i][g] = "   ";
			}
		}
	}
}

void Table::draw() {
	cout << endl;
	cout << "     0   1   2   3   4   5   6   7    " << endl;
	for (int i = 0; i < m_row; i++) {
		cout << " " << i << "  ";
		for (int g = 0; g < m_column; g++) {
			cout << m_matrix[i][g] << " ";
		}
		cout << " " << i << " ";
		cout << endl;
	}
	cout << "     0   1   2   3   4   5   6   7    " << endl;
	cout << endl;
}

void Table::set_figure(Figure* figure, int row, int col) {
	m_matrix[row][col] = figure->get_name();
	figure->set_row(row);
	figure->set_col(col);
}