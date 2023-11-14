//
// Created by dannypa on 13.11.23.
//
#include "Assassin.hpp"
#include "random"

/// @brief Helper functions to return random int
/// @param engine Random number generator
/// @param a lower bound; included
/// @param b upper bound; not included
/// @return random int from [a, b)
int randInt(std::mt19937 &engine, int a, int b) {
  return a + abs((int) engine()) % (b - a);
}

void Assassin::Special() {
  std::mt19937 engine;
  engine.seed(5);
  position_ = sf::Vector2f((float) randInt(engine, 0, (int) window_.getSize().x),
                           (float) randInt(engine, 0, (int) window_.getSize().y));
}


