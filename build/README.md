# How to build and run the game

## Prerequisites
Before building this project SFML needs to be added as a submodule with the following command
```
git submodule update --init --recursive --remote
```
SFML also needs some dependencies for it to compile. Download the required dependencies with the following apt-get command
```
sudo apt-get install libgl1-mesa-dev libfreetype6-dev libopenal-dev libjpeg-dev libpng-dev libtiff5-dev libflac-dev libvorbis-dev libsfml-dev libudev-dev
```
If you encounter problems with running the get command there are two additional commands you can try
```
sudo hwclock --hctosys
```
and
```
sudo apt install pkg-config
```
Now try running the initial apt-get command again

## Build and run the game
In this (/build) folder, run the following commands to build the application
```
cmake ..
make
```
Then, you can run the application using
```
./DungeonCrawler
```
To save time, you can run all of the commands in a row
```
cmake .. && make && ./DungeonCrawler
```