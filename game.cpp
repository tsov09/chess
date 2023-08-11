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
	else {
		cout << endl << "Invalid position for " << figure_name << "!" << endl;
	}
}

void Chess::start() {
	//set_random_pos();
	//set_figures();
	//is_check_and_mate();
	if (is_possible_game()) {
		m_chess_table->draw();
		if (!is_check()) {
			is_check_and_mate_after_whites_move();
		}
		else {
			cout << "Whites already won." << endl;
		}
	}
	else {
		cout << "Impossible game." << endl;
	}
}
void Chess::stop() {
	cout << endl;
}
void Chess::print_figures() {
	for (int i = 0; i < m_figures_count; i++) {
		m_figures[i]->get_name();
	}
}

bool Chess::is_check_and_mate() {
	bool check_and_mate = false;
	if (is_possible_game()) {
		if (is_check()) {
			if (is_mate()) {
				//cout << "Check and mate" << endl;
				check_and_mate = true;
			}
			/*else {
				cout << "Check" << endl;
			}*/
		}
		/*else {
			cout << "Not check" << endl;
		}*/
	}
	/*else {
		cout << "Impossible game." << endl;
	}*/
	return check_and_mate;
}
void Chess::is_check_and_mate_after_whites_move() {
	m_white_king->fill_moves_list();
	m_white_queen->fill_moves_list();
	m_white_bishop->fill_moves_list();
	m_white_knight->fill_moves_list();
	vector<Position> white_king_moves = m_white_king->get_moves_list();
	vector<Position> white_queen_moves = m_white_queen->get_moves_list();
	vector<Position> white_bishop_moves = m_white_bishop->get_moves_list();
	vector<Position> white_knight_moves = m_white_knight->get_moves_list();

	cout << "Whites can win in case of moving: ";

	
	bool exists = false;
	Moving_Type move;

	int saved_row = m_white_king->get_row();
	int saved_col = m_white_king->get_col();

	for (int i = 0; i < white_king_moves.size(); i++) {
		move = m_white_king->can_move(white_king_moves[i].row, white_king_moves[i].col);
		if (move != no_way) {
			if (m_chess_table->line_is_free(move, saved_row, saved_col, white_king_moves[i].row, white_king_moves[i].col)
				&& m_chess_table->cell_is_available(saved_row, saved_col, white_king_moves[i].row, white_king_moves[i].col)) {
				if (m_chess_table->set_figure(m_white_king, white_king_moves[i].row, white_king_moves[i].col)) {
					m_chess_table->empty_cell(saved_row, saved_col);
						if (is_check_and_mate()) {
						exists = true;
						cout << "White King " + get_position(white_king_moves[i].row, white_king_moves[i].col);
						//is_check_and_mate();
						//m_chess_table->draw();
					}
					m_chess_table->empty_cell(m_white_king->get_row(), m_white_king->get_col());
					m_white_king->set_row(saved_row);
					m_white_king->set_col(saved_col);
					m_chess_table->set_figure(m_white_king, saved_row, saved_col);
				}
			}
		}
	}
	m_chess_table->empty_cell(m_white_king->get_row(), m_white_king->get_col());
	m_white_king->set_row(saved_row);
	m_white_king->set_col(saved_col);
	m_chess_table->set_figure(m_white_king, saved_row, saved_col);

	saved_row = m_white_queen->get_row();
	saved_col = m_white_queen->get_col();
	for (int i = 0; i < white_queen_moves.size(); i++) {
		move = m_white_queen->can_move(white_queen_moves[i].row, white_queen_moves[i].col);
		if (move != no_way) {
			if (m_chess_table->line_is_free(move, saved_row, saved_col, white_queen_moves[i].row, white_queen_moves[i].col)
				&& m_chess_table->cell_is_available(saved_row, saved_col, white_queen_moves[i].row, white_queen_moves[i].col)) {
				if (m_chess_table->set_figure(m_white_queen, white_queen_moves[i].row, white_queen_moves[i].col)) {
					m_chess_table->empty_cell(saved_row, saved_col);
					if (is_check_and_mate()) {
						exists = true;
						cout << "White Queen " + get_position(white_queen_moves[i].row, white_queen_moves[i].col);
						//is_check_and_mate();
						//m_chess_table->draw();
					}
					m_chess_table->empty_cell(m_white_queen->get_row(), m_white_queen->get_col());
					m_white_queen->set_row(saved_row);
					m_white_queen->set_col(saved_col);
					m_chess_table->set_figure(m_white_queen, saved_row, saved_col);
				}
				
			}
		}
	}
	m_chess_table->empty_cell(m_white_queen->get_row(), m_white_queen->get_col());
	m_white_queen->set_row(saved_row);
	m_white_queen->set_col(saved_col);
	m_chess_table->set_figure(m_white_queen, saved_row, saved_col);


	saved_row = m_white_bishop->get_row();
	saved_col = m_white_bishop->get_col();
	for (int i = 0; i < white_bishop_moves.size(); i++) {
		move = m_white_bishop->can_move(white_bishop_moves[i].row, white_bishop_moves[i].col);
		if (move != no_way) {
			if (m_chess_table->line_is_free(move, saved_row, saved_col, white_bishop_moves[i].row, white_bishop_moves[i].col)
				&& m_chess_table->cell_is_available(saved_row, saved_col, white_bishop_moves[i].row, white_bishop_moves[i].col)) {
				if (m_chess_table->set_figure(m_white_bishop, white_bishop_moves[i].row, white_bishop_moves[i].col)) {
					m_chess_table->empty_cell(saved_row, saved_col);
					if (is_check_and_mate()) {
						exists = true;
						cout << "White Bishop " + get_position(white_bishop_moves[i].row, white_bishop_moves[i].col);
						//is_check_and_mate();
						//m_chess_table->draw();
					};
					m_chess_table->empty_cell(m_white_bishop->get_row(), m_white_bishop->get_col());
					m_white_bishop->set_row(saved_row);
					m_white_bishop->set_col(saved_col);
					m_chess_table->set_figure(m_white_bishop, saved_row, saved_col);
				}
			}
		}
	}
	m_chess_table->empty_cell(m_white_bishop->get_row(), m_white_bishop->get_col());
	m_white_bishop->set_row(saved_row);
	m_white_bishop->set_col(saved_col);
	m_chess_table->set_figure(m_white_bishop, saved_row, saved_col);


	saved_row = m_white_knight->get_row();
	saved_col = m_white_knight->get_col();

	for (int i = 0; i < white_knight_moves.size(); i++) {
		move = m_white_knight->can_move(white_knight_moves[i].row, white_knight_moves[i].col);
		if (move != no_way) {
			if (m_chess_table->line_is_free(move, saved_row, saved_col, white_knight_moves[i].row, white_knight_moves[i].col) 
				&& m_chess_table->cell_is_available(saved_row, saved_col, white_knight_moves[i].row, white_knight_moves[i].col)) {
				if (m_chess_table->set_figure(m_white_knight, white_knight_moves[i].row, white_knight_moves[i].col)) {
					m_chess_table->empty_cell(saved_row, saved_col);
					if (is_check_and_mate()) {
						exists = true;
						cout << "White Knight " + get_position(white_knight_moves[i].row, white_knight_moves[i].col);
						//is_check_and_mate();
						//m_chess_table->draw();
					};
					m_chess_table->empty_cell(m_white_knight->get_row(), m_white_knight->get_col());
					m_white_knight->set_row(saved_row);
					m_white_knight->set_col(saved_col);
					m_chess_table->set_figure(m_white_knight, saved_row, saved_col);
				};
			}
		}
	}
	m_chess_table->empty_cell(m_white_knight->get_row(), m_white_knight->get_col());
	m_white_knight->set_row(saved_row);
	m_white_knight->set_col(saved_col);
	m_chess_table->set_figure(m_white_knight, saved_row, saved_col);

	if (!exists) {
		cout << "no move." << endl;
	}
}
bool Chess::is_check() {
	bool is_check = false;
	int black_king_row = m_black_king->get_row();
	int black_king_col = m_black_king->get_col();
	Moving_Type move;
	for (int i = 0; i < m_figures_count; i++) {
		move = m_figures[i]->can_move(black_king_row, black_king_col);
		if (move != no_way) {
			if (m_chess_table->line_is_free(move, m_figures[i]->get_row(), m_figures[i]->get_col(), black_king_row, black_king_col)) {
				//cout << m_figures[i]->get_name() << " " << move << endl;
				is_check = true;
				break;
			}
		}
	}
	return is_check;
}

bool Chess::is_mate() {
	bool is_mate = true;
	Moving_Type move;
	m_black_king->fill_moves_list();
	vector<Position> black_king_moves = m_black_king->get_moves_list();
	for (int i = 0; i < black_king_moves.size(); i++) {
		bool is_check_this = false;
		bool matches = false;
		for (int g = 0; g < m_figures_count; g++) {
			move = m_figures[g]->can_move(black_king_moves[i].row, black_king_moves[i].col);
			if (move != no_way) {
				if (m_chess_table->line_is_free(move, m_figures[g]->get_row(), m_figures[g]->get_col(), black_king_moves[i].row, black_king_moves[i].col)) {
					//cout << m_figures[g]->get_name() << " " << move << endl;
					is_check_this = true;
					break;
				}
			}
		}
		if (!is_check_this) {
			is_mate = false;
			break;
		}
	}
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
		cout << "Position is invalid" << endl;
		break;
	}

	row = 8 - (pos[1] - '0');
}

string Chess::get_position(int row, int col) {
	string pos;
	cout << pos << endl;

	switch (col)
	{
	case 0:
		pos += 'A';
		break;
	case 1:
		pos += 'B';
		break;
	case 2:
		pos += 'C';
		break;
	case 3:
		pos += 'D';
		break;
	case 4:
		pos += 'E';
		break;
	case 5:
		pos += 'F';
		break;
	case 6:
		pos += 'G';
		break;
	case 7:
		pos += 'H';
		break;
	default:
		cout << "Position is invalid" << endl;
		break;
	}

	row = (8 - row) + '0';
	pos += row;
	return pos;
}

bool Chess::is_possible_game() {
	int can_set = true;
	int diff_row = m_black_king->get_row() - m_white_king->get_row();
	int diff_col = m_black_king->get_col() - m_white_king->get_col();
	if (m_black_king->get_row() == -1 || m_black_king->get_col() == -1) {
		cout << "Black king is absent" << endl;
		can_set = false;
	}
	if (m_white_king->get_row() == -1 || m_white_king->get_col() == -1) {
		cout << "White king is absent" << endl;
		can_set = false;
	}
	if (diff_row == 0 || diff_row == 1 || diff_row == -1) {
		if (diff_col == 0 || diff_col == 1 || diff_col == -1) {
			can_set = false;
		}
	}
	return can_set;
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