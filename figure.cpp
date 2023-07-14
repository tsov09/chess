#include "figure.h"

#include <iostream>
#include <string>
using namespace std;


string Figure::generate_name(string type, string index, string color) {
	return type + index + color;
}

bool Figure::is_valid_position(int hor, int vert) {
	if (hor > 0 && hor < 9 && vert > 0 && vert < 9) {
		return true;
	}
	else {
		return false;
	}
}

King::King(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("K", "_", "W");
	}
	else if (color == "black") {
		m_name = Figure::generate_name("K", "_", "B");
	}
	else {
		cout << "Enter white or black." << endl;
	}
}
bool King::can_move(int horiz, int vertic) {
	if (Figure::is_valid_position(horiz, vertic)) {
		
	}
	return true;
}

Queen::Queen(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("Q", "_", "W");
	}
	else if (color == "black") {
		m_name = Figure::generate_name("Q", "_", "B");
	}
	else {
		cout << "Enter white or black." << endl;
	}
}

bool Queen::can_move(int horiz, int vertic) {
	if (Figure::is_valid_position(horiz, vertic)) {

	}
	return true;
}

Bishop::Bishop(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("B", "_", "W");
	}
	else if (color == "black") {
		m_name = Figure::generate_name("B", "_", "B");
	}
	else {
		cout << "Enter white or black." << endl;
	}
}

bool Bishop::can_move(int horiz, int vertic) {
	if (Figure::is_valid_position(horiz, vertic)) {

	}
	return true;
}

Knight::Knight(string color) {
	if (color == "white") {
		m_name = Figure::generate_name("N", "_", "W");
	}
	else if (color == "black") {
		m_name = Figure::generate_name("N", "_", "B");
	}
	else {
		cout << "Enter white or black." << endl;
	}
}

bool Knight::can_move(int horiz, int vertic) {
	if (Figure::is_valid_position(horiz, vertic)) {

	}
	return true;
}