#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "Test/test.hpp"

int main() {
    runTests()
    Game game;
    game.run();
    return 0;
}