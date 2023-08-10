#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

#include "figure.h"
#include "table.h"
#include "game.h"

class Game {
public:
	virtual void start() = 0;
	virtual void stop() = 0;
	Game() = default;
	Game(const Game&) = delete;
	Game (Game&&) = delete;
	Game& operator = (const Game&) = delete;
	Game& operator = (Game&&) = delete;
	virtual ~Game();
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
	//int* m_rand_pos;
	Chess();
	Chess(const Chess&) = delete;
	Chess(Chess&&) = delete;
	Chess& operator = (const Chess&) = delete;
	Chess& operator = (Chess&&) = delete;
	~Chess() override;
	virtual void start() override;
	virtual void stop() override;
	void set_figure(string, string);
private:
	static bool is_valid_ind(int);
	void print_figures();
	//int gen_rand(int, int);
	//void gen_random_array(int);
	//void set_random_pos();
	//void set_figures();
	void get_coordinates(string, int&, int&);
	string get_position(int, int);
	bool is_check_and_mate();
	void is_check_and_mate_after_whites_move();
	bool is_check();
	bool is_mate();
	bool is_possible_game();
};