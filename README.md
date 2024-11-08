# So_long 🎮

A 2D game project developed as part of the 42 School curriculum where players must collect items and find the exit while avoiding obstacles.

## Ideas and To do


### Core Mechanics (Estimated: 14-16 hours)

- [ ] backtracking for invalid map
  - Path validation algorithm
  - Error handling and messaging
  - Edge case testing
- [ ] Steps tracking (4h)
  - Display counter on screen
  - Update with each valid move
- [ ] add collectibles (3h)
  - Implement collection mechanism
  - Track collected items
  - Victory condition check

### Animations (Estimated: 8 hours)

- [ ] animate character (4h)
  - Walking animation
  - Idle animation
  - Direction changes
- [ ] animate tree	(3h)
- [ ] animate water (2h)

### Advanced Features (Estimated: 8-10 hours)

- [ ] backtracking for quickest exit?
- [ ] add ennemies
  - Enemy movement patterns
  - Collision with player
  - Game over conditions
- [ ] key to show quickest exit?
- [ ] make obstacle water when at the edge of map when possible (not fullscreen)


## Table of Contents
- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Controls](#controls)
- [Implementation Details](#implementation-details)
- [Project Structure](#project-structure)
- [Custom Features](#custom-features)
- [Resources](#resources)
- [Credits](#credits)

## Description
So_long is a simple 2D game using the MinilibX graphics library. The player navigates through a map, collecting items while trying to reach the exit in the minimum number of moves possible.

## Installation
```bash
# Clone the repository
git clone https://github.com/yourusername/so_long.git

# Navigate to the project directory
cd so_long

# Compile the game
make

# Run the game with a map file
./so_long maps/map1.ber
```

## Controls
- `W` or `↑`: Move up
- `S` or `↓`: Move down
- `A` or `←`: Move left
- `D` or `→`: Move right
- `ESC`: Exit game

## Project Structure
```
so_long/
├── src/
│   ├── main.c
│   ├── map_parser.c
│   ├── graphics.c
│   └── game_logic.c
├── includes/
│   └── so_long.h
├── assets/
│   └── sprites/
├── maps/
└── Makefile
```

<!-- ## Custom Features
### Dynamic Water Surrounding
- Automatically adds water tiles around the map when screen resolution permits
- Creates a more visually appealing environment
- Prevents empty screen space -->

## Resources

### Development Tools
- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Official documentation
- [Comprehensive Guide to So_long](https://reactive.so/post/42-a-comprehensive-guide-to-so_long/) - Detailed tutorial
- [Sprite Animation Tutorial](https://pulgamecanica.herokuapp.com/posts/mlx-animations) - Guide for implementing animations

### Asset Tools
- [Tiny Swords Assets](https://pixelfrog-assets.itch.io/tiny-swords) - Game sprites and textures

## Credits
- Project structure inspired by []()
- Assets from [Pixel Frog](https://pixelfrog-assets.itch.io/tiny-swords)
- MinilibX provided by 42 School

<!-- ## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. -->

---
Made with by [llebugle] at 42 School