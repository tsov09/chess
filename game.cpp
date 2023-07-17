#include "game.h"

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
void Chess::print_figures() {
	for (int i = 0; i < m_figures_count; i++) {
		m_figures[i]->get_name();
	}
}
bool Chess::start() {
	set_random_pos();
	m_chess_table->draw();

	int** black_king_moves = new int* [8];
	int moves_size = 0;
	for (int i = 0; i < 8; i++) {
		black_king_moves[i] = new int[2];
	}
	m_black_king->moves_list(black_king_moves, moves_size);

	for (int i = 0; i < moves_size; i++) {
		cout << black_king_moves[i][0] << "," << black_king_moves[i][1] << endl;
	}

	int black_king_row = m_black_king->get_row();
	int black_king_col = m_black_king->get_col();


	Moving_Type move;
	bool is_check = false;
	for (int i = 0; i < m_figures_count; i++) {
		move = m_figures[i]->can_move(black_king_row, black_king_col);
		cout << move << m_figures[i]->get_name() << endl;
		if (move != no_way) {
			if (m_chess_table->line_is_free( move, m_figures[i]->get_row(), m_figures[i]->get_col(), black_king_row, black_king_col)) {
				cout << move << m_figures[i]->get_name() << endl;
				is_check = true;
				break;
			}
		}
	}

	bool is_mate = true;

	if (is_check) {
		for (int i = 0; i < moves_size; i++) {
			bool is_check_this = false;
			for (int g = 0; g < m_figures_count; g++) {
				move = m_figures[g]->can_move(black_king_moves[i][0], black_king_moves[i][1]);
				cout << move << m_figures[i]->get_name() << " in mate" << black_king_moves[i][0] << "," << black_king_moves[i][1] << endl;
				if (move != no_way) {
					if (m_chess_table->line_is_free(move, m_figures[g]->get_row(), m_figures[g]->get_col(), black_king_moves[i][0], black_king_moves[i][1])) {
						is_check_this = true;
						break;
					}
				}
			}
			if (!is_check_this) {
				cout << black_king_moves[i][0] << "," << black_king_moves[i][1] << " safe" << endl;
				is_mate = false;
				break;
			}
		}
	}

	if (!is_check) {
		cout << "NOT CHECK" << endl;
	}
	if (is_check && !is_mate) {
		cout << "CHECK NOT MATE" << endl;
	}
	if (is_check && is_mate) {
		cout << "CHECKMATE" << endl;
		return true;
	}


};
void Chess::stop() {
	cout << endl;
};

int Chess::gen_rand(int start, int end) {
	int n = rand() % (end - start) + start;
	if (n % 10 == 0 || n % 10 == 9) {
		return gen_rand(start, end);
	}
	return n;
};
void Chess::gen_random_array(int size) {
	m_rand_pos = new int[size];
	int next = 0;
	int n;
	while (next < size) {
		n = gen_rand(11, 88);
		bool exists = false;
		for (int i = 0; i < next; i++) {
			if (m_rand_pos[i] == n) {
				exists = true;
				break;
			}
		}
		if (!exists) {
			m_rand_pos[next] = n;
			next++;
		}
	}
};

void Chess::set_random_pos() {
	gen_random_array(m_figures_count + 1);
	int row;
	int col;

	row = m_rand_pos[0] / 10 - 1;
	col = m_rand_pos[0] % 10 - 1;
	m_chess_table->set_figure(m_black_king, row, col);
	m_black_king->set_row(row);
	m_black_king->set_col(col);

	for (int i = 1; i < m_figures_count; i++) {
		row = m_rand_pos[i] / 10 - 1;
		col = m_rand_pos[i] % 10 - 1;
		m_chess_table->set_figure(m_figures[i], row, col);
		m_figures[i]->set_row(row);
		m_figures[i]->set_col(col);
	}


	/*m_chess_table->set_figure(m_black_king, 0, 4);
	m_black_king->set_row(0);
	m_black_king->set_col(4);
	m_chess_table->set_figure(m_white_king, 1, 3);
	m_white_king->set_row(1);
	m_white_king->set_col(3);
	m_chess_table->set_figure(m_white_queen, 1, 4);
	m_white_queen->set_row(1);
	m_white_queen->set_col(4);
	m_chess_table->set_figure(m_white_bishop, 7, 0);
	m_white_bishop->set_row(7);
	m_white_bishop->set_col(0);
	m_chess_table->set_figure(m_white_knight, 2, 3);
	m_white_knight->set_row(2);
	m_white_knight->set_col(3);*/
}

