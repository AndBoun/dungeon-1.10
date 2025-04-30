# How To Run The Project:

 Create a `.rlg327` folder in your home directory and move the `monster_desc.txt` and `object_desc.txt` file into it:
```bash
mkdir ~/.rlg327
```

> [!NOTE]
> You must have these files in your `.rlg327` folder. All files within the `.rlg327` folder are from Iowa State University's professor, Jeremy Scheaffer, except the `state.txt` file thats created by me. The included `.rlg327` provides all you need, including `state.txt` to run the program


Build the project:
```bash
make
```


> [!Note]
> The project includes a `.devcontainer` folder, that provides the intended development environment for the program. It uses a `Dockerfile` with the latest stable Fedora version with gcc/g++, gdb, and ncurses. This emulates Iowa State University's Pyrite server environment.

## Running configurations

Run the project:
```bash
./dungeon --load --save --nummon <number>
```


# Main Files:
```plain
/
├── include/
│   └── io/
│       └── TextState.hpp
├── src/
│   └── io/
│       ├── LoadTextState.cpp
│       └── SaveTextState.cpp
└── main.cpp
```

# About the Project:
The project introduces saving and loading with text files. This allows you to save a state while playing the game and instantly revert to it. You do this in gameplay, not with flags before running the program (like in previous assignments, although these still work).

## Constraints:
- All files and inputs are assumed to be valid

## Additional Notes
- Loading and Saving depend you maintaining the same `object_desc.txt` and  `monster_desc.txt` files in the `rlg327` folder.
- The loading and saving should maintain everything, but the priority queue state.
- Press `[` to save the current state in your turn.
- Press `]` to revert back to your saved state. This assumes you have a valid state saved in `state.txt`.

## How the Project Runs:
In `main.cpp`, it creates a dungeon instance, `start_gameplay()` in `Dungeon.cpp`.  This will then ask for user input in `ui.cpp`, this is where you can save and load a state in `LoadTextState.cpp` and `SaveTextState.cpp`. When you press `]` to load a state, it returns `-4` all the way back into `start_gampeplay()` and `main.cpp`, where is will reset the dungeon and load the `state.txt` with `LoadTextState.cpp`


# `State.txt` Configurations
See the included `state.txt` file in the `.rlg327` folder for a full representation.

### Rooms
`topLeft`is a `Point(x, y)`
```
ROOMS
BEGIN ROOM
width 5
height 4
topLeft 29 14
END ROOM
END
```

### Items
```
ITEMS
BEGIN ITEM
pos 55 7
hit 100
dodge 55
def 100
weight 1000
speed 10
attr 10
val 19900
rrty 50
symbol |
ID 0
descID 14
inInventory 0
canBeGenerated 1
END ITEM
END
```

### NPC
```
NPCS
BEGIN NPC
hp 22
position 53 9
speed 10
symbol G
alive 1
ID 0
pcPosition 0 0
descID 11
canBeGenerated 1
END NPC
END
```

### PC
Where  equipment slots take an `int` that indexes the Item from the Dungeon. 'damDices' dices has sets of three ints, representing all three dice attributes. `items` take a list of `ints` that indexes items from the Dungeon
```
PC
hp 100
position 37 11
speed 10
symbol @
alive 1
ID 0
dice_dam 2 3 4
weapon_slot -1
offhand_slot -1
range_slot -1
armor_slot -1
helmet_slot -1
cloak_slot -1
gloves_slot -1
boots_slot -1
amulet_slot -1
light_slot -1
ring_slot_1 -1
ring_slot_2 -1
damDices 1 10 12 40 30 12
items 0 5 8
END
```

### NumMonsters
```
NUMMONSTERS
10
END
```


### Grid
Format is : `<char> <hardness>`, where `X` represent a space character
```
GRID
X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 255 X 
END
```

### Fog
This only holds character, where `X` represents a space character
```
FOG
X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X . . . . . X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X 
X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X . . . . . X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X 
X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X . . . . . 
END
```


# Example Gameplay:
![gameplay](https://github.com/user-attachments/assets/7d647fca-6523-4d89-9ae7-e633a4b40434)
