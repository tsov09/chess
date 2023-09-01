#include <iostream>
using namespace std;

#include "table.h"
#include "figure.h"


Matrix::Matrix(int row, int column) : m_row(row), m_column(column) {
	m_matrix = new string * [m_row];
	for (int i = 0; i < m_row; i++) {
		m_matrix[i] = new string[m_column];
	}
}
Matrix::~Matrix() {
	for (int i = 0; i < m_row; i++) {
		delete [] m_matrix[i];
		m_matrix[i] = nullptr;
	}
	delete[] m_matrix;
	m_matrix = nullptr;
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
Table::~Table() {};

bool Table::cell_is_available(int row_current, int col_current, int row_aim, int col_aim) {
	if (m_matrix[row_current][col_current][2] == m_matrix[row_aim][col_aim][2]) {
		return false;
	}
	else {
		return true;
	}
};
bool Table::line_is_free(Moving_Type type, int row_current, int col_current, int row_aim, int col_aim) {
	bool is_free = true;

	switch (type)
	{
	case left_row:
		for (int i = col_current - 1; i > col_aim; i--) {
			if (m_matrix[row_current][i] != "   " && m_matrix[row_current][i] != "###") {
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
		for (int i = 1; i < row_current - row_aim; i++) {
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
	cout << "     A   B   C   D   E   F   G   H    " << endl;
	for (int i = 0; i < m_row; i++) {
		cout << " " << 8 - i << "  ";
		for (int g = 0; g < m_column; g++) {
			cout << m_matrix[i][g] << " ";
		}
		cout << " " << 8 - i << " ";
		cout << endl;
	}
	cout << "     A   B   C   D   E   F   G   H    " << endl;
	cout << endl;
}

//bool isn't correct
bool Table::set_figure(Figure* figure, int row, int col) {
	m_matrix[row][col] = figure->get_name();
	figure->set_row(row);
	figure->set_col(col);
	figure->fill_moves_list();
	return true;
	
	//if (m_matrix[row][col] == "   " || m_matrix[row][col] == "###") {
	//}
	//else {
	//	//cout << "Position for " << figure->get_name() << " and " << m_matrix[row][col] << " are similar." << endl;
	//	return false;
	//}
}

void Table::empty_cell(int row, int col) {
	if ((row + col) % 2 == 0) {
		m_matrix[row][col] = "###";
	}
	else {
		m_matrix[row][col] = "   ";
	}
}

string Table::get_cell(int row, int col) {
	//check if indexes are correct
	return m_matrix[row][col];
}