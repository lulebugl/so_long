# So_long

A 2D adventure game built with MinilibX where players navigate through custom maps, collecting sheep while avoiding obstacles and enemies.

## Overview

In So_long, you control a character through various terrain types, including grass and water. Your mission is to collect all sheep and reach the exit while avoiding hazards like water and hostile goblins.

![Example map](assets/readme/example.gif)

## Features

- Animated collectibles
- Auto-tiling system for natural-looking terrain
- Flood-filling algorithm to test if the game is playable
- Breadth-first-search algorithm to place ennemy in real-time

## Installation

1. Clone the repository
```bash
git clone --recurse-submodules https://github.com/lulebugl/so_long
cd so_long       # Move to the project directory
make             # Compile mandatory
make bonus       # Compiling bonus
```

2. Compile the game:
```bash
make        # Regular version
make bonus  # Enhanced version with enemies and animations
```

## Usage

```bash
./so_long [map_file].ber
./so_long_bonus [map_file].ber
```

### Controls

- Movement: WASD or Arrow Keys
- Pause: E
- Quit: ESC

### Game Elements

- Player: Your character
- Sheep: Collectibles required to complete levels
- Water: Deadly terrain
- Goblins: Hostile enemies that explode on contact
- Trees/Walls: Obstacles
- Exit: Level completion point (requires all sheep)

### Map Format

Maps must be rectangular `.ber` files using these characters:
- `0`: Empty space
- `1`: Wall/Tree
- `C`: Collectible (sheep)
- `E`: Exit
- `P`: Player starting position

Example map:
```
1111111111
1P000000C1
1000011001
1C00000001
1111111E11
```

## Resources

### Asset Tools
- [Tiny Swords Assets](https://pixelfrog-assets.itch.io/tiny-swords) - Game sprites and textures

## Credits
- Project structure inspired by [Alienxbe/SoLong](https://github.com/Alienxbe/SoLong/tree/main)
- Assets from [Pixel Frog](https://pixelfrog-assets.itch.io/tiny-swords)
- MinilibX provided by 42 School

---
Made with by [llebugle] at 19 School.
