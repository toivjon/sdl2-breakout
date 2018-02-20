# sdl2-breakout
A SDL2 implementation of the classic Breakout game.

Contains game modes for a one and two player games.

Development blog entry: https://toivjon.wordpress.com/2017/07/19/sdl2-breakout/

## Scenes
Game is split into following scenes:
1. A welcome scene, which contains the main menu.
2. A court scene, which contains the actual gameplay.

The implementation only contains the following scene transition:
* 1 to 2, when the game is started by selecting the number of players.

## Features
This Breakout implementation contains the following features.
* A support for a one or two player (turn-based) games.
* Each player has three balls.
* Each round lasts until the ball reaches the bottom of the screen or until the court's last brick is being destroyed.
* The game ends after the last ball is missed.
* The end of the game starts the ending animation.
* The color of the destroyed brick (yellow, green, orange and red) defines the amount of points the player receives.
* Ball movement speed increases after the first hit with any orange brick.
* Ball movement speed increases after the first hit with any red brick.
* Ball movement speed increases after the first four hits with the paddle or walls.
* Ball movement speed increases after the first 12 hits with the paddle or walls.
* Active player score digits are blinked after the player receives points.
* Active player index is blinked if the player index is being changed (in two player games only).
* Supports the hidden extra level like the one in the original game. See ball.cpp comment lines 143-149 for more details.

## External Dependencies
This implementation has external dependencies on the following libraries:
* SDL2
* SDL2_ttf
* libfreetype-6.dll
* zlib1.dll

## Compilation
Easiest way to compile the code is to use the [CMake](https://cmake.org/) utility.

Required tools and libraries for the compilation:
1. [CMake](https://cmake.org/) (ver. >=3.7.2)
2. [SDL2](https://www.libsdl.org/download-2.0.php) (ver. >=2.0.5)
3. [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) (ver. >=2.0.14)
4. A compilation toolkit supported by the CMake utility (e.g. Visual Studio).

CMake compilation uses Find*-modules from the /cmake folder which specify where CMake looks for the required libraries.

Without any modifications, CMake will make use the following environment variable paths.
* SDL2DIR, which should point to the root directory of the SDL2 library.
* SDL2TTFDIR, which should point to the root directory of the SDL2_ttf library.

## Screenshots
![alt text](https://github.com/toivjon/sdl2-breakout/blob/master/screenshots/welcome-scene.png "WelcomeScene")
![alt text](https://github.com/toivjon/sdl2-breakout/blob/master/screenshots/court-scene.png "CourtScene")
