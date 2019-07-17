#include <iostream>
#include <unordered_set>

#include "shapegame.hpp"
using namespace shapegame;

class Enemy;
std::unordered_set<Enemy*> enemy_list;



class Enemy : public Rectangle {
    public:
        Enemy(Position pos) : Rectangle(40, 40, pos, Color::RED) {}
        void update() override {
            this->translate(0, 5);

            /* If this enemy is below the screen */
            if (this->pos.y > 700) {
                /* This kill its self */
                this->kill();
            }
        }
};


class Bullet : public Rectangle {
    public:
        /* A constructor for our bullet class that takes a Position as an argument
         * It then initilizes the rectangle that will be representing the bullet
         * with a width, height, position, and color */
        Bullet(Position pos) : Rectangle(5, 30, pos, Color::WHITE) {}


        /* Override the update method. This will be called every frame by the
         * engine once the object instance is added to the scene */
        void update() override {
            /* Every frame move up pixels */
            this->translate(0, -30);

            /* If this bullet is above the screen */
            if (this->pos.y < -30) {
                /* This kill its self */
                this->kill();
            }
        }
};

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
        Player() : TriangleIsosceles(50, 50, Position(100, 100), Color::GREEN) {}

        /* Override the update method. This method is called every frame */
        void update() override {
            /* Set the X position of the player to the X position of the mouse */
            this->setPosition(Position(Input::Mouse::getPos().x, 590));
            /* Move the player over 50 pixels so the mouse is in the middle */
            /* Origin is the corner by default */
            this->translate(-25, 0);
        }
        /* override the mouse click handler to recieve callbacks when
         * mouse clicks happen
         */
        void onMouseClick(Input::Mouse::Btn btn, Input::Action action) override {
            /* check to see if the left mouse button is down */
            if (btn == Input::Mouse::Btn::LEFT && action == Input::Action::DOWN) {
                /* if it is down then shoot */

                /* A lot of things are happening here. Were creating an instance of
                 * bullet using make_unique
                 * Were adding that bullet to the scene.
                 * Notice that we are getting the scene by accessing the game
                 * instance via the inst() static method of the Game object.
                 * Then notice that scene->addChild returns a reference to the
                 * child that was added. We can use this reference to perform
                 * operations on the object even though it is already added to the
                 * scene. This is why we can move it around via the translate
                 * method call below*/
                Object *bullet = Game::inst().scene->addChild(std::make_unique<Bullet>(this->pos));
                /* Move the bullet so it looks like its coming out of the tip of
                 * the player */
                bullet->translate(25, -40);
            }
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
    game.scene->addChild(std::make_unique<Timer>(1000, true, true, [](){
            Game::inst().scene->addChild(std::make_unique<Enemy>(Position(200, -60)));
        }
    ));

    game.run();
}
