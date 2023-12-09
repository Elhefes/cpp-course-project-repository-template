#include "game.hpp"
#include "Test/test.hpp"
#include <ctime>
#include <cstdlib>

int main() {
  srand(static_cast<unsigned int>(time(nullptr)));
  runTests();
  Game game;
  game.Run();
  return 0;
}