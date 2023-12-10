#include <random>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "dungeon.hpp"

Dungeon::Dungeon() : roomGrid_(GRID_SIZE, std::vector<bool>(GRID_SIZE, false)) {
}

Dungeon::~Dungeon() = default;

void Dungeon::GenerateDungeon(std::vector<Room> &rooms,
                              std::vector<Room> &corridors,
                              int numRooms,
                              int TILE_SIZE,
                              int WINDOW_WIDTH,
                              int WINDOW_HEIGHT) {
  const float GRID_WIDTH = static_cast<float>(WINDOW_WIDTH) / GRID_SIZE;
  const float GRID_HEIGHT = static_cast<float>(WINDOW_HEIGHT) / GRID_SIZE;

  // Create a 2D array to represent the grid that rooms_ are placed in
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

  GenerateRooms(rooms,
                corridors,
                numRooms,
                GRID_SIZE / 2,
                GRID_SIZE / 2,
                GRID_WIDTH,
                GRID_HEIGHT,
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
                GRID_SIZE);
}

void Dungeon::GenerateRooms(std::vector<Room> &rooms,
                            std::vector<Room> &corridors,
                            int numRooms,
                            int x,
                            int y,
                            float GRID_WIDTH,
                            float GRID_HEIGHT,
                            int WINDOW_WIDTH,
                            int WINDOW_HEIGHT,
                            int GRID_SIZE) {
  if (rooms.size() >= numRooms) {
    return;
  }

  int roomWidth = ROOM_MIN_SIZE + rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE);  // Random width of room
  int roomHeight = ROOM_MIN_SIZE + rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE); // Random height of room
  int roomX = x * GRID_WIDTH + (GRID_WIDTH / 2) - (roomWidth / 2);
  int roomY = y * GRID_HEIGHT + (GRID_HEIGHT / 2) - (roomHeight / 2);

  Room newRoom(roomX, roomY, roomWidth, roomHeight, false);
  rooms.push_back(newRoom);

  if (rooms.size() > 1) {
    Room lastRoom = rooms[rooms.size() - 2];
    int lastRoomX = (lastRoom.x + (lastRoom.width / 2) - (GRID_WIDTH / 2)) / GRID_WIDTH;
    int lastRoomY = (lastRoom.y + (lastRoom.height / 2) - (GRID_HEIGHT / 2)) / GRID_HEIGHT;

    int shorterSide =
        (lastRoomX == x) ? std::min(newRoom.width, lastRoom.width) : std::min(newRoom.height, lastRoom.height);

    if (lastRoomX > x) {
      // left
      Room corridor(newRoom.x + newRoom.width,
                    newRoom.y + (newRoom.height / 2) + rand() % (shorterSide) - shorterSide / 2,
                    lastRoom.x - newRoom.x - newRoom.width,
                    1,
                    true);
      corridors.push_back(corridor);
    } else if (lastRoomX < x) {
      // right
      Room corridor(lastRoom.x + lastRoom.width,
                    newRoom.y + (newRoom.height / 2) + rand() % (shorterSide) - shorterSide / 2,
                    lastRoom.x - newRoom.x + lastRoom.width,
                    1,
                    true);
      corridors.push_back(corridor);
    } else if (lastRoomY > y) {
      // up
      Room corridor(newRoom.x + (newRoom.width / 2) + rand() % (shorterSide) - shorterSide / 2,
                    newRoom.y + newRoom.height,
                    1,
                    lastRoom.y - newRoom.y - newRoom.height,
                    true);
      corridors.push_back(corridor);
    } else {
      // down
      Room corridor(newRoom.x + (newRoom.width / 2) + rand() % (shorterSide) - shorterSide / 2,
                    lastRoom.y + lastRoom.height,
                    1,
                    lastRoom.y - newRoom.y + lastRoom.height,
                    true);
      corridors.push_back(corridor);
    }
  }

  roomGrid_[x][y] = true;

  // Randomly choose directions to branch out
  std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
  std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device()()));

  // Flag to check if a valid direction is found
  bool validDirectionFound = false;

  for (const auto &dir : directions) {
    int newX = x;
    int newY = y;

    switch (dir) {
      case UP:newY--;
        break;
      case DOWN:newY++;
        break;
      case LEFT:newX--;
        break;
      case RIGHT:newX++;
        break;
    }

    // Check if the new coordinates are within the grid
    if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE && !roomGrid_[newX][newY]) {
      validDirectionFound = true;
      GenerateRooms(rooms,
                    corridors,
                    numRooms,
                    newX,
                    newY,
                    GRID_WIDTH,
                    GRID_HEIGHT,
                    WINDOW_WIDTH,
                    WINDOW_HEIGHT,
                    GRID_SIZE);
      break;
    }
  }
  // If no valid direction is found, clear vectors and restart from the center
  if (!validDirectionFound) {
    rooms.clear();
    corridors.clear();
    roomGrid_.assign(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));
    GenerateRooms(rooms,
                  corridors,
                  numRooms,
                  GRID_SIZE / 2,
                  GRID_SIZE / 2,
                  GRID_WIDTH,
                  GRID_HEIGHT,
                  WINDOW_WIDTH,
                  WINDOW_HEIGHT,
                  GRID_SIZE);
    return;
  }
}