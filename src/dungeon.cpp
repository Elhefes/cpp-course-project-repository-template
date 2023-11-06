#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

const int tileSize = 10;

sf::Color getRandomColor() {
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}

class Room {
public:
    int x, y, width, height;

    std::vector<std::vector<sf::Color>> tileColors;

    Room(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
        tileColors.resize(width, std::vector<sf::Color>(height));
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                tileColors[i][j] = getRandomColor();
            }
        }
    }
};

class Corridor {
public:
    int x, y, width, height;

    std::vector<std::vector<sf::Color>> tileColors;

    Corridor(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
        tileColors.resize(width, std::vector<sf::Color>(height));
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                tileColors[i][j] = getRandomColor();
            }
        }
    }
};

void generateRooms(std::vector<Room>& rooms, int numRooms, int maxWidth, int maxHeight) {
    int maxDistance = 25;
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

        // Check for overlaps with existing rooms
        bool overlaps = false;
        for (const Room& existingRoom : rooms) {
            if (newRoom.x * tileSize < existingRoom.x  * tileSize + existingRoom.width * tileSize &&
                newRoom.x * tileSize + newRoom.width * tileSize > existingRoom.x * tileSize &&
                newRoom.y * tileSize < existingRoom.y * tileSize + existingRoom.height * tileSize &&
                newRoom.y * tileSize + newRoom.height * tileSize > existingRoom.y * tileSize) {
                overlaps = true;
                break;
            }
        }

        if (!overlaps) {
            rooms.push_back(newRoom);
        }
    }
}

void generateCorridors(const std::vector<Room>& rooms, std::vector<Corridor>& corridors) {
    int maxLength = 25;
    for (size_t i = 0; i < rooms.size(); i++) {
        for (size_t j = i + 1; j < rooms.size(); j++) {
            // Calculate corridor dimensions in terms of tiles
            int corridorX, corridorY, corridorWidth, corridorHeight;
            bool vertical = false;

            if (rooms[i].x + rooms[i].width < rooms[j].x) {
                corridorX = rooms[i].x + rooms[i].width;
                corridorY = rooms[i].y + rooms[i].height / 2 - 1;
                corridorWidth = rooms[j].x - (rooms[i].x + rooms[i].width);
                if (corridorWidth > maxLength) {
                    continue;
                }
                corridorHeight = 1;
                vertical = true;
            } else if (rooms[i].x > rooms[j].x + rooms[j].width) {
                corridorX = rooms[j].x + rooms[j].width;
                corridorY = rooms[i].y + rooms[i].height / 2 - 1;
                corridorWidth = rooms[i].x - (rooms[j].x + rooms[j].width);
                corridorWidth = std::max(corridorWidth, 1);
                if (corridorWidth > maxLength) {
                    continue;
                }
                corridorHeight = 1;
                vertical = true;
            } else if (rooms[i].y + rooms[i].height < rooms[j].y) {
                corridorX = rooms[i].x + rooms[i].width / 2 - 1;
                corridorY = rooms[i].y + rooms[i].height;
                corridorWidth = 1;
                corridorHeight = rooms[j].y - (rooms[i].y + rooms[i].height);
                if (corridorHeight > maxLength) {
                    continue;
                }
            } else {
                corridorX = rooms[i].x + rooms[i].width / 2 - 1;
                corridorY = rooms[j].y + rooms[j].height;
                corridorWidth = 1;
                corridorHeight = rooms[i].y - (rooms[j].y + rooms[j].height);
                if (corridorHeight > maxLength) {
                    continue;
                }
            }

            Corridor corridor(corridorX, corridorY, corridorWidth, corridorHeight);
            corridors.push_back(corridor);
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    sf::Vector2u windowSize(800u, 600u);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Dungeon");
    window.setFramerateLimit(60);

    std::vector<Room> rooms;
    std::vector<Corridor> corridors;
    std::vector<Corridor> c;
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

        // Rooms
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


        // Corridors
        for (const Corridor& corridor : corridors) {
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



/*

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Room {
public:
    float x, y, width, height;

    Room(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
};

class Corridor {
public:
    float x, y, width, height;

    Corridor(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
};

void generateRooms(std::vector<Room>& rooms, int numRooms, float maxWidth, float maxHeight) {
    while (rooms.size() < numRooms) {
        float roomWidth = 100 + rand() % 200;
        float roomHeight = 100 + rand() % 200;
        float roomX = rand() % static_cast<int>(maxWidth - roomWidth);
        float roomY = rand() % static_cast<int>(maxHeight - roomHeight);
        Room newRoom(roomX, roomY, roomWidth, roomHeight);

        // Check for overlaps with existing rooms
        bool overlaps = false;
        for (const Room& existingRoom : rooms) {
            if (newRoom.x < existingRoom.x + existingRoom.width &&
                newRoom.x + newRoom.width > existingRoom.x &&
                newRoom.y < existingRoom.y + existingRoom.height &&
                newRoom.y + newRoom.height > existingRoom.y) {
                overlaps = true;
                break;
            }
        }

        if (!overlaps) {
            rooms.push_back(newRoom);
        }
    }
}

void generateCorridors(const std::vector<Room>& rooms, std::vector<Corridor>& corridors, std::vector<Corridor>& c) {
    for (size_t i = 0; i < rooms.size(); i++) {
        for (size_t j = i + 1; j < rooms.size(); j++) {
            // Calculate corridor dimensions
            float corridorX, corridorY, corridorWidth, corridorHeight;
            bool vertical = false;

            if (rooms[i].x + rooms[i].width < rooms[j].x) {
                corridorX = rooms[i].x + rooms[i].width;
                corridorY = rooms[i].y + rooms[i].height / 2.0f - 5;
                corridorWidth = rooms[j].x - (rooms[i].x + rooms[i].width);
                corridorHeight = 10;
                vertical = true;
            } else if (rooms[i].x > rooms[j].x + rooms[j].width) {
                corridorX = rooms[j].x + rooms[j].width;
                corridorY = rooms[i].y + rooms[i].height / 2.0f - 5;
                corridorWidth = rooms[i].x - (rooms[j].x + rooms[j].width);
                corridorHeight = 10;
                vertical = true;
            } else if (rooms[i].y + rooms[i].height < rooms[j].y) {
                corridorX = rooms[i].x + rooms[i].width / 2.0f - 5;
                corridorY = rooms[i].y + rooms[i].height;
                corridorWidth = 10;
                corridorHeight = rooms[j].y - (rooms[i].y + rooms[i].height);
            } else {
                corridorX = rooms[i].x + rooms[i].width / 2.0f - 5;
                corridorY = rooms[j].y + rooms[j].height;
                corridorWidth = 10;
                corridorHeight = rooms[i].y - (rooms[j].y + rooms[j].height);
            }

            Corridor corridor(corridorX, corridorY, corridorWidth, corridorHeight);
            corridors.push_back(corridor);

            if (vertical) {
                if (rooms[i].y + rooms[i].height < rooms[j].y) {
                    float corridorX2 = corridorX; // Start from the same X
                    float corridorY2 = corridorY + corridorHeight;
                    float corridorWidth2 = 10;
                    float corridorHeight2 = rooms[j].y - (corridorY + corridorHeight);

                    Corridor newCorridor(corridorX2, corridorY2, corridorWidth2, corridorHeight2);
                    c.push_back(newCorridor);
                } else if (rooms[i].y > rooms[j].y + rooms[i].height) {
                    float corridorX2 = corridorX; // Start from the same X
                    float corridorY2 = rooms[j].y + rooms[j].height;
                    float corridorWidth2 = 10;
                    float corridorHeight2 = rooms[i].y - (corridorY + corridorHeight);

                    Corridor newCorridor(corridorX2, corridorY2, corridorWidth2, corridorHeight2);
                    c.push_back(newCorridor);
                }
            } else {
                if (rooms[i].x + rooms[i].width < rooms[j].x) {
                    float corridorX2 = corridorX + corridorWidth;
                    float corridorY2 = corridorY; // Start from the same Y
                    float corridorWidth2 = rooms[j].x - (corridorX + corridorWidth);
                    float corridorHeight2 = 10;

                    Corridor newCorridor(corridorX2, corridorY2, corridorWidth2, corridorHeight2);
                    c.push_back(newCorridor);
                } else if (rooms[i].x > rooms[j].x + rooms[j].width) {
                    float corridorX2 = rooms[j].x + rooms[j].width;
                    float corridorY2 = corridorY; // Start from the same Y
                    float corridorWidth2 = rooms[i].x - (corridorX + corridorWidth);
                    float corridorHeight2 = 10;

                    Corridor newCorridor(corridorX2, corridorY2, corridorWidth2, corridorHeight2);
                    c.push_back(newCorridor);
                }
            }
        }
    }
}



int main() {
    srand(static_cast<unsigned>(time(0)));

    sf::Vector2u windowSize(1920u, 1080u);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Dungeon");
    window.setFramerateLimit(60);

    std::vector<Room> rooms;
    std::vector<Corridor> corridors;
    std::vector<Corridor> c;
    int numRooms = 10;
    float maxWidth = 1920.0f;
    float maxHeight = 1080.0f;

    generateRooms(rooms, numRooms, maxWidth, maxHeight);
    generateCorridors(rooms, corridors, c);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Draw the corridors and rooms
    
        // Rooms
        for (const Room& room : rooms) {
            sf::RectangleShape roomShape(sf::Vector2f(room.width, room.height));
            roomShape.setPosition(sf::Vector2f(room.x, room.y));
            roomShape.setFillColor(sf::Color::White);
            window.draw(roomShape);
        }

        // Corridors
        for (const Corridor& corridor : corridors) {
            sf::RectangleShape corridorShape(sf::Vector2f(corridor.width, corridor.height));
            corridorShape.setPosition(sf::Vector2f(corridor.x, corridor.y));
            corridorShape.setFillColor(sf::Color::Green);
            window.draw(corridorShape);
        }

        for (const Corridor& corridor : c) {
            sf::RectangleShape corridorShape(sf::Vector2f(corridor.width, corridor.height));
            corridorShape.setPosition(sf::Vector2f(corridor.x, corridor.y));
            corridorShape.setFillColor(sf::Color::Blue);
            window.draw(corridorShape);
        }

        window.display();
    }

    return 0;
}
*/
/*
#include <iostream>
#include <SFML/Graphics.hpp>

class Room {
public:
    Room(float x, float y, float size) {
        roomShape.setSize(sf::Vector2f(size, size));
        roomShape.setPosition(sf::Vector2f(x, y));
        roomShape.setFillColor(sf::Color::White);  // Customize the color as needed
    }

    void draw(sf::RenderWindow& window) {
        window.draw(roomShape);
    }

private:
    sf::RectangleShape roomShape;
};




int main() {
    sf::Vector2u windowSize(800u, 600u);
    sf::RenderWindow window(sf::VideoMode(windowSize), "Dungeon");
    window.setFramerateLimit(60);

    // Create Wall objects
    Room room1(100, 100, 50);  // Example coordinates and size

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Draw the walls
        room1.draw(window);

        window.display();
    }

    return 0;
}
*/