# Tetris 🟦

This is a simple Tetris clone written in C using the SDL2 framework. The project is compiled and ready to use as is for Windows, though can be recompiled to run on Linux operating systems ( first replace the sdl files with their Linux alternatives, then recomplie. Make sure to use the 32bit dev versions of [SDL2](https://github.com/libsdl-org/SDL/releases), [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/releases), [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases)).

## Controls 🕹️

| Key         | Action                         |
| ----------- | ------------------------------ |
| Esc         | Open main menu                 |
| P           | Toggle pause                   |
| G           | Change grid style              |
| C           | Toggle random tetromino colors |
| Space       | Hard drop tetromino            |
| Down arrow  | Soft drop tetromino            |
| Up arrow    | Rotate tetromino               |
| Left arrow  | Move tetromino left            |
| Right arrow | Move tetromino right           |

## Scoring 🏆

The scoring system implemented in the project is [the same one used in the original Nintendo version for NES](https://tetris.fandom.com/wiki/Scoring), where points are calculated based on the number of lines cleared and the current level.

![Game footage](/assets/footage.gif)

_Happy coding!_ 🚀
