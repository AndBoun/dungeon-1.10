# How To Run The Project:

 Create a `.rlg327` folder in your home directory and move the `monster_desc.txt` and `object_desc.txt` file into it:
```bash
mkdir ~/.rlg327
```

Build the project:
```bash
make
```

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

## Constraints:
- All files and inputs are assumed to be valid

## Additional Notes
- Loading and Saving depend you maintaining the same `object_desc.txt` and  `monster_desc.txt` files in the `rlg327` folder.
- Press `[` to save the current state in your turn.
- Press `]` to revert back to your saved state. This assumes you have a valid state saved in `state.txt`.

## How the Project Runs:
In `main.cpp`, it creates a dungeon instance, `start_gameplay()` in `Dungeon.cpp`.  This will then ask for user input in `ui.cpp`, this is where you can save and load state in `LoadTextState.cpp` and `SaveTextState.cpp`. When you press `]` to load a state, it return `-4` all the way back into `start_gampeplay()` and `main.cpp`, where is will reset the dungeon and load the `state.txt` with `LoadTextState.cpp`


# `State.txt` Configurations
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