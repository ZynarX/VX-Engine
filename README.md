# VX-Engine

A simple console and SDL2 based game engine written in C++. 
Supports player movement, item pickup, monster AI, and turn-based combat

-------------------------------------------------------------------------

## OVERVIEW

This is a *fully functional console and SDL2 based game engine* that allows developers to:

 - Create games using `.vxed` files
 - Place entities like monsters, items, and traps
 - Implement player movement and interaction
 - Add inventory and combat systems

All built entirely with C++ using the SDL2 library

-------------------------------------------------------------------------

## FEATURES

| Feature | Description |
|---------|-------------|
| **Game Loading** | Loads game data from `.vxed` files |
| **Game Creation** | Allows users to create their own games and save it inside a `.vxed` file |
| **Player Movement** | WASD keys, bounds checking, wall collision |
| **Monster A.I.** | Enemies move towards the player intelligently |
| **Combat System** | Turn-based battle with HP tracking |
| **Item Pickup** | Collect items and track them in inventory |
| **Inventory System** | Shows collected items (e.g. "Bread x2", "Sword x1") |
| **Collision Detection** | Detects when the player hits walls, items, enemies, or traps |

-------------------------------------------------------------------------

## TECHNOLOGIES USED

 - **C++17 & SDL2**
 - **Standard Template Library (STL)**: `vector`, `map`, `string`, `cstring`, `ctype.h`, `fstream`, `iostream`, `SDL`
 - **Object-Oriented Programming (OOP)**: Structured around `Designer`, `Compiler`, `Game`, `Player`, `Entity`, `Item`, and `Trap` classes
 - **FileIO**: Load game data from a `.vxed` file
