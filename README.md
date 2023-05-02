# CPPND Capstone: Space Invaders
Space Invaders is a classic arcade game developed using SDL2 library in C++. The player controls a spaceship and must defeat waves of alien enemies. 

## Dependencies for Running Locally
* cmake >= 3.7
    * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
    * Linux: make is installed by default on most Linux distros
    * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
    * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. <br>
  >For MacOS, an 'Homebrew' can be used like `brew install SDL2 SDL2_image SDL2_ttf`
* gcc/g++ >= 5.4
    * Linux: gcc / g++ is installed by default on most Linux distros
    * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
    * Windows: recommend using [MinGW](http://www.mingw.org/)

## Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SpaceInvaders`.

## How to Play
- Use the arrow keys to move your spaceship left and right.
- Press the spacebar to shoot missiles at the aliens.
- Player has 3 lives by default, after defeating aliens wave - new wave will be spawned and aliens speed increased.
- The objective of the game is to achieve maximum score. 

## Classes
- **Game**: This class is responsible for initializing the game window and managing the game loop.
- **Controller**: This class is responsible for handling user input.
- **ScoreManager**: This class is responsible for managing the game's high score table.
- **HudManager**: This class is responsible for rendering the game's HUD.
- **Scene**: This class is the base class for all game scenes.
- **GameScene**: This class is responsible for managing the main game scene.
- **GameOverScene**: This class is responsible for managing the game over scene.
- **GameObject**: This class is the base class for all game objects.
- **Player**: This class is responsible for managing the player's spaceship.
- **Alien**: This class is responsible for managing the alien enemies.
- **Bullet**: This class is responsible for managing bullets.
- **Obstacle**: This class is responsible for managing the game's obstacles.
- **ScoreEntry**: This class is responsible for managing single score entry.

## Utilities:
- *cleanup.h*: This file contains methods for releasing resources acquired by SDL2
- *logger.h*: This file contains methods for logging internal SDL2 errors

## Rubric points addressed:
#todo:#