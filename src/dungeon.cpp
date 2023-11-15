#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "room.cpp"
#include <algorithm>

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
    Dungeon() : corridors(), roomGrid(GRID_SIZE, std::vector<bool>(GRID_SIZE, false)) {
    }

    /**
     * @brief Generates a dungeon with rooms.
     *
     * @param rooms Vector to store generated rooms.
     * @param numRooms Number of rooms to generate.
     * @param TILE_SIZE Size of a tile.
     * @param WINDOW_WIDTH Width of the game window.
     * @param WINDOW_HEIGHT Height of the game window.
     */
    void generateDungeon(std::vector<Room>& rooms, int numRooms, int TILE_SIZE, int WINDOW_WIDTH, int WINDOW_HEIGHT) {
        const float GRID_WIDTH = static_cast<float>(WINDOW_WIDTH) / GRID_SIZE;
        const float GRID_HEIGHT = static_cast<float>(WINDOW_HEIGHT) / GRID_SIZE;

        // Create a 2D array to represent the grid that rooms are placed in
        std::pair<int, int> grid[GRID_SIZE][GRID_SIZE];

        // Calculate the center of the grid
        int centerX = GRID_SIZE / 2;
        int centerY = GRID_SIZE / 2;

        // Initialize the grid with coordinates scaled based on WINDOW_WIDTH and WINDOW_HEIGHT
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                int x = i;
                int y = j;
                grid[i][j] = std::make_pair(x, y);
            }
        }

        generateRooms(rooms, numRooms, GRID_SIZE / 2, GRID_SIZE / 2, GRID_WIDTH, GRID_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, GRID_SIZE);
    }

private:
    const static int GRID_SIZE = 20;
    std::vector<Room> corridors; /**< Vector to store corridors. */
    std::vector<std::vector<bool>> roomGrid; /**< 2D grid representing which grid instances have rooms. */

    /**
     * @brief Recursively generates rooms in the dungeon.
     *
     * @param rooms Vector to store generated rooms.
     * @param numRooms Number of rooms to generate.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @param GRID_WIDTH Width of a grid cell.
     * @param GRID_HEIGHT Height of a grid cell.
     * @param WINDOW_WIDTH Width of the window.
     * @param WINDOW_HEIGHT Height of the window.
     * @param GRID_SIZE Size of the grid.
     */
    void generateRooms(std::vector<Room>& rooms, int numRooms, int x, int y, float GRID_WIDTH, float GRID_HEIGHT, int WINDOW_WIDTH, int WINDOW_HEIGHT, int GRID_SIZE) {
        if (rooms.size() >= numRooms) {
            return;
        }

        if (!roomGrid[x][y]) {
            int roomWidth = 10 + rand() % 10;  // Random width of room
            int roomHeight = 10 + rand() % 10; // Random height of room
            int roomX = x * GRID_WIDTH + (GRID_WIDTH / 2) - (roomWidth / 2);
            int roomY = y * GRID_HEIGHT + (GRID_HEIGHT / 2) - (roomHeight / 2);

            // Adjust room position to be centered within the grid cell
            roomX += (GRID_WIDTH - roomWidth) / 2;
            roomY += (GRID_HEIGHT - roomHeight) / 2;

            Room newRoom(roomX, roomY, roomWidth, roomHeight);
            rooms.push_back(newRoom);

            roomGrid[x][y] = true;

            // Randomly choose directions (right, down) to branch out
            std::vector<Direction> directions = { UP, DOWN, LEFT, RIGHT };
            std::random_shuffle(directions.begin(), directions.end());

            for (const auto& dir : directions) {
                int newX = x;
                int newY = y;

                switch (dir) {
                case UP:
                    newY--;
                    break;
                case DOWN:
                    newY++;
                    break;
                case LEFT:
                    newX--;
                    break;
                case RIGHT:
                    newX++;
                    break;
                }

                // Check if the new coordinates are within the grid
                if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) {
                    generateRooms(rooms, numRooms, newX, newY, GRID_WIDTH, GRID_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, GRID_SIZE);
                }
            }
        }
    }
};
