cmake_minimum_required(VERSION 3.11.0)
project(DungeonCrawler VERSION 0.1.0)

# Define the source files in your project (you can add more source files as needed)
file(GLOB SRC
        "src/*.hpp"
        "src/*.cpp"
        "src/Creature/*.hpp"
        "src/Creature/*.cpp"
)

set(SFML_STATIC_LIBRARIES TRUE)
# Create a subdirectory for the SFML submodule
add_subdirectory(libs/sfml)

# Link your project with the SFML libraries
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-system sfml-window)