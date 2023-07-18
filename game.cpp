#include "game.h"

Game::~Game() {};

bool Chess::is_valid_ind(int x) {
	if (x >= 0 && x < 8) {
		return true;
	}
	else {
		return false;
	}
}

Chess::Chess() : m_figures_count(4) {
	int next = 0;
	m_figures = new Figure * [m_figures_count];
	m_chess_table = new Table();
	m_chess_table->fill();
	m_black_king = new King("black");
	//m_figures[next++] = m_black_king;
	m_white_king = new King("white");
	m_figures[next++] = m_white_king;
	m_white_queen = new Queen("white");
	m_figures[next++] = m_white_queen;
	m_white_bishop = new Bishop("white");
	m_figures[next++] = m_white_bishop;
	m_white_knight = new Knight("white");
	m_figures[next++] = m_white_knight;
}

Chess::~Chess() {
	for (int i = 0; i < m_figures_count; i++) {
		delete m_figures[i];
		m_figures[i] = nullptr;
	}
	delete[] m_figures;
	m_figures = nullptr;
	delete m_chess_table;
	m_chess_table = nullptr;
	delete m_black_king;
	m_black_king = nullptr;
	delete m_white_king; 
	m_white_king = nullptr;
	delete m_white_queen;
	m_white_queen = nullptr;
	delete m_white_bishop;
	m_white_bishop = nullptr;
	delete m_white_knight;
	m_white_knight = nullptr;
}

void Chess::start() {
	//set_random_pos();
	//set_figures();
	m_chess_table->draw();
	if (is_possible_game()) {
		if (is_check()) {
			if (is_mate()) {
				cout << "Checkmate" << endl;
			}
			else {
				cout << "Check" << endl;
			}
		}
		else {
			cout << "Not check" << endl;
		}
	}
	else {
		cout << "Impossible game." << endl;
	}
};
void Chess::stop() {
	cout << endl;
};
void Chess::print_figures() {
	for (int i = 0; i < m_figures_count; i++) {
		m_figures[i]->get_name();
	}
}
bool Chess::is_check() {
	int black_king_row = m_black_king->get_row();
	int black_king_col = m_black_king->get_col();
	Moving_Type move;
	bool is_check = false;
	for (int i = 0; i < m_figures_count; i++) {
		move = m_figures[i]->can_move(black_king_row, black_king_col);

		if (move != no_way) {
			//cout << "Move in check " << move << " " << m_figures[i]->get_name() << " " << black_king_row << ", " << black_king_col << endl;
			if (m_chess_table->line_is_free(move, m_figures[i]->get_row(), m_figures[i]->get_col(), black_king_row, black_king_col)) {
				is_check = true;
				break;
			}
		}
	}
	return is_check;

}

bool Chess::is_mate() {
	Moving_Type move;
	bool is_mate = true;
	int** black_king_moves = new int* [8];
	for (int i = 0; i < 8; i++) {
		black_king_moves[i] = new int[2];
	}
	int black_king_moves_size = 0;
	m_black_king->get_moves_list(black_king_moves, black_king_moves_size);
	for (int i = 0; i < black_king_moves_size; i++) {
		cout << black_king_moves[i][0] << " " << black_king_moves[i][1] << endl;
	}
	for (int g = 0; g < m_figures_count; g++) {
		bool is_check_this = false;
		bool matches = false;
		for (int i = 0; i < black_king_moves_size; i++) {
			if (m_figures[g]->get_row() == black_king_moves[i][0] && m_figures[g]->get_col() == black_king_moves[i][1]) {
				matches = true;
			}
			else {
				move = m_figures[g]->can_move(black_king_moves[i][0], black_king_moves[i][1]);
				if (move != no_way) {
					if (m_chess_table->line_is_free(move, m_figures[g]->get_row(), m_figures[g]->get_col(), black_king_moves[i][0], black_king_moves[i][1])) {
						is_check_this = true;
						break;
					}
				}

			}
		}
		if (!is_check_this && !matches) {
			cout << "Move in mate " << move << " " << m_figures[g]->get_row() << ", " << m_figures[g]->get_col() << endl;
			
			is_mate = false;
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		delete [] black_king_moves[i];
		black_king_moves[i] = nullptr;
	}
	delete[] black_king_moves;
	black_king_moves = nullptr;

	return is_mate;
}


void Chess::get_coordinates(string pos, int& row, int& col) {
	switch (pos[0])
	{
	case 'A': case 'a':
		col = 0;
		break;
	case 'B': case 'b':
		col = 1;
		break;
	case 'C': case 'c':
		col = 2;
		break;
	case 'D': case 'd':
		col = 3;
		break;
	case 'E': case 'e':
		col = 4;
		break;
	case 'F': case 'f':
		col = 5;
		break;
	case 'G': case 'g':
		col = 6;
		break;
	case 'H': case 'h':
		col = 7;
		break;
	default:
		break;
	}
	row = 8 - (pos[1] - '0');
}

bool Chess::is_possible_game() {
	int can_set = true;
	int diff_row = m_black_king->get_row() - m_white_king->get_row();
	int diff_col = m_black_king->get_col() - m_white_king->get_col();

	if (diff_row == 0 || diff_row == 1 || diff_row == -1) {
		if (diff_col == 0 || diff_col == 1 || diff_col == -1) {
			can_set = false;
		}
	}
	return can_set;
}

void Chess::set_figure(string figure_name, string position) {
	int row;
	int col;
	get_coordinates(position, row, col);
	if (Chess::is_valid_ind(row) && Chess::is_valid_ind(col)) {
		if (figure_name == "Black King") {
			m_chess_table->set_figure(m_black_king, row, col);
		}
		else if (figure_name == "White King") {
			m_chess_table->set_figure(m_white_king, row, col);
		}
		else if (figure_name == "White Queen") {
			m_chess_table->set_figure(m_white_queen, row, col);
		}
		else if (figure_name == "White Bishop") {
			m_chess_table->set_figure(m_white_bishop, row, col);
		}
		else if (figure_name == "White Knight") {
			m_chess_table->set_figure(m_white_knight, row, col);
		}
		else {
			cout << "Figure not found" << endl;
		}
	}
}

//void Chess::set_figures() {
//	set_figure("Black King", "H8");
//	set_figure("White King", "E5");
//	set_figure("White Queen", "H3");
//	set_figure("White Bishop", "E6");
//	set_figure("White Knight", "D6");
//}



//int Chess::gen_rand(int start, int end) {
//	int n = rand() % (end - start) + start;
//	if (n % 10 == 0 || n % 10 == 9) {
//		return gen_rand(start, end);
//	}
//	return n;
//};
//void Chess::gen_random_array(int size) {
//	m_rand_pos = new int[size];
//	int next = 0;
//	int n;
//	while (next < size) {
//		n = gen_rand(11, 88);
//		bool exists = false;
//		for (int i = 0; i < next; i++) {
//			if (m_rand_pos[i] == n) {
//				exists = true;
//				break;
//			}
//		}
//		if (!exists) {
//			m_rand_pos[next] = n;
//			next++;
//		}
//	}
//};

//void Chess::set_random_pos() {
//	gen_random_array(m_figures_count + 1);
//	int row;
//	int col;
//
//	row = m_rand_pos[0] / 10 - 1;
//	col = m_rand_pos[0] % 10 - 1;
//	m_chess_table->set_figure(m_black_king, row, col);
//	m_black_king->set_row(row);
//	m_black_king->set_col(col);
//
//	for (int i = 1; i < m_figures_count; i++) {
//		row = m_rand_pos[i] / 10 - 1;
//		col = m_rand_pos[i] % 10 - 1;
//		m_chess_table->set_figure(m_figures[i], row, col);
//		m_figures[i]->set_row(row);
//		m_figures[i]->set_col(col);
//	}
//}