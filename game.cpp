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
	m_chess_table = new Table();
	m_chess_table->fill();
	m_black_king = new King("black");
	m_white_king = new King("white");
	m_figures.push_back(m_white_king);
	m_white_queen = new Queen("white");
	m_figures.push_back(m_white_queen);
	m_white_bishop = new Bishop("white");
	m_figures.push_back(m_white_bishop);
	m_white_knight = new Knight("white");
	m_figures.push_back(m_white_knight);
}

Chess::~Chess() {
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
			//is_check_and_mate_after_whites_move();
			is_check_and_mate_after_whites_move_twice();

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
void Chess::is_check_and_mate_after_whites_move_twice() {
	vector<Position> black_king_moves = m_black_king->get_moves_list(); //remove this
	bool exists = false;
	Moving_Type move;

	int saved_row;
	int saved_col;
	vector<Position> figure_moves;
	for (auto figure: m_figures) {
		saved_row = figure->get_row();
		saved_col = figure->get_col();
		figure_moves = figure->get_moves_list();
		for (int i = 0; i < figure_moves.size(); i++) {
			move = figure->can_move(figure_moves[i].row, figure_moves[i].col);
			if (move != no_way) {
				if (m_chess_table->line_is_free(move, saved_row, saved_col, figure_moves[i].row, figure_moves[i].col)
					&& m_chess_table->cell_is_available(saved_row, saved_col, figure_moves[i].row, figure_moves[i].col)) {
					if (m_chess_table->set_figure(figure, figure_moves[i].row, figure_moves[i].col)) {
						m_chess_table->empty_cell(saved_row, saved_col);
						if (is_possible_game()) {
							if (!is_check_and_mate()) {
								int saved_black_king_row = m_black_king->get_row();
								int saved_black_king_col = m_black_king->get_col();
								if (!is_mate()) {
									for (int g = 0; g < black_king_moves.size(); g++) {
										m_chess_table->empty_cell(m_black_king->get_row(), m_black_king->get_col());
										string cell_condition = m_chess_table->get_cell(black_king_moves[g].row, black_king_moves[g].col);
										Figure* removed_figure = nullptr;
										int removed_figure_index = -1;

										if (!(cell_condition == "   " || cell_condition == "###")) {
											for (int f = 0; f < m_figures.size(); f++) {
												if (m_figures[f]->get_name() == cell_condition) {
													removed_figure_index = f;
													removed_figure = m_figures[f];
													m_figures.erase(m_figures.begin() + f);
												}
											}
										}
										m_chess_table->set_figure(m_black_king, black_king_moves[g].row, black_king_moves[g].col);
										if (is_possible_game()) {
											if (!is_check()) {
												m_twice_move_mate_combinations.push_back(figure->get_full_name() + " " + get_position(figure_moves[i].row, figure_moves[i].col) + "\n" + "Black King " + get_position(black_king_moves[g].row, black_king_moves[g].col) + "\n");
												is_check_and_mate_after_whites_move();
												/*if (is_check_and_mate_after_whites_move()) {
													cout << "1. White King " + get_position(white_king_moves[i].row, white_king_moves[i].col);
													cout << "2. Black King " + get_position(black_king_moves[g].row, black_king_moves[g].col);
													cout << endl << "------------------------------------------" << endl;
												};*/
											}
										}
										if (removed_figure) {
											m_figures.insert(m_figures.begin() + removed_figure_index, removed_figure);
											removed_figure = nullptr;
										}
									}
									m_chess_table->empty_cell(m_black_king->get_row(), m_black_king->get_col());
									m_chess_table->set_figure(m_black_king, saved_black_king_row, saved_black_king_col);
								}
							}
						}
						m_chess_table->empty_cell(figure->get_row(), figure->get_col());
						m_chess_table->set_figure(figure, saved_row, saved_col);
					}
				}
			}
		}
		m_chess_table->empty_cell(figure->get_row(), figure->get_col());
		m_chess_table->set_figure(figure, saved_row, saved_col);
	}

	cout << "Mate combinations: " << endl << endl;
	if (m_twice_move_mate_combinations.size()) {
		for (auto iter : m_twice_move_mate_combinations) {
			cout << iter << endl << endl;
		}
	}
	else {
		cout << "No way.";
	}

}


bool Chess::is_check_and_mate_after_whites_move() {
	
	//vector<Position> black_king_moves = m_black_king->get_moves_list(); //remove this
	vector<Position> white_king_moves = m_white_king->get_moves_list();
	vector<Position> white_queen_moves = m_white_queen->get_moves_list();
	vector<Position> white_bishop_moves = m_white_bishop->get_moves_list();
	vector<Position> white_knight_moves = m_white_knight->get_moves_list();


	//cout << "Whites can win in case of moving: ";


	bool exists = false;
	Moving_Type move;


	int saved_row;
	int saved_col;

	vector<Position> figure_moves;
	for (auto figure : m_figures) {
		saved_row = figure->get_row();
		saved_col = figure->get_col();
		figure_moves = figure->get_moves_list();
		for (int i = 0; i < figure_moves.size(); i++) {
			move = figure->can_move(figure_moves[i].row, figure_moves[i].col);
			if (move != no_way) {
				if (m_chess_table->line_is_free(move, saved_row, saved_col, figure_moves[i].row, figure_moves[i].col)
					&& m_chess_table->cell_is_available(saved_row, saved_col, figure_moves[i].row, figure_moves[i].col)) {
					if (m_chess_table->set_figure(figure, figure_moves[i].row, figure_moves[i].col)) {
						m_chess_table->empty_cell(saved_row, saved_col);
						if (is_check_and_mate()) {
							exists = true;
							m_twice_move_mate_combinations[m_twice_move_mate_combinations.size() - 1] += (figure->get_full_name() + " " + get_position(figure_moves[i].row, figure_moves[i].col) + ", ");
							//cout << "3. White King " + get_position(white_king_moves[i].row, white_king_moves[i].col);
						}
						m_chess_table->empty_cell(figure->get_row(), figure->get_col());
						m_chess_table->set_figure(figure, saved_row, saved_col);
					}
				}
			}
		}
		m_chess_table->empty_cell(figure->get_row(), figure->get_col());
		m_chess_table->set_figure(figure, saved_row, saved_col);
	
	}


	if (!exists) {
		m_twice_move_mate_combinations.pop_back();
	}
	return exists;
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