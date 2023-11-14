#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "room.cpp"

const int TILE_SIZE = 10;

class Dungeon {
public:
    Dungeon() {
        
    }
    bool roomConstraintsOverlap(Room existingRoom, Room newRoom) {
        return (newRoom.x * TILE_SIZE < existingRoom.x  * TILE_SIZE + existingRoom.width * TILE_SIZE &&
                newRoom.x * TILE_SIZE + newRoom.width * TILE_SIZE > existingRoom.x * TILE_SIZE &&
                newRoom.y * TILE_SIZE < existingRoom.y * TILE_SIZE + existingRoom.height * TILE_SIZE &&
                newRoom.y * TILE_SIZE + newRoom.height * TILE_SIZE > existingRoom.y * TILE_SIZE);
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
                roomX = rand() % (maxWidth / TILE_SIZE - roomWidth);
                roomY = rand() % (maxHeight / TILE_SIZE - roomHeight);
            } else {
                // Place new room within maxDistance
                const Room& existingRoom = rooms[rand() % rooms.size()];
                roomX = std::max(existingRoom.x - maxDistance, 0) + rand() % (2 * maxDistance + 1);
                roomY = std::max(existingRoom.y - maxDistance, 0) + rand() % (2 * maxDistance + 1);

                roomX = std::min(roomX, (maxWidth / TILE_SIZE - roomWidth));
                roomY = std::min(roomY, (maxHeight / TILE_SIZE - roomHeight));
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

                //std::cout << "DeltaX: " << deltaX << ", DeltaY: " << deltaY << std::endl;

                // Check if rooms are close enough to connect or that rooms aren't already connected
                if (std::abs(deltaX) < minDistance && std::abs(deltaY) < minDistance) {
                    // Calculate corridor dimensions in terms of tiles
                    int corridorX, corridorY, corridorWidth, corridorHeight;
                    bool vertical = true;

                    if (std::abs(deltaX) > std::abs(deltaY)) {
                        // Vertical corridor
                        corridorX = (deltaX > 0) ? rooms[i].x + rooms[i].width : rooms[j].x + rooms[j].width;
                        corridorY = rooms[i].y + rooms[i].height / 2 - 1;
                        corridorWidth = std::abs(deltaX);
                        corridorHeight = 1;
                    } else {
                        // Horizontal corridor
                        corridorX = rooms[i].x + rooms[i].width / 2 - 1;
                        corridorY = (deltaY > 0) ? rooms[i].y + rooms[i].height : rooms[j].y + rooms[j].height;
                        corridorWidth = 1;
                        corridorHeight = std::abs(deltaY);
                        vertical = false;
                    }

                    Room corridor(corridorX, corridorY, corridorWidth, corridorHeight);
                    corridors.push_back(corridor);

                    // Calculate distance to the nearest wall of the connected room
                    const Room& connectedRoom = rooms[j];
                    int distanceToWall = vertical ? connectedRoom.x - corridorX :
                                                    connectedRoom.y - corridorY ;

                    std::cout << "Distance to wall: " << distanceToWall << std::endl;

                    if (abs(distanceToWall) > 0) {
                        // Adjust the corridor dimensions to connect to the wall

                        if (vertical) {
                            corridorX = (deltaX > 0) ? corridorX - corridorWidth : corridorX + corridorWidth; 
                        } else {
                            corridorY = (deltaY > 0) ? corridorY - corridorHeight : corridorY + corridorHeight;
                        }

                        corridorWidth = vertical ? abs(distanceToWall) : 1;
                        corridorHeight = vertical ? 1 : abs(distanceToWall);

                        if (distanceToWall < 0 && vertical) {
                            corridorX -= corridorWidth;
                        } else if (distanceToWall < 0 && !(vertical)) {
                            corridorY -= corridorHeight;
                        }

                        Room additionalCorridor(corridorX, corridorY, corridorWidth, corridorHeight);
                        corridors.push_back(additionalCorridor);
                    }        
                }
            }
        }
    }
};