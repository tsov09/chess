#pragma once
#include <iostream>
#include <string>
using namespace std;

enum Moving_Type {
	left_row,      // left straight
	right_row,	   // rigth straight
	up_col,		   // up straight
	down_col,	   // down straight
	up_left,       // up-left diagonal
	up_right,	   // up-right diagonal
	down_right,	   // down-right diagonal
	down_left,	   // down left diagonal
	up_left_N,     // row up 1 and col left 2 for knight
	up_right_N,    // row up 1 and col right 2 for knight
	down_right_N,  // row down 1 and col right 2 for knight
	down_left_N,   // row down 1 and col left 2 for knight
	left_up_N,     // row up 2 and col left 1 for knight
	right_up_N,    // row up 2 and col right 1 for knight
	right_down_N,  // row down 2 and col right 1 for knight
	left_down_N,   // row down 2 and col left 1 for knight
	no_way,
};

class Figure {
protected:
	string m_name;
	int m_row;
	int m_col;
	string m_color;
public:
	static string generate_name(string, string, string);
	string get_name();
	virtual Moving_Type can_move(int, int);
	virtual void moves_list(int**, int&	);
	bool is_valid_index(int);
	void set_row(int);
	void set_col(int);
	int get_row();
	int get_col();

};

class King : public Figure {
public:
	King(string);
	Moving_Type can_move(int, int);
	void moves_list(int**, int&) override;
};

class Queen : public Figure {
public:
	Queen(string);
	Moving_Type can_move(int, int);

};

class Bishop : public Figure {
public:
	Bishop(string);
	Moving_Type can_move(int, int);
};

class Knight : public Figure {
public:
	Knight(string);
	Moving_Type can_move(int, int);
};