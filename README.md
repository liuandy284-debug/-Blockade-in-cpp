# Snake

A classic Snake game for the Windows console, written in C++. It is a single source file with no third-party dependencies.

```
+-- Score: 5 ------------------------------------------------+
|                                                            |
|                  *                                         |
|                                                            |
|                         ooooo@                             |
|                         o                                  |
|                                                            |
+------------------------------------------------------------+
```

(Illustration only. The actual map is 28 rows × 60 columns.)

## Features

- Control with arrow keys or WASD
- Pressing the opposite direction by mistake won't make the snake turn back into itself
- Food only spawns on empty cells
- The snake speeds up as your score goes up
- The game ends when you hit a wall or yourself, and you can restart right away
- Fill the whole map to win
- Flicker-free rendering

## Controls

| Key | Action |
| --- | --- |
| `↑` `↓` `←` `→` or `W` `S` `A` `D` | Change direction |
| `R` | Play again after game over |
| `Esc` | Quit after game over |

## Symbols

| Symbol | Meaning |
| --- | --- |
| `@` | Snake head |
| `o` | Snake body |
| `*` | Food |

The current score is shown in the top border. Each piece of food is worth 1 point.

## Building and Running

You need **Windows** and a compiler that supports **C++11**. The game uses `<conio.h>` and `<windows.h>`, so it won't compile on Linux or macOS as is.

**MinGW / g++**

```bash
g++ -std=c++11 -O2 snake.cpp -o snake.exe
snake.exe
```

**Visual Studio (command line)**

```bash
cl /EHsc /utf-8 snake.cpp
snake.exe
```

The comments in the source file are in Chinese and saved as UTF-8. The `/utf-8` flag stops the encoding warnings.

**Visual Studio (IDE):** Create an empty console project, add `snake.cpp` to it, and press `Ctrl + F5` to run.

**Dev-C++:** Open `snake.cpp` and press `F11` to compile and run. If the compiler doesn't recognize `constexpr`, go to *Tools → Compiler Options* and add `-std=c++11`.

> The console window needs at least 62 columns × 30 rows, or the display will be garbled. The Windows default of 120 × 30 is enough.

## Rules

- The snake starts in the middle of the map, heading right
- Eating food makes the snake one segment longer and scores 1 point
- The snake starts at one step every 150 ms. Each point makes it 3 ms faster, down to a minimum of 60 ms per step
- Hitting a wall or your own body ends the game
- Moving the head into the cell the tail just left is allowed and doesn't count as hitting yourself

## Code Structure

All the code is in `snake.cpp`.

| Name | Purpose |
| --- | --- |
| `Map` | The map. Each cell is empty, food, snake body, or snake head |
| `Snake` | The snake. `snake[0]` is the head. Also stores the length and current direction |
| `initMap` / `initSnake` | Set up the map and the snake |
| `generateFood` | Places food on a random empty cell. Returns `false` if there are no empty cells left |
| `readDirection` | Reads keyboard input and returns the direction for the next step |
| `moveSnake` | Moves the snake one step. Returns `false` if it hits a wall or itself |
| `drawMap` | Draws a full frame |
| `showMessage` | Shows a line of text in the middle of the map |
| `main` | The outer loop runs one game after another. The inner loop is the game loop |

Each frame of the game loop does this:

```
wait → read input → move the snake → spawn new food if it was eaten → draw the frame
```

## Implementation Notes

**The snake is stored on the map too.** Every cell knows whether it holds part of the snake. That means checking for a collision with yourself only takes one cell lookup, with no need to walk the whole snake.

**The order of steps in a move matters.** `moveSnake` works in this order:

1. Work out the head's new position. If it's off the map, the snake hit a wall
2. Check whether there's food at the new position
3. If there's no food, clear the tail cell first
4. Then check whether the new position is part of the body
5. Move each segment forward one cell and put the head in its new position

Step 3 has to come before step 4. Otherwise a snake chasing its own tail would be wrongly counted as hitting itself.

**No turning back.** A new direction is checked against the direction the snake actually moved last step, not against the last key pressed. So even if you quickly press up and then left within one frame, the snake won't turn back into itself.

**No flicker.** Each frame is built as one string first. The cursor then goes back to the top-left corner and the whole frame is printed in one go, covering the previous one. It doesn't call `system("cls")` every frame.

**Food never lands on the snake.** The game counts the empty cells and then picks one of them at random. If there are no empty cells left, the snake has filled the map.

## Ideas for More Features

- [ ] Pause with the space bar
- [ ] Wrap-around mode: leave one side and come back in on the other
- [ ] Save the high score to a file
- [ ] Difficulty levels
- [ ] Obstacles on the map
