# Basic Tetris

A simple terminal-based Tetris game implemented in C.

## Description

This is a basic implementation of the classic Tetris game that runs in the terminal. The game features 7 different block types (Tetrominos) that players can place on a customizable grid. Complete rows to score points and try to beat your high score!

## Features

- 7 different Tetromino shapes
- Block rotation capability
- Customizable game board dimensions
- Score tracking with high score memory
- Terminal-based ASCII graphics
- Simple and intuitive controls

## Requirements

- C compiler (GCC, Clang, or similar)
- Standard C library
- Unix-like environment (macOS, Linux) or Windows with appropriate compiler

## Compilation

To compile the game, use the following command:

```bash
gcc BasicTetris.c -o game
```

Or with optimization flags:

```bash
gcc -O2 BasicTetris.c -o game
```

## How to Play

1. Run the compiled executable:
   ```bash
   ./game
   ```

2. Follow the on-screen menu to start the game:
   - Press `1` to start a new game
   - Press `0` to quit

3. Enter the desired board dimensions:
   - **Rows**: Number of rows for the game board (recommended: 10-20)
   - **Columns**: Number of columns for the game board (recommended: 8-15)

## Controls

- **Type a number (1 to N)**: Place the current block at column position
- **Type -1**: Rotate the current block 90 degrees clockwise
- **Type 0**: Return to main menu

## Game Rules

- Blocks fall from the top and are placed in the selected column
- Complete a full row to clear it and earn points
- Each cleared row awards points equal to the number of columns
- The game ends when blocks reach the top row
- Try to achieve the highest score possible!

## Block Types

The game includes 7 different Tetromino shapes:
- Z-shaped block
- I-shaped blocks (various sizes)
- L-shaped block
- Square block
- T-shaped variations

## Scoring

- Points are awarded for each completed row
- Score = Number of columns × Number of rows cleared
- High score is saved during the current session

## Project Structure

```
.
├── BasicTetris.c      # Main game source code
├── game               # Compiled executable (after compilation)
├── .gitignore         # Git ignore file
└── README.md          # This file
```

## License

This project is open source and available for educational purposes.

## Author

Created as a learning project for C programming.

## Future Improvements

Potential enhancements for future versions:
- Add difficulty levels with increasing speed
- Implement persistent high score storage
- Add color support with ncurses
- Create more sophisticated graphics
- Add sound effects
- Implement gravity (automatic block falling)
