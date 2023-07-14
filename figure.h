#pragma once
#include <iostream>
#include <string>
using namespace std;

class Figure {
protected:
	string m_name;
	string m_position;
	string m_color;
public:
	static string generate_name(string, string, string);
	string get_name() {
		return m_name;
	}
	//virtual bool can_move(int, int);
	static bool is_valid_position(int, int);
};

class King : public Figure {
public:
	King(string);
	bool can_move(int, int);

};

class Queen : public Figure {
public:
	Queen(string);
	bool can_move(int, int);

};

class Bishop : public Figure {
public:
	Bishop(string);
	bool can_move(int, int);
};

class Knight : public Figure {
public:
	Knight(string);
	bool can_move(int, int);
};