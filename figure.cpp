#include "figure.h"

#include <iostream>
#include <string>
using namespace std;

Figure::~Figure() {};
Figure::Figure() : m_row(-1), m_col(-1) {};
string Figure::generate_name(string type, string index, string color) {
	return type + index + color;
}

string Figure::get_name() {
	return m_name;
}

string Figure::get_full_name() {
	return m_full_name;
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

void Figure::fill_moves_list() {
	cout << endl;
}

vector<Position> Figure::get_moves_list() {
	return m_moves_list;
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
		m_full_name = "White King";
	}
	else if (color == "black") {
		m_name = Figure::generate_name("K", "_", "B");
		m_full_name = "Black King";
	}
	else {
		cout << "Enter white or black." << endl;
	}
}
King::~King() {};

Moving_Type King::can_move(int row, int col) {
	Moving_Type type;
	int row_diff = m_row - row;
	int col_diff = m_col - col;

	if (row_diff == 0 && col_diff == 0) {
		return no_way;
	}
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

void King::fill_moves_list() {
	m_moves_list.clear();
	Position pos;
	if (Figure::is_valid_index(m_col - 1)) {
		pos.row = m_row;
		pos.col = m_col - 1;
		m_moves_list.push_back(pos);
		if (Figure::is_valid_index(m_row + 1)) {
			pos.row = m_row + 1;
			pos.col = m_col - 1;
			m_moves_list.push_back(pos);
		}
		if (Figure::is_valid_index(m_row - 1)) {
			pos.row = m_row - 1;
			pos.col = m_col - 1;
			m_moves_list.push_back(pos);
		}
	}
	if (Figure::is_valid_index(m_col + 1)) {
		pos.row = m_row;
		pos.col = m_col + 1;
		m_moves_list.push_back(pos);

		if (Figure::is_valid_index(m_row - 1)) {
			pos.row = m_row - 1;
			pos.col = m_col + 1;
			m_moves_list.push_back(pos);
		}
		if (Figure::is_valid_index(m_row + 1)) {
			pos.row = m_row + 1;
			pos.col = m_col + 1;
			m_moves_list.push_back(pos);
		}
	}
	if (Figure::is_valid_index(m_row - 1)) {
		pos.row = m_row - 1;
		pos.col = m_col;
		m_moves_list.push_back(pos);
	}
	if (Figure::is_valid_index(m_row + 1)) {
		pos.row = m_row + 1;
		pos.col = m_col;
		m_moves_list.push_back(pos);

	}
}

Queen::~Queen() {};
Queen::Queen(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("Q", "_", "W");
		m_full_name = "White Queen";
	}
	else if (color == "black") {
		m_name = Figure::generate_name("Q", "_", "B");
		m_full_name = "Black Queen";
	}
	else {
		cout << "Enter white or black." << endl;
	}
}

Moving_Type Queen::can_move(int row, int col) {
	Moving_Type type;
	int row_diff = m_row - row;
	int col_diff = m_col - col;
	if (row_diff == 0 && col_diff == 0) {
		return no_way;
	}
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

void Queen::fill_moves_list() {
	m_moves_list.clear();
	Position pos;
	int row = m_row - 1;
	int col = m_col - 1;
	while (col >= 0 && row >= 0) {
		pos.row = row;
		pos.col = col;
		m_moves_list.push_back(pos);
		row--;
		col--;
	}
	row = m_row + 1;
	col = m_col + 1;
	while (col < 8 && row < 8) {
		pos.row = row;
		pos.col = col;
		m_moves_list.push_back(pos);
		row++;
		col++;
	}
	row = m_row + 1;
	col = m_col - 1;
	while (col >= 0 && row < 8) {
		pos.row = row;
		pos.col = col;
		m_moves_list.push_back(pos);
		row++;
		col--;
	}
	row = m_row - 1;
	col = m_col + 1;
	while (col < 8 && row >= 0) {
		pos.row = row;
		pos.col = col;
		m_moves_list.push_back(pos);
		row--;
		col++;
	}
	col = m_col - 1;
	while (col >= 0) {
		pos.row = m_row;
		pos.col = col;
		m_moves_list.push_back(pos);
		col--;
	}
	row = m_row - 1;
	while (row >= 0) {
		pos.row = row;
		pos.col = m_col;
		m_moves_list.push_back(pos);
		row--;
	}
	col = m_col + 1;
	while (col < 8) {
		pos.row = m_row;
		pos.col = col;
		m_moves_list.push_back(pos);
		col++;
	}
	row = m_row + 1;
	while (row < 8) {
		pos.row = row;
		pos.col = m_col;
		m_moves_list.push_back(pos);
		row++;
	}
}

Bishop::~Bishop() {};
Bishop::Bishop(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("B", "_", "W");
		m_full_name = "White Bishop";
	}
	else if (color == "black") {
		m_name = Figure::generate_name("B", "_", "B");
		m_full_name = "Black Bishop";
	}
	else {
		cout << "Enter white or black." << endl;
	}
}

Moving_Type Bishop::can_move(int row, int col) {
	Moving_Type type;
	int row_diff = m_row - row;
	int col_diff = m_col - col;
	if (row_diff == 0 && col_diff == 0) {
		return no_way;
	}
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

void Bishop::fill_moves_list() {
	m_moves_list.clear();
	int col = m_col - 1;
	int row = m_row - 1;
	Position pos;

	while (col >= 0 && row >= 0) {
		pos.row = row;
		pos.col = col;
		m_moves_list.push_back(pos);
		row--;
		col--;
	}
	col = m_col + 1;
	row = m_row + 1;
	while (col < 8 && row < 8) {
		pos.row = row;
		pos.col = col;
		m_moves_list.push_back(pos);
		row++;
		col++;
	}
	col = m_col - 1;
	row = m_row + 1;
	while (col >= 0 && row < 8) {
		pos.row = row;
		pos.col = col;
		m_moves_list.push_back(pos);
		row++;
		col--;
	}
	col = m_col + 1;
	row = m_row - 1;
	while (col < 8 && row >= 0) {
		pos.row = row;
		pos.col = col;
		m_moves_list.push_back(pos);
		row--;
		col++;
	}
}

Knight::~Knight() {};
Knight::Knight(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("N", "_", "W");
		m_full_name = "White Knight";
	}
	else if (color == "black") {
		m_name = Figure::generate_name("N", "_", "B");
		m_full_name = "Black Knight";
	}
	else {
		cout << "Enter white or black." << endl;
	}
}

Moving_Type Knight::can_move(int row, int col) {
	Moving_Type type;
	int row_diff = m_row - row;
	int col_diff = m_col - col;
	if (row_diff == 0 && col_diff == 0) {
		return no_way;
	}
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

void Knight::fill_moves_list() {
	m_moves_list.clear();
	Position pos;

	if (Figure::is_valid_index(m_row - 1) && Figure::is_valid_index(m_col - 2)) {
		pos.row = m_row - 1;
		pos.col = m_col - 2;
		m_moves_list.push_back(pos);
	}
	if (Figure::is_valid_index(m_row - 2) && Figure::is_valid_index(m_col - 1)) {
		pos.row = m_row - 2;
		pos.col = m_col - 1;
		m_moves_list.push_back(pos);

	}
	if (Figure::is_valid_index(m_row - 1) && Figure::is_valid_index(m_col + 2)) {
		pos.row = m_row - 1;
		pos.col = m_col + 2;
		m_moves_list.push_back(pos);

	}
	if (Figure::is_valid_index(m_row - 2) && Figure::is_valid_index(m_col + 1)) {
		pos.row = m_row - 2;
		pos.col = m_col + 1;
		m_moves_list.push_back(pos);

	}
	if (Figure::is_valid_index(m_row + 1) && Figure::is_valid_index(m_col + 2)) {
		pos.row = m_row + 1;
		pos.col = m_col + 2;
		m_moves_list.push_back(pos);

	}
	if (Figure::is_valid_index(m_row + 2) && Figure::is_valid_index(m_col + 1)) {
		pos.row = m_row + 2;
		pos.col = m_col + 1;
		m_moves_list.push_back(pos);
	}
	if (Figure::is_valid_index(m_row + 1) && Figure::is_valid_index(m_col - 2)) {
		pos.row = m_row + 1;
		pos.col = m_col - 2;
		m_moves_list.push_back(pos);

	}
	if (Figure::is_valid_index(m_row + 2) && Figure::is_valid_index(m_col - 1)) {
		pos.row = m_row + 2;
		pos.col = m_col - 1;
		m_moves_list.push_back(pos);
	}
}