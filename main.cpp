#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>	
using namespace std;

#include "figure.h"
#include "table.h"
#include "game.h"


void play_chess() {
	ifstream infile("positions.txt");

	Chess* chess = new Chess();

	std::string line;
	while (std::getline(infile, line))
	{
		chess->set_figure(line.substr(0, line.size() - 3), line.substr(line.size() - 2, line.size()));
	}
	chess->start();
	delete chess;
	chess = nullptr;
}

int main() {

	srand(time(0));
	play_chess();
	return 0;
}