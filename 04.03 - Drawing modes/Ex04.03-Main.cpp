#include "Game.h"


int main(int argc, char ** argv) {
	Game game("04.03 - Drawing modes", 800, 800,true,60,false);

	try {
		game.run();
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}