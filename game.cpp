#include "game.h"

Chess::Chess() : m_figures_count(5) {
	int next = 0;
	m_figures = new Figure*[m_figures_count];
	m_chess_table = new Table();
	m_chess_table->fill();
	m_black_king = new King("black");
	m_figures[next++] = m_black_king;
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
void Chess::start() {
	set_random_pos();
	m_chess_table->draw();
	cout << endl;
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
	gen_random_array(5);
	cout << endl;
	for (int i = 0; i < m_figures_count; i++) {
		m_chess_table->set_figure(m_figures[i], m_rand_pos[i]);
	}
}

