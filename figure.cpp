#include "figure.h"

#include <iostream>
#include <string>
using namespace std;

string Figure::generate_name(string type, string index, string color) {
	return type + index + color;
}

string Figure::get_name() {
	return m_name;
}

bool Figure::is_valid_index(int x) {
	if (x >= 0 && x < 8) {
		return true;
	}
	else {
		return false;
	}
}

Moving_Type Figure::can_move(int row, int col) {
	Moving_Type type;
	return type;
}

void Figure::moves_list(int** list, int&) {
	cout << endl;
}

void Figure::set_row(int row) {
	if (is_valid_index(row)) {
		m_row = row;
	}
}
void Figure::set_col(int col) {
	if (is_valid_index(col)) {
		m_col = col;
	}
}

int Figure::get_row() {
	return m_row;
}

int Figure::get_col() {
	return m_col;
}

King::King(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("K", "_", "W");
	}
	else if (color == "black") {
		m_name = Figure::generate_name("K", "_", "B");
	}
	else {
		cout << "Enter white or black." << endl;
	}
}
Moving_Type King::can_move(int row, int col) {
	Moving_Type type;
	int row_diff = m_row - row;
	int col_diff = m_col - col;
	if (Figure::is_valid_index(row) && Figure::is_valid_index(col)) {
		if (row_diff == 0 && col_diff == 1) {
			type = left_row;
		}
		else if (row_diff == 1 && col_diff == 1) {
			type = up_left;
		}
		else if (row_diff == 1 && col_diff == 0) {
			type = up_col;
		}
		else if (row_diff == 1 && col_diff == -1) {
			type = up_right;
		}
		else if (row_diff == 0 && col_diff == -1) {
			type = right_row;
		}
		else if (row_diff == -1 && col_diff == -1) {
			type = down_right;
		}
		else if (row_diff == -1 && col_diff == 0) {
			type = down_col;
		}
		else if (row_diff == -1 && col_diff == 1) {
			type = down_left;
		}
		else {
			type = no_way;
		}
	}
	else {
		type = no_way;
	}
	return type;
}

void King::moves_list(int** list, int& size) {

	if (Figure::is_valid_index(m_col - 1)) {
		list[size][0] = m_row;
		list[size][1] = m_col-1;
		size++;
	}
	if (Figure::is_valid_index(m_col + 1)) {
		list[size][0] = m_row;
		list[size][1] = m_col + 1;
		size++;
	}
	if (Figure::is_valid_index(m_row - 1)) {
		list[size][0] = m_row - 1;
		list[size][1] = m_col;
		size++;
	}
	if (Figure::is_valid_index(m_row + 1)) {
		list[size][0] = m_row + 1;
		list[size][1] = m_col;
		size++;
	}
	if (Figure::is_valid_index(m_row - 1) && Figure::is_valid_index(m_col - 1)) {
		list[size][0] = m_row - 1;
		list[size][1] = m_col - 1;
		size++;
	}
	if (Figure::is_valid_index(m_row - 1) && Figure::is_valid_index(m_col + 1)) {
		list[size][0] = m_row - 1;
		list[size][1] = m_col + 1;
		size++;
	}
	if (Figure::is_valid_index(m_row + 1) && Figure::is_valid_index(m_col + 1)) {
		list[size][0] = m_row + 1;
		list[size][1] = m_col + 1;
		size++;
	}
	if (Figure::is_valid_index(m_row + 1) && Figure::is_valid_index(m_col - 1)) {
		list[size][0] = m_row + 1;
		list[size][1] = m_col - 1;
		size++;
	}
}


Queen::Queen(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("Q", "_", "W");
	}
	else if (color == "black") {
		m_name = Figure::generate_name("Q", "_", "B");
	}
	else {
		cout << "Enter white or black." << endl;
	}
}

Moving_Type Queen::can_move(int row, int col) {
	Moving_Type type;
	int row_diff = m_row - row;
	int col_diff = m_col - col;
	cout << row_diff << "  " << col_diff << " diff" << m_row << " " << m_col << endl;
	if (Figure::is_valid_index(row) && Figure::is_valid_index(col)) {
		if (row_diff == 0 && col_diff > 0) {
			type = left_row;
		}
		else if (row_diff == col_diff && row_diff > 0) {
			type = up_left;
		}
		else if (row_diff > 0 && col_diff == 0) {
			type = up_col;
		}
		else if (row_diff == col_diff * (-1) && row_diff > 0) {
			type = up_right;
		}
		else if (row_diff == 0 && col_diff < 0) {
			type = right_row;
		}
		else if (row_diff == col_diff && row_diff < 0) {
			type = down_right;
		}
		else if (row_diff < 0 && col_diff == 0) {
			type = down_col;
		}
		else if (row_diff == col_diff * (-1) && row_diff < 0) {
			type = down_left;
		}
		else {
			type = no_way;
		}
	}
	else {
		type = no_way;
	}
	return type;
}

Bishop::Bishop(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("B", "_", "W");
	}
	else if (color == "black") {
		m_name = Figure::generate_name("B", "_", "B");
	}
	else {
		cout << "Enter white or black." << endl;
	}
}

Moving_Type Bishop::can_move(int row, int col) {
	Moving_Type type;
	int row_diff = m_row - row;
	int col_diff = m_col - col;
	if (Figure::is_valid_index(row) && Figure::is_valid_index(col)) {
		if (row_diff == col_diff && row_diff > 0) {
			type = up_left;
		}
		else if (row_diff == col_diff * (-1) && row_diff > 0) {
			type = up_right;
		}
		else if (row_diff == col_diff && row_diff < 0) {
			type = down_right;
		}
		else if (row_diff == col_diff * (-1) && row_diff < 0) {
			type = down_left;
		}
		else {
			type = no_way;
		}
	}
	else {
		type = no_way;
	}
	return type;
}

Knight::Knight(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("N", "_", "W");
	}
	else if (color == "black") {
		m_name = Figure::generate_name("N", "_", "B");
	}
	else {
		cout << "Enter white or black." << endl;
	}
}

Moving_Type Knight::can_move(int row, int col) {
	Moving_Type type;
	int row_diff = m_row - row;
	int col_diff = m_col - col;
	if (Figure::is_valid_index(row) && Figure::is_valid_index(col)) {
		if (row_diff == 1 && col_diff == 2) {
			type = up_left_N;
		}
		else if (row_diff == 1 && col_diff == -2) {
			type = up_right_N;
		}
		else if (row_diff == -1 && col_diff == -2) {
			type = down_right_N;
		}
		else if (row_diff == -1 && col_diff == 2) {
			type = down_left_N;
		}
		else if (row_diff == 2 && col_diff == 1) {
			type = left_up_N;
		}
		else if (row_diff == 2 && col_diff == -1) {
			type = right_up_N;
		}
		else if (row_diff == -2 && col_diff == -1) {
			type = right_down_N;
		}
		else if (row_diff == -2 && col_diff == 1) {
			type = left_down_N;
		}
		else {
			type = no_way;
		}
	}
	else {
		type = no_way;
	}
	return type;
}