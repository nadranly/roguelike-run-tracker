# Roguelike Run Tracker

A C++ console application where players create fantasy hero classes, run dungeon encounters, and track their progress over time.

## Why this project works for the rubric

This project includes:

- **Interactive input** through a menu-based system
- **File handling** to save and load character data
- **Class inheritance and polymorphism** using an abstract `Character` base class with derived `Assassin`, `Tank`, and `Mage` classes
- **Exception handling** through a custom `GameException` class
- **A clear GitHub-ready structure** with separate headers, source files, and data folder

## Features

- Create multiple characters
- Choose an active character
- Run a 3-room dungeon
- Use class-specific attacks and abilities
- Track wins, deaths, runs, and potions
- Save and load roster data from a file
- Remove characters from the roster

## Project Structure

```text
roguelike-run-tracker/
├── include/
│   ├── Assassin.h
│   ├── Character.h
│   ├── Enemy.h
│   ├── Game.h
│   ├── GameException.h
│   ├── InputHelper.h
│   ├── Mage.h
│   ├── SaveManager.h
│   └── Tank.h
├── src/
│   ├── Assassin.cpp
│   ├── Character.cpp
│   ├── Enemy.cpp
│   ├── Game.cpp
│   ├── Mage.cpp
│   ├── SaveManager.cpp
│   ├── Tank.cpp
│   └── main.cpp
├── data/
└── README.md
```

## How to Compile

### g++

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o roguelike_run_tracker
./roguelike_run_tracker
```

## Sample Save File Format

Each character is saved like this:

```text
Assassin|Niko|85|85|18|2|1|3|3
Tank|Rook|130|130|14|1|0|1|2
```