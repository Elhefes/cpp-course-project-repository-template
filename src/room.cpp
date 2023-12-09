#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include "room.hpp"

Room::Room(int x, int y, int width, int height, bool isCorridor)
    : x(x), y(y), width(width), height(height), isCorridor_(isCorridor) {
  // Initialize random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 1);

  tileTextures.resize(abs(width), std::vector<sf::Texture *>(abs(height)));

  for (int i = 0; i < abs(width); ++i) {
    for (int j = 0; j < abs(height); ++j) {
      short int random = dis(gen);

      if (random == 1) {
        tileTextures[i][j] = &room_t1;
      } else {
        tileTextures[i][j] = &room_t2;
      }
    }
  }
  id_ = rand();
}

Room::~Room() {
}

std::tuple<bool, float, float, sf::Vector2f> Room::IsInside(sf::Vector2f pos, float sz) const {
  const float EPS = 0.1;
  auto xMin = (float) x /*+ sz / 2*/, xMax = (float) (x + std::abs(width)) /*- sz / 2*/;
  auto yMin = (float) y /*+ sz / 2*/, yMax = (float) (y + std::abs(height)) /*- sz / 2*/;
  bool flag = (xMin <= pos.x && pos.x <= xMax && yMin <= pos.y && pos.y <= yMax);
  float xMul = 1, yMul = 1;
  if (help::close(pos.x, yMin, EPS) || help::close(pos.x, xMax, EPS)) xMul *= -1;
  if (help::close(pos.y, yMin, EPS) || help::close(pos.y, yMax, EPS)) yMul *= -1;
  pos.x = bound(pos.x, xMin, xMax, 0.9f * EPS);
  pos.y = bound(pos.y, yMin, xMax, 0.9f * EPS);
  return {flag, xMul, yMul, pos};
}
sf::Vector2f Room::RandomPos(float sz) const {
  return {(float) RandInt(x + sz / 2, x + width - sz / 2), (float) RandInt(y + sz / 2, y + height - sz / 2)};
}
int Room::RandInt(int a, int b) {
  if (b == a) return a; // shouldnt be like that, but it is what it is
  return a + rand() % (b - a);
}
