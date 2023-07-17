#include <iostream>
#include <time.h>	
using namespace std;

#include "figure.h"
#include "table.h"
#include "game.h"


void play_chess() {
	Chess* chess = new Chess();
	chess->set_figure("Black King", "H8");
	chess->set_figure("White King", "E5");
	chess->set_figure("White Queen", "H3");
	chess->set_figure("White Bishop", "E6");
	chess->set_figure("White Knight", "D6");
	chess->start();
	delete chess;
}

int main() {
	srand(time(0));
	play_chess();
	return 0;
}
