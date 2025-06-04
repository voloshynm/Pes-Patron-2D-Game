# Zombie Game (So_Long)

A classic 2D adventure game built with C and MinilibX, featuring maze exploration, collectible items, and strategic gameplay. This project implements fundamental game development concepts including sprite rendering, collision detection, and game state management.

![cub3D Demo](https://img.shields.io/badge/42-Project-brightgreen)
![Language](https://img.shields.io/badge/Language-C-darkgrey)
![Graphics](https://img.shields.io/badge/Graphics-MinilibX-orange)

## 🎮 Features

- **2D Top-down Perspective**: Classic arcade-style gameplay with pixel-perfect movement
- **Collectible System**: Gather all items to unlock the exit
- **Enemy AI**: Dynamic enemy movement patterns and collision detection
- **Multiple Maps**: Various levels with increasing difficulty
- **Sprite Animation**: Smooth character and object animations
- **Score System**: Track your progress and completion time
- **Cross-platform Compatibility**: Runs on Linux and macOS

## 🚀 Quick Start

### Prerequisites

- GCC compiler
- Make
- X11 development libraries (Linux)
- MinilibX library (automatically handled)

### Installation

1. **Clone the repository**:
```
git clone https://github.com/voloshynm/Pes-Patron-2D-Game.git
cd Pes-Patron-2D-Game
```

2. **Compile the project**:
```
make
```

3. **Run the game**:
```
./so_long maps/map1.ber
```

### Controls

| Key | Action |
|-----|--------|
| `W` or `↑` | Move up |
| `S` or `↓` | Move down |
| `A` or `←` | Move left |
| `D` or `→` | Move right |
| `ESC` | Exit game |

## 🗺️ Map Configuration

Maps are defined in `.ber` files with the following format:

```
1111111111111
1E0C00000C001
1010010100101
1P0011000C001
1111111111111
```

### Map Elements

**Characters**:
- `1` - Wall (impassable)
- `0` - Empty space (walkable)
- `P` - Player starting position
- `C` - Collectible item
- `E` - Exit (unlocked when all collectibles are gathered)

### Map Rules

- Map must be rectangular and surrounded by walls (`1`)
- Must contain exactly one player starting position (`P`)
- Must contain at least one collectible (`C`)
- Must contain exactly one exit (`E`)
- Must have a valid path from player to all collectibles and exit

## 🏗️ Project Structure

```
Pes-Patron-2D-Game/
├── src/                    # Source files
│   ├── main.c             # Program entry point
│   ├── game_init.c        # Game initialization
│   ├── map_parser.c       # Map file parsing and validation
│   ├── player_movement.c  # Player controls and movement
│   ├── collision.c        # Collision detection system
│   ├── collectibles.c     # Item collection logic
│   ├── enemy_ai.c         # Enemy behavior and AI
│   ├── graphics.c         # Sprite rendering and graphics
│   └── utils.c            # Utility functions
├── inc/
│   └── so_long.h          # Header file with structures and prototypes
├── sprites/               # Game sprites and textures
│   ├── player/           # Player character sprites
│   ├── enemies/          # Enemy sprites
│   ├── items/            # Collectible item sprites
│   ├── walls/            # Wall and environment textures
│   └── ui/               # UI elements
├── maps/                  # Example game maps
│   ├── map1.ber          # Basic tutorial level
│   ├── map2.ber          # Intermediate level
│   └── map3.ber          # Advanced level
├── Makefile              # Build configuration
└── README.md
```

## 🔧 Technical Implementation

### Game Engine Components

**Map Parser**: Validates and loads map configuration from `.ber` files
**Sprite System**: Handles loading and rendering of XPM sprite files
**Game Loop**: Manages frame updates, input handling, and rendering
**Collision Detection**: Prevents movement through walls and handles item collection
**State Management**: Tracks game progress, score, and win/lose conditions

### Key Features

**Memory Management**: Proper allocation and cleanup of all resources
**Error Handling**: Comprehensive validation of maps and game states
**Performance Optimization**: Efficient rendering and update cycles
**Modular Design**: Clean separation of concerns for easy maintenance

## 🛠️ Build System

### Available Commands

```
make          # Compile the project
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild everything
make bonus    # Compile bonus features (if available)
```

### Dependencies

The project handles dependencies automatically:
- **MinilibX**: Graphics library for rendering
- **Custom utilities**: Built-in helper functions

## 🧪 Testing

Test the game with provided maps:

```
# Basic level
./so_long maps/map1.ber

# Test error handling
./so_long maps/invalid_map.ber
./so_long nonexistent.ber
```

### Map Validation

The game validates maps for:
- Proper rectangular shape
- Wall boundaries
- Valid character placement
- Reachable paths to all collectibles

## 🐛 Troubleshooting

### Common Issues

**Game won't start**:
- Check map file format and validity
- Ensure sprite files exist in the sprites directory
- Verify file permissions

**Compilation errors**:
- Install required development libraries
- Check GCC version compatibility
- Ensure MinilibX is properly installed

**Graphics issues**:
- Verify XPM sprite file format
- Check display environment variables
- Ensure X11 forwarding (if using SSH)

### Debug Mode

Compile with debug symbols:
```
make CFLAGS="-Wall -Wextra -Werror -g"
gdb ./so_long maps/map1.ber
```

## 🎯 Game Objectives

1. **Collect All Items**: Gather every collectible (`C`) on the map
2. **Reach the Exit**: Navigate to the exit (`E`) after collecting all items
3. **Avoid Enemies**: Stay away from moving enemies (bonus feature)
4. **Minimize Moves**: Complete levels with the fewest possible moves

## 📈 Scoring System

- **Movement Points**: Each move costs 1 point
- **Collection Bonus**: Bonus points for collecting items
- **Time Bonus**: Faster completion yields higher scores
- **Perfect Run**: Complete without unnecessary movements

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is part of the 42 School curriculum. Feel free to use it for educational purposes.

## 👥 Authors

**Maksym Voloshyn** - [GitHub Profile](https://github.com/voloshynm)

## 🙏 Acknowledgments

- 42 School for the project specification and learning environment
- MinilibX developers for the graphics library
- Classic arcade games for inspiration
- The game development community for resources and tutorials

## 📚 Learning Resources

- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Game Development Patterns](https://gameprogrammingpatterns.com/)
- [2D Game Development Tutorials](https://lazyfoo.net/tutorials/SDL/)

*Made with ❤️ at 42 School*

---

**Keywords**: `c-programming` `game-development` `2d-game` `minilibx` `42-school` `arcade-game` `sprite-rendering` `collision-detection`
