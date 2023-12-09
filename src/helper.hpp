//
// Created by dannypa on 20.11.23.
//

#ifndef DUNGEONCRAWLER_SRC_HELPER_HPP_
#define DUNGEONCRAWLER_SRC_HELPER_HPP_
#include "iostream"
#include "SFML/Graphics.hpp"
#include "random"

template<typename T>
T bound(T x, T lower, T upper, T EPS) {
  x = std::max(lower + EPS, x);
  x = std::min(x, upper - EPS);
  return x;
}

namespace help {
/// @brief returns the square of the vector.
/// @tparam T type of vector values
/// @param v the vector to square
/// @return square of the vector.
template<typename T>
T square(const sf::Vector2<T> v) {
  return v.x * v.x + v.y * v.y;
}

/// @brief returns the length of the vectir
/// @tparam T
/// @param v
/// @return length.
template<typename T>
double len(const sf::Vector2<T> v) {
  return sqrt(square(v));
}

/// @brief Checks if two numerical values are close enough (|a - b| < EPS)
/// @tparam T type of values
/// @param EPS precision desired
/// @return true if close enough, false otherwise
template<typename T>
bool close(T a, T b, T EPS) {
  return std::abs(a - b) < EPS;
}

/// @brief Checks if two positions are close enough (|v1 - v2| <= maxDist).
/// @tparam T type of vector values (float / int)
/// @param v1 first position
/// @param v2 second position
/// @return true if close enough, false otherwise
template<typename T>
bool close(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2, T maxDist) {
  return square(v1 - v2) <= maxDist * maxDist;
}
//std::mt19937 engine; // todo: why the fuck it gives me "multiple definitions" error particularly on this function
//
//int RandInt() {
//  // [0; INTMAX?)
//  return abs((int) engine());
//}
//
//int RandInt(int b) {
//  // [0; b)
//  return RandInt() % b;
//}
//
//int RandInt(int a, int b) {
//  // [a; b)
//  return a + RandInt(b - a);
//}
}

#endif //DUNGEONCRAWLER_SRC_HELPER_HPP_

