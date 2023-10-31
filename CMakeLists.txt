cmake_minimum_required(VERSION 3.11.0)
project(DungeonCrawler VERSION 0.1.0)

file(GLOB SRC
    "src/*.hpp"
    "src/*.cpp"
)

add_executable(DungeonCrawler ${SRC})