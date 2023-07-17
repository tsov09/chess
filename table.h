#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "figure.h"


class Matrix {
public:
	Matrix(int row, int column);
	virtual int cln_vrt() = 0;
	virtual void set_row(int row);
	virtual void set_column(int column);
protected:
	int m_row;
	int m_column;
	string** m_matrix;
};


class Table : public Matrix {
public:
	Table();
	bool line_is_free(Moving_Type, int, int, int, int);
public:
	int cln_vrt() override;
	void fill();
	void draw();
	void set_figure(Figure*, int, int);
};