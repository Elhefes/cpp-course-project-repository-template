cmake_minimum_required(VERSION 3.11.0)
project(DungeonCrawler VERSION 0.1.0)

file(GLOB SRC
    "src/*.hpp"
    "src/*.cpp"
)
## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "libs/SFML-2.6.0/lib/cmake/SFML")

find_package(SFML 2.6.0 COMPONENTS graphics audio REQUIRED)
add_executable(DungeonCrawler ${SRC})
target_link_libraries(DungeonCrawler sfml-graphics sfml-audio)
