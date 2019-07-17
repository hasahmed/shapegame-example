#include <iostream>
#include "shapegame.hpp"
using namespace shapegame;


/* Create a player class which extends
 * TriangleIsosceles built in class. In order to hook into the callbacks
 * of the engine you need to create a class that overrides the callback
 * methods
 */
class Player : public TriangleIsosceles {
    public:
        /* Construct the player with a triangle 100px wide, 100px tall
         * at position 100, 100, and with a color of green
         */
        Player() : TriangleIsosceles(100, 100, Position(100, 100), Color::GREEN) {}

        /* Override the update method. This method is called every frame */
        void update() override {
            /* Set the X position of the player to the X position of the mouse */
            this->setPosition(Position(Input::Mouse::getPos().x, 590));
            /* Move the player over 50 pixels so the mouse is in the middle */
            /* Origin is the corner by default */
            this->translate(-50, 0);
        }
};

int main() {
    /* Create a new Game object with window width, height, and window title */
	Game game(400, 600, "SHMUP");
    /* Set the background color of the scene */
	game.scene->setBackgroundColor(Color::BLUE);

    /* Add a convenience key handler that closes the window when escape is pressed */
    game.scene->addChild(std::make_unique<DebugKeyHandler>());

    /* Add a child to the scene */
	//game.scene->addChild(new TriangleIsosceles(100, 100, Position(100, 100), Color::BLACK));
	game.scene->addChild(std::make_unique<Player>());

    game.run();
}
