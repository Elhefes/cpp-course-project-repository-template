#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "Test/test.hpp"
#include <ctime>
#include <cstdlib>

int main() {
    srand(static_cast<unsigned int>(time(0)));
    runTests();
    Game game;
    game.run();
    return 0;
}