# Dungeon_crawler_antti_karvanen_3 

# Group
- Matias Veikkola 
- Henri Palin 
- Lauri Palin 
- Daniil Parniukov 

This software is a basic dungeon crawler video game. It’s programmed in C++ and uses SFML to draw the game. 

Before the game starts, the software runs a series of tests which test the basic functionality of dungeon generation, creature creation and inventory handling. After all of the tests pass, the actual game starts. 

The software uses SFML to draw a window and loads all used texture files from a set directory. A randomly generated dungeon is then created, consisting of rooms and corridors that connect them. The rooms’ floors have a random distribution of different textures and the corridors have their own textures as well. 

The player is spawned in the first room and its inventory is created. Currently it consists of a sword and collectible potions. The player can move with keyboard input, attack with mouse clicks and equip the sword or the potion(s) with key binds to their respective numbers to use them. Potions have a chance to spawn randomly in each room and they can be picked up and added to the inventory. Using potions restores health. 

A single basic enemy is also spawned to the first room, and the player needs to kill the enemy to gain access to the corridor. Killing all of the enemies in each room is the basic game loop. 

The enemies can attack the player. If the player is hit, their health gets lower. If their health reaches zero, the game is lost. In this scenario, a losing screen is shown and there is a “Play again” button. 

Clearing rooms of enemies becomes consecutively harder as there are more and more enemies to fight as the player progresses.

Finally, the last room contains only one enemy, the boss. The boss is much stronger than basic enemies and has its own texture. Killing the boss is the game’s winning condition, where a congratulatory screen is shown. There is a “Play again” button. 

The build instructions can be found in Readme.md file in the build/ folder.
