#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "figure.h"
#include "table.h"
#include "game.h"

class Game {
	virtual bool start() = 0;
	virtual void stop() = 0;
};

class Chess : public Game{
public:
	Table* m_chess_table;
	int m_figures_count;
	Figure** m_figures;
	Figure* m_black_king;
	Figure* m_white_king;
	Figure* m_white_queen;
	Figure* m_white_bishop;
	Figure* m_white_knight;
	int* m_rand_pos;
	Chess();
	virtual bool start() override;
	virtual void stop() override;
private:
	void print_figures();
	int gen_rand(int, int);
	void gen_random_array(int);
	void set_random_pos();
};