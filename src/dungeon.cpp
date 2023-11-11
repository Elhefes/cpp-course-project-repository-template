#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "room.cpp"

const int tileSize = 10;

bool roomConstraintsOverlap(Room existingRoom, Room newRoom) {
    return (newRoom.x * tileSize < existingRoom.x  * tileSize + existingRoom.width * tileSize &&
            newRoom.x * tileSize + newRoom.width * tileSize > existingRoom.x * tileSize &&
            newRoom.y * tileSize < existingRoom.y * tileSize + existingRoom.height * tileSize &&
            newRoom.y * tileSize + newRoom.height * tileSize > existingRoom.y * tileSize);
}

void generateRooms(std::vector<Room>& rooms, int numRooms, int maxWidth, int maxHeight) {
    int maxDistance = 15;
    while (rooms.size() < numRooms) {
        int roomWidth = 3 + rand() % 9;  // Random width in terms of tiles
        int roomHeight = 3 + rand() % 9;  // Random height in terms of tiles
        int roomX;
        int roomY;
        
        if (rooms.empty()) {
            // Place first room randomly
            roomX = rand() % (maxWidth / tileSize - roomWidth);
            roomY = rand() % (maxHeight / tileSize - roomHeight);
        } else {
            // Place new room within maxDistance
            const Room& existingRoom = rooms[rand() % rooms.size()];
            roomX = std::max(existingRoom.x - maxDistance, 0) + rand() % (2 * maxDistance + 1);
            roomY = std::max(existingRoom.y - maxDistance, 0) + rand() % (2 * maxDistance + 1);

            roomX = std::min(roomX, (maxWidth / tileSize - roomWidth));
            roomY = std::min(roomY, (maxHeight / tileSize - roomHeight));
        }

        Room newRoom(roomX, roomY, roomWidth, roomHeight);

        bool overlaps;

        for (const Room& existingRoom : rooms) {
            overlaps = roomConstraintsOverlap(existingRoom, newRoom);
            if (overlaps) {
                break;
            }
        }

        // Check for overlaps with existing rooms
        if (!overlaps) {
            rooms.push_back(newRoom);
        }
    }
}

void generateCorridors(const std::vector<Room>& rooms, std::vector<Room>& corridors) {
    int minDistance = 20; // Minimum distance to connect rooms
    for (size_t i = 0; i < rooms.size(); i++) {
        for (size_t j = i + 1; j < rooms.size(); j++) {
            int deltaX, deltaY;

            // Calculate the horizontal (X) delta
            if (rooms[i].x > rooms[j].x + rooms[j].width) {
                // Room i is to the right of room j
                deltaX = -(rooms[i].x - (rooms[j].x + rooms[j].width));
            } else if (rooms[j].x > rooms[i].x + rooms[i].width) {
                // Room j is to the right of room i
                deltaX = rooms[j].x - (rooms[i].x + rooms[i].width);
            } else {
                // Rooms overlap in the X direction, set deltaX to 0
                deltaX = 0;
            }

            // Calculate the vertical (Y) delta
            if (rooms[i].y > rooms[j].y + rooms[j].height) {
                // Room i is below room j
                deltaY = -(rooms[i].y - (rooms[j].y + rooms[j].height));
            } else if (rooms[j].y > rooms[i].y + rooms[i].height) {
                // Room j is below room i
                deltaY = rooms[j].y - (rooms[i].y + rooms[i].height);
            } else {
                // Rooms overlap in the Y direction, set deltaY to 0
                deltaY = 0;
            }

            std::cout << "DeltaX: " << deltaX << ", DeltaY: " << deltaY << std::endl;

            // Check if rooms are close enough to connect or that rooms aren't already connected
            if (std::abs(deltaX) < minDistance && std::abs(deltaY) < minDistance) {
                // Calculate corridor dimensions in terms of tiles
                int corridorX, corridorY, corridorWidth, corridorHeight;
                bool vertical = false;

                if (std::abs(deltaX) > std::abs(deltaY)) {
                    // Horizontal corridor
                    corridorX = (deltaX > 0) ? rooms[i].x + rooms[i].width : rooms[j].x + rooms[j].width;
                    corridorY = rooms[i].y + rooms[i].height / 2 - 1;
                    corridorWidth = std::abs(deltaX);
                    corridorHeight = 1;
                } else {
                    // Vertical corridor
                    corridorX = rooms[i].x + rooms[i].width / 2 - 1;
                    corridorY = (deltaY > 0) ? rooms[i].y + rooms[i].height : rooms[j].y + rooms[j].height;
                    corridorWidth = 1;
                    corridorHeight = std::abs(deltaY);
                    vertical = true;
                }

                Room corridor(corridorX, corridorY, corridorWidth, corridorHeight);
                corridors.push_back(corridor);
            }
        }
    }
}


int main() {
    //srand(static_cast<unsigned>(time(0)));
    srand(5);

    sf::Vector2u windowSize(800u, 600u);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Dungeon");
    window.setFramerateLimit(60);

    std::vector<Room> rooms;
    std::vector<Room> corridors;

    int numRooms = 10;
    int maxWidth = 800;
    int maxHeight = 600;

    generateRooms(rooms, numRooms, maxWidth, maxHeight);
    generateCorridors(rooms, corridors);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Draw the corridors and rooms
        for (const Room& room : rooms) {
            for (int i = 0; i < room.width; ++i) {
                for (int j = 0; j < room.height; ++j) {
                    sf::RectangleShape tileShape(sf::Vector2f(tileSize, tileSize));
                    tileShape.setPosition(sf::Vector2f((room.x + i) * tileSize, (room.y + j) * tileSize));
                    tileShape.setFillColor(room.tileColors[i][j]);
                    window.draw(tileShape);
                }
            }
        }

        for (const Room& corridor : corridors) {
            for (int i = 0; i < corridor.width; ++i) {
                for (int j = 0; j < corridor.height; ++j) {
                    sf::RectangleShape tileShape(sf::Vector2f(tileSize, tileSize));
                    tileShape.setPosition(sf::Vector2f((corridor.x + i) * tileSize, (corridor.y + j) * tileSize));
                    tileShape.setFillColor(corridor.tileColors[i][j]);
                    window.draw(tileShape);
                }
            }
        }

        window.display();
    }

    return 0;
}
