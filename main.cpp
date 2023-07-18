#include <iostream>
#include <time.h>	
using namespace std;

#include "figure.h"
#include "table.h"
#include "game.h"


void play_chess() {
	Chess* chess = new Chess();
	chess->set_figure("Black King", "e8");
	chess->set_figure("White King", "d6");
	chess->set_figure("White Queen", "f5");
	chess->set_figure("White Bishop", "h5");
	chess->set_figure("White Knight", "b7");
	chess->start();
	delete chess;
	chess = nullptr;
}

int main() {
	srand(time(0));
	play_chess();
	return 0;
}