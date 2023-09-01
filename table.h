#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "figure.h"


class Matrix {
public:
	Matrix(int row, int column);
	Matrix(const Matrix&) = delete;
	Matrix(Matrix&&) = delete;
	Matrix& operator = (const Matrix&) = delete;
	Matrix& operator = (Matrix&&) = delete;
	virtual ~Matrix();
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
	Table(const Table&) = delete;
	Table(Table&&) = delete;
	Table& operator = (const Table&) = delete;
	Table& operator = (Table&&) = delete;
	~Table() override;
	bool line_is_free(Moving_Type, int, int, int, int);
public:
	int cln_vrt() override;
	void fill();
	void draw();
	bool set_figure(Figure*, int, int);
	void empty_cell(int, int);
	string get_cell(int, int);
	bool cell_is_available(int, int, int, int);
};