#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "room.cpp"
#include <algorithm>

struct Direction {
    int right = 0;
    int down = 0;
};

class Dungeon {
public:
    Dungeon() : corridors() {
    }

    void generateDungeon(std::vector<Room>& rooms, int numRooms, int TILE_SIZE, int ROOM_MAX_WIDTH, int ROOM_MAX_HEIGHT, int WINDOW_WIDTH, int WINDOW_HEIGHT) {
        const int GRID_SIZE = 20;
        const float GRID_WIDTH = static_cast<float>(WINDOW_WIDTH) / GRID_SIZE;
        const float GRID_HEIGHT = static_cast<float>(WINDOW_HEIGHT) / GRID_SIZE;

        // Create a 2D array to represent the grid
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
    std::vector<Room> corridors;

    void generateRooms(std::vector<Room>& rooms, int numRooms, int x, int y, float GRID_WIDTH, float GRID_HEIGHT, int WINDOW_WIDTH, int WINDOW_HEIGHT, int GRID_SIZE) {
        if (rooms.size() >= numRooms) {
            return;
        }

        int roomWidth = 10 + rand() % 10;  // Random width
        int roomHeight = 10 + rand() % 10; // Random height
        int roomX = x * GRID_WIDTH + (GRID_WIDTH / 2) - (roomWidth / 2);
        int roomY = y * GRID_HEIGHT + (GRID_HEIGHT / 2) - (roomHeight / 2);

        // Adjust room position to be centered within the grid cell
        roomX += (GRID_WIDTH - roomWidth) / 2;
        roomY += (GRID_HEIGHT - roomHeight) / 2;

        Room newRoom(roomX, roomY, roomWidth, roomHeight);
        rooms.push_back(newRoom);

        // Randomly choose directions (right, down) to branch out
        std::vector<Direction> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        std::random_shuffle(directions.begin(), directions.end());

        for (const auto& dir : directions) {
            int newX = x + dir.right;
            int newY = y + dir.down;

            // Check if the new coordinates are within the grid
            if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) {
                generateRooms(rooms, numRooms, newX, newY, GRID_WIDTH, GRID_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, GRID_SIZE);
            }
        }
    }
};
