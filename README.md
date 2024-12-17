# Pong Multithreaded Linux C++ Game

## Overview

Welcome to the Pong Multithreaded Linux C++ Game, an exciting project that brings the classic Pong game to life using advanced OS concepts. This game features two paddles and a ball, each controlled by separate threads, utilizing Linux system calls and SDL2 for graphics. Two human players can control the paddles, and the game includes a scoring system with real-time updates.
This project serves as an educational tool to understand the practical application of OS concepts in game development, offering both a fun gameplay experience and a robust learning platform.

## Key Features

**Multithreading:**
   - Separate threads for ball and paddle control, showcasing advanced OS concepts.

**Graphics:**
   - Utilizes SDL2 and SDL_ttf for rendering graphics and text.

**Real-time Interaction:**
   - Two-player control with responsive paddle movements.

**Scoring System:**
   - Real-time score updates for a competitive gaming experience.

## Controls
**Player 1:** Use `W` to move up and `S` to move down.

**Player 2:** Use the `UP` and `DOWN` arrow keys to move.

## How to Play

1. Install dependencies:
   ```sh
   Ensure you have SDL2 and SDL_ttf installed. On Ubuntu, you can install them using:
   sudo apt-get install libsdl2-dev libsdl2-ttf-dev

2. Compile the code:
   ```sh
   g++ -o pong main.cpp -lSDL2 -lSDL2_ttf -lpthread

3. Run the game executable:
   ```sh
   ./pong

Now, by following these steps in order, you can successfully set up and enjoy the Linux based PONG Game on your machine. Happy gaming!

## Contributors

- Husnain Ali (https://github.com/M-Husnain-Ali)

## Contact Information

For inquiries or support, please contact the project maintainers:

- m.husnainali.work@gmail.com

---
Enjoy playing and exploring the implementation of multithreading and some other advanced OS concepts in this classic Pong game!
