# Amazed

Amazed is a maze-solving project written in C during our first year at EPITECH. It includes a main program that parses a maze description, initializes robots, and calculates their movements to solve the maze. Additionally, a bonus graphical version is provided, which visualizes the maze and robot movements using the CSFML library.

## Table of contents
    
- [Amazed](#amazed)
  - [Table of contents](#table-of-contents)
  - [Contributors](#contributors)
  - [Features](#features)
  - [Compilation](#compilation)
  - [Usage](#usage)
  - [Requirements](#requirements)
  - [Disclaimer](#disclaimer)

---

## Contributors
- [Léo Batillot](https://github.com/Leo-Batilliot)
- [Gabin Wilson](https://github.com/Gabin-Wilson)
- [Théophile Riffé](https://github.com/inkurey-22)

---

## Features

- **Maze Parsing**: Parses maze descriptions from standard input.
- **Robot Initialization**: Initializes robots and assigns them starting positions.
- **Pathfinding**: Implements algorithms to find the best paths for robots to traverse the maze.
- **Error Handling**: Validates maze structure and ensures solvability.
- **Graphical Visualization (Bonus)**: Displays the maze and robot movements using CSFML.

---

## Compilation

To compile the project, nothing simpler:
```bash
make
```
If you want to compile the graphical bonus:
```bash
make bonus
```
---

## Usage

There a different way to use the program.
First, you will need to create the maze.

To do so, launch the generator.
```bash
./labygen.pl [nb_rooms] [density] [nb_robots] > maze.txt
```
Then you can launch the programm :
```bash
./amazed < maze.txt
```

Alternatively, you can shortcut this by launching the program directly with the maze generator

```bash
./labygen.pl [nb_rooms] [density] [nb_robots] | ./amazed
```
---

## Requirements

There are a few requirements for this project to be compiled and ran.

First, you need to be on Linux.
Then you will need to following packages:
```
gcc (compiler)
perl (maze generator)
make (build tool)
CSFML library (for the graphical bonus)
```
---

## Disclaimer
Amazed is a project developed for educational purposes and is not affiliated with or endorsed by any entity mentioned.