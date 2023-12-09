#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../dungeon.hpp"
#include "../textureManager.hpp"
#include "../Creature/Creature.hpp"
#include "../Creature/GameCharacter.hpp"

bool testDungeonGeneration() {
  // Test dungeon_ generation with 5 rooms_
  int numRooms = 5;
  int TILE_SIZE = 32; // Example tile size
  int WINDOW_WIDTH = 800; // Example window width
  int WINDOW_HEIGHT = 600; // Example window height

  std::vector<Room> rooms;
  std::vector<Room> corridors;
  sf::Texture player_t;

  Dungeon dungeon;
  dungeon.GenerateDungeon(rooms, corridors, numRooms, TILE_SIZE, WINDOW_WIDTH, WINDOW_HEIGHT);

  // Check if the number of generated rooms_ matches the expected number
  if (rooms.size() != numRooms) {
    std::cout << "Test failed: Incorrect number of rooms_ generated." << std::endl;
    return false;
  }

  // Check if the number of generated corridors_ matches the expected number
  if (corridors.size() != --numRooms) {
    std::cout << "Test failed: Incorrect number of corridors_ generated." << std::endl;
    return false;
  }

  sf::RenderWindow test_window;
  // Create a test creature
  Monster test_creature("test", "creature", 50, 10.0f,
                        sf::Vector2f(0, 0),
                        test_window, Room(0, 0, 0, 0, false), 10, player_t);

  // Check if the position matches the expected postition
  if (test_creature.GetPosition() != sf::Vector2f(0, 0)) {
    std::cout << "Test failed: Incorrect initial postition of test creature." << std::endl;
    return false;
  }

  // Add health postions to the test creatures inventory_
  test_creature.GetInventory().AddPotion(HealthPotion(), 3);

  // Check if the size of the inventory_ matches the expected size

  if (test_creature.GetInventory().GetSize() != 1) {
    std::cout << "Test failed: Incorrect inventory_ size." << std::endl;
    return false;
  }

  // All tests passed
  std::cout << "All tests passed\n";
  return true;
}

int runTests() {
  // Run tests
  if (!testDungeonGeneration()) {
    std::cout << "Tests failed!\n";
    return 1;
  }

  return 0;
}
