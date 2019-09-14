#include <iostream>
#include <unordered_set>
#include <cstdlib>

#include "shapegame.hpp"
using namespace shapegame;



int main() {
    /* Create a new Game object with window width, height, and title */
	Game game(400, 600, "SHMUP");
    // Set the background color of the scene
	game.scene->setBackgroundColor(Color::BLUE);

    //[> Add a convenience key handler that closes the window when escape is pressed <]
    game.scene->addChild(std::make_unique<DebugKeyHandler>());

    game.run();
}
