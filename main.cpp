#include <iostream>
#include <time.h>	
using namespace std;

#include "figure.h"
#include "table.h"
#include "game.h"


void play_chess() {
	Chess* chess = new Chess();
	chess->set_figure("Black King", "f5");
	chess->set_figure("White King", "h5");
	chess->set_figure("White Queen", "e3");
	chess->set_figure("White Bishop", "g7");
	chess->set_figure("White Knight", "d4");
	chess->start();
	delete chess;
	chess = nullptr;
}

int main() {
	srand(time(0));
	play_chess();
	return 0;
}