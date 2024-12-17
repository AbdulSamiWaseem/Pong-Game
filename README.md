# Pong Multithreaded Linux C++ Game

## Overview

With the help of cutting-edge OS ideas, I created the ground-breaking Pong Multithreaded Linux Game in C++, which transforms the traditional Pong game. This project demonstrates how well independent threads for paddle and ball control can be integrated, and it also features sensitive paddle movements and real-time scoring updates. It is a complex teaching tool for multithreading comprehension in addition to providing an engaging game experience.

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
