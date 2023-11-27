#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <vector>
#include "room.hpp"

/**
 * @brief Enumeration representing directions.
 */
enum Direction {
    UP,     /**< Up direction. */
    DOWN,   /**< Down direction. */
    LEFT,   /**< Left direction. */
    RIGHT   /**< Right direction. */
};

/**
 * @brief Class representing a dungeon.
 */

class Dungeon {
public:
    /**
     * @brief Constructor for the Dungeon class.
     */
    Dungeon();
    ~Dungeon();

    /**
     * @brief Generates a dungeon with rooms.
     *
     * @param rooms Vector to store generated rooms.
     * @param corridors Vector to store generated corridors.
     * @param numRooms Number of rooms to generate.
     * @param TILE_SIZE Size of a tile.
     * @param WINDOW_WIDTH Width of the game window.
     * @param WINDOW_HEIGHT Height of the game window.
     */

    void generateDungeon(std::vector<Room>& rooms, std::vector<Room>& corridors, int numRooms, int TILE_SIZE, int WINDOW_WIDTH, int WINDOW_HEIGHT);

private:
    static const int GRID_SIZE = 20;
    std::vector<std::vector<bool>> roomGrid;

    /**
     * @brief Recursively generates rooms and corridors that connect the rooms in the dungeon.
     *
     * @param rooms Vector to store generated rooms.
     * @param rooms Vector to store generated corridors.
     * @param numRooms Number of rooms to generate.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param GRID_WIDTH Width of a grid cell.
     * @param GRID_HEIGHT Height of a grid cell.
     * @param WINDOW_WIDTH Width of the window.
     * @param WINDOW_HEIGHT Height of the window.
     * @param GRID_SIZE Size of the grid.
     */

    void generateRooms(std::vector<Room>& rooms, std::vector<Room>& corridors, int numRooms, int x, int y, float GRID_WIDTH, float GRID_HEIGHT, int WINDOW_WIDTH, int WINDOW_HEIGHT, int GRID_SIZE);
};

#endif
