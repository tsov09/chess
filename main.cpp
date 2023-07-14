#include <iostream>
#include <time.h>	
using namespace std;

#include "figure.h"
#include "table.h"
#include "game.h"

int main() {
	srand(time(0));
	Chess* chess = new Chess();
	chess->start();
	return 0;
}