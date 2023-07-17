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
	Figure() = default;
	Figure(const Figure&) = delete;
	Figure(Figure&&) = delete;
	Figure& operator = (const Figure&) = delete;
	Figure& operator = (Figure&&) = delete;
	virtual ~Figure();
	static string generate_name(string, string, string);
	string get_name();
	virtual Moving_Type can_move(int, int);
	bool is_valid_index(int);
	void set_row(int);
	void set_col(int);
	virtual void get_moves_list(int**, int&);
	int get_moves_size();
	int get_row();
	int get_col();

};

class King : public Figure {
public:
	King(string);
	King(const King&) = delete;
	King(King&&) = delete;
	King& operator = (const King&) = delete;
	King& operator = (King&&) = delete;
	~King() override;
	Moving_Type can_move(int, int);
	void get_moves_list(int**, int&) override;
};

class Queen : public Figure {
public:
	Queen(string);
	Queen(const Queen&) = delete;
	Queen(Queen&&) = delete;
	Queen& operator = (const Queen&) = delete;
	Queen& operator = (Queen&&) = delete;
	~Queen() override;
	Moving_Type can_move(int, int);

};

class Bishop : public Figure {
public:
	Bishop(string);
	Bishop(const Bishop&) = delete;
	Bishop(Bishop&&) = delete;
	Bishop& operator = (const Bishop&) = delete;
	Bishop& operator = (Bishop&&) = delete;
	~Bishop() override;
	Moving_Type can_move(int, int);
};

class Knight : public Figure {
public:
	Knight(string);
	Knight(const Knight&) = delete;
	Knight(Knight&&) = delete;
	Knight& operator = (const Knight&) = delete;
	Knight& operator = (Knight&&) = delete;
	~Knight() override;
	Moving_Type can_move(int, int);
};