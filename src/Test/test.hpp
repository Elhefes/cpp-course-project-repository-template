#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../dungeon.hpp"
#include "../textureManager.hpp"
#include "../Creature/GameCharacter.hpp"

bool testDungeonGeneration() {
    // Test dungeon generation with 5 rooms
    int numRooms = 5;
    int TILE_SIZE = 32; // Example tile size
    int WINDOW_WIDTH = 800; // Example window width
    int WINDOW_HEIGHT = 600; // Example window height

    std::vector<Room> rooms;
    std::vector<Room> corridors;

    Dungeon dungeon;
    dungeon.generateDungeon(rooms, corridors, numRooms, TILE_SIZE, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Check if the number of generated rooms matches the expected number
    if (rooms.size() != numRooms) {
        std::cout << "Test failed: Incorrect number of rooms generated." << std::endl;
        return false;
    }

    // Check if the number of generated corridors matches the expected number
    if (corridors.size() != --numRooms) {
        std::cout << "Test failed: Incorrect number of corridors generated." << std::endl;
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
