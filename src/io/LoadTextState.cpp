//
// Created By Andrew Boun on 4/29/2025
//

#include <io/TextState.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

void TextState::loadState(Dungeon &d){
    const char* home = std::getenv("HOME");
    std::ifstream file(std::string(home) + "/.rlg327/state.txt");
    if (!file.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    loadRooms(d, file);
    loadStairs(d, file); //up stairs and down stairs
    loadItems(d, file);                     
    loadNPCs(d, file);
    loadPC(d, file);
    loadNumMonsters(d, file);
    loadGrid(d, file);
    loadFog(d, file); // fog grid in isFog boolean

    file.close();
}

void TextState::loadRooms(Dungeon &d, std::ifstream &file){
    std::string line;
    while (std::getline(file, line)) {
        if (line == "ROOMS") break;
    }
    while (std::getline(file, line)){
        if (line == "END") break;
        if (line == "BEGIN ROOM"){
            std::string temp;
            int width = 0, height = 0, topLeftX = 0, topLeftY = 0;

            // width
            std::getline(file, line);
            std::stringstream ss1(line);
            ss1 >> temp >> width;

            // height
            std::getline(file, line);
            std::stringstream ss2(line);
            ss2 >> temp >> height;

            // topLeft
            std::getline(file, line);
            std::stringstream ss3(line);
            ss3 >> temp >> topLeftX >> topLeftY;

            // END ROOM
            std::getline(file, line);

            d.rooms.push_back(
                Room(
                    topLeftX, 
                    topLeftY,
                    width,
                    height
                )
            );
        }
    }
}

void TextState::loadStairs(Dungeon &d, std::ifstream &file){
    std::string line;
    // UPSTAIRS
    while (std::getline(file, line)) {
        if (line == "UPSTAIRS") break;
    }
    while (std::getline(file, line)) {
        if (line == "END") break;
        if (line == "BEGIN STAIR") {
            int x = 0, y = 0;
            std::getline(file, line); // location line
            std::stringstream ss(line);
            std::string temp;
            ss >> temp >> x >> y;
            Stair stair(x, y, '<');
            d.up_stairs.push_back(stair);
            std::getline(file, line); // END STAIR
        }
    }
    
    // DOWNSTAIRS
    while (std::getline(file, line)) {
        if (line == "DOWNSTAIRS") break;
    }
    while (std::getline(file, line)) {
        if (line == "END") break;
        if (line == "BEGIN STAIR") {
            int x = 0, y = 0;
            std::getline(file, line); // location line
            std::stringstream ss(line);
            std::string temp;
            ss >> temp >> x >> y;
            Stair stair(x, y, '>');
            d.down_stairs.push_back(stair);
            std::getline(file, line); // END STAIR
        }
    }
}

void TextState::loadItems(Dungeon &d, std::ifstream &file){
    std::string line;
    // Wait for "ITEMS"
    while (std::getline(file, line)) {
        if (line == "ITEMS") break;
    }
    while (std::getline(file, line)) {
        if (line == "END") break;
        if (line == "BEGIN ITEM") {
            int posX = 0, posY = 0, hit = 0, dodge = 0, def = 0, weight = 0, speed = 0, attr = 0, val = 0, rrty = 0;
            char symbol = ' ';
            int ID = 0, descID = 0, inInventory = 0, canBeGenerated = 0;
            std::string temp;

            // pos
            std::getline(file, line);
            std::stringstream ss1(line);
            ss1 >> temp >> posX >> posY;

            // hit
            std::getline(file, line);
            std::stringstream ss2(line);
            ss2 >> temp >> hit;

            // dodge
            std::getline(file, line);
            std::stringstream ss3(line);
            ss3 >> temp >> dodge;

            // def
            std::getline(file, line);
            std::stringstream ss4(line);
            ss4 >> temp >> def;

            // weight
            std::getline(file, line);
            std::stringstream ss5(line);
            ss5 >> temp >> weight;

            // speed
            std::getline(file, line);
            std::stringstream ss6(line);
            ss6 >> temp >> speed;

            // attr
            std::getline(file, line);
            std::stringstream ss7(line);
            ss7 >> temp >> attr;

            // val
            std::getline(file, line);
            std::stringstream ss8(line);
            ss8 >> temp >> val;

            // rrty
            std::getline(file, line);
            std::stringstream ss9(line);
            ss9 >> temp >> rrty;

            // symbol
            std::getline(file, line);
            std::stringstream ss10(line);
            ss10 >> temp >> symbol;

            // ID
            std::getline(file, line);
            std::stringstream ss11(line);
            ss11 >> temp >> ID;

            // descID
            std::getline(file, line);
            std::stringstream ss12(line);
            ss12 >> temp >> descID;

            // inInventory
            std::getline(file, line);
            std::stringstream ss13(line);
            ss13 >> temp >> inInventory;

            // canBeGenerated
            std::getline(file, line);
            std::stringstream ss14(line);
            ss14 >> temp >> canBeGenerated;

            // END ITEM
            std::getline(file, line);

            // Construct and add the item (adjust constructor as needed)
            Item *item = ItemDescription::createItem(d.itemDescList[descID], ID, descID);
            if (!canBeGenerated) {
                d.itemDescList[descID].canBeGenerated = false;
            }
            item->pos = Point(posX, posY);
            item->hit = hit;
            item->dodge = dodge;
            item->def = def;
            item->weight = weight;
            item->speed = speed;
            item->attr = attr;
            item->val = val;
            item->rrty = rrty;
            item->symbol = symbol;
            item->ID = ID;
            item->descID = descID;
            item->inInventory = inInventory;
            d.items.push_back(item);
                
        }
    }
}

void TextState::loadNPCs(Dungeon &d, std::ifstream &file){
    std::string line;
    // Wait for "NPCS"
    while (std::getline(file, line)) {
        if (line == "NPCS") break;
    }
    while (std::getline(file, line)) {
        if (line == "END") break;
        if (line == "BEGIN NPC") {
            int hp = 0, posX = 0, posY = 0, speed = 0, alive = 0, ID = 0, pcPosX = 0, pcPosY = 0, descID = 0, canBeGenerated = 0;
            char symbol = ' ';
            std::string temp;

            // hp
            std::getline(file, line);
            std::stringstream ss1(line);
            ss1 >> temp >> hp;

            // position
            std::getline(file, line);
            std::stringstream ss2(line);
            ss2 >> temp >> posX >> posY;

            // speed
            std::getline(file, line);
            std::stringstream ss3(line);
            ss3 >> temp >> speed;

            // symbol
            std::getline(file, line);
            std::stringstream ss4(line);
            ss4 >> temp >> symbol;

            // alive
            std::getline(file, line);
            std::stringstream ss5(line);
            ss5 >> temp >> alive;

            // ID
            std::getline(file, line);
            std::stringstream ss6(line);
            ss6 >> temp >> ID;

            // pcPosition
            std::getline(file, line);
            std::stringstream ss7(line);
            ss7 >> temp >> pcPosX >> pcPosY;

            // descID
            std::getline(file, line);
            std::stringstream ss8(line);
            ss8 >> temp >> descID;

            // canBeGenerated
            std::getline(file, line);
            std::stringstream ss9(line);
            ss9 >> temp >> canBeGenerated;

            // END NPC
            std::getline(file, line);

            // Construct and add the NPC (adjust constructor as needed)
            NPC *npc = NPCDescription::createNPC(d.npcDescList[descID], ID, descID);
            if (!canBeGenerated) {
                d.npcDescList[descID].canBeGenerated = false;
            }
            npc->hp = hp;
            npc->position = Point(posX, posY);
            npc->speed = speed;
            npc->symbol = symbol;
            npc->alive = alive;
            npc->ID = ID;
            npc->pcPosition = Point(pcPosX, pcPosY);
            npc->descID = descID;
            d.npcs.push_back(npc);
        }
    }
}

void TextState::loadPC(Dungeon &d, std::ifstream &file){
    std::string line;
    // Wait for "PC"
    while (std::getline(file, line)) {
        if (line == "PC") break;
    }

    PC pc;
    std::string temp;

    // hp
    std::getline(file, line);
    std::stringstream ss1(line);
    ss1 >> temp >> pc.hp;

    // position
    std::getline(file, line);
    std::stringstream ss2(line);
    int posX, posY;
    ss2 >> temp >> posX >> posY;
    pc.position = Point(posX, posY);

    // speed
    std::getline(file, line);
    std::stringstream ss3(line);
    ss3 >> temp >> pc.speed;

    // symbol
    std::getline(file, line);
    std::stringstream ss4(line);
    ss4 >> temp >> pc.symbol;

    // alive
    std::getline(file, line);
    std::stringstream ss5(line);
    ss5 >> temp >> pc.alive;

    // ID
    std::getline(file, line);
    std::stringstream ss6(line);
    ss6 >> temp >> pc.ID;

    // dice_dam
    std::getline(file, line);
    std::stringstream ss7(line);
    ss7 >> temp >> pc.dice_dam.base >> pc.dice_dam.numDice >> pc.dice_dam.numSides;

    // weapon_slot
    std::getline(file, line);
    std::stringstream ss8(line);
    int id;
    ss8 >> temp >> id;
    pc.weapon_slot = (id == -1) ? nullptr : d.items[id];

    // offhand_slot
    std::getline(file, line);
    std::stringstream ss9(line);
    ss9 >> temp >> id;
    pc.offhand_slot = (id == -1) ? nullptr : d.items[id];

    // range_slot
    std::getline(file, line);
    std::stringstream ss10(line);
    ss10 >> temp >> id;
    pc.range_slot = (id == -1) ? nullptr : d.items[id];

    // armor_slot
    std::getline(file, line);
    std::stringstream ss11(line);
    ss11 >> temp >> id;
    pc.armor_slot = (id == -1) ? nullptr : d.items[id];

    // helmet_slot
    std::getline(file, line);
    std::stringstream ss12(line);
    ss12 >> temp >> id;
    pc.helmet_slot = (id == -1) ? nullptr : d.items[id];

    // cloak_slot
    std::getline(file, line);
    std::stringstream ss13(line);
    ss13 >> temp >> id;
    pc.cloak_slot = (id == -1) ? nullptr : d.items[id];

    // gloves_slot
    std::getline(file, line);
    std::stringstream ss14(line);
    ss14 >> temp >> id;
    pc.gloves_slot = (id == -1) ? nullptr : d.items[id];

    // boots_slot
    std::getline(file, line);
    std::stringstream ss15(line);
    ss15 >> temp >> id;
    pc.boots_slot = (id == -1) ? nullptr : d.items[id];

    // amulet_slot
    std::getline(file, line);
    std::stringstream ss16(line);
    ss16 >> temp >> id;
    pc.amulet_slot = (id == -1) ? nullptr : d.items[id];

    // light_slot
    std::getline(file, line);
    std::stringstream ss17(line);
    ss17 >> temp >> id;
    pc.light_slot = (id == -1) ? nullptr : d.items[id];

    // ring_slot_1
    std::getline(file, line);
    std::stringstream ss18(line);
    ss18 >> temp >> id;
    pc.ring_slot_1 = (id == -1) ? nullptr : d.items[id];

    // ring_slot_2
    std::getline(file, line);
    std::stringstream ss19(line);
    ss19 >> temp >> id;
    pc.ring_slot_2 = (id == -1) ? nullptr : d.items[id];

    // damDices (array of dice: base numDice numSides ...)
    std::getline(file, line);
    std::stringstream ss20(line);
    ss20 >> temp;
    pc.damDices.clear();
    int base, numDice, numSides;
    while (ss20 >> base >> numDice >> numSides) {
        pc.damDices.push_back(Dice(base, numDice, numSides));
    }

    // items (array of item IDs)
    std::getline(file, line);
    std::stringstream ss21(line);
    ss21 >> temp;
    pc.items.clear();
    int itemID;
    while (ss21 >> itemID) {
        if (itemID != -1) {
            pc.items.push_back(d.items[itemID]);
        }
    }

    d.pc = pc; // Set the PC in the dungeon

    // END
    while (std::getline(file, line)) {
        if (line == "END") break;
    }
}

void TextState::loadNumMonsters(Dungeon &d, std::ifstream &file){
    std::string line;
    // Wait for "NUMMONSTERS"
    while (std::getline(file, line)) {
        if (line == "NUMMONSTERS") break;
    }
    // Read the number of monsters
    int numMonsters = 0;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        ss >> numMonsters;
    }
    d.numMonsterAlive = numMonsters; // or use a setter if available

    // Read until "END"
    while (std::getline(file, line)) {
        if (line == "END") break;
    }
}

void TextState::loadGrid(Dungeon &d, std::ifstream &file){
    std::string line;
    // Wait for "GRID"
    while (std::getline(file, line)) {
        if (line == "GRID") break;
    }

    int y = 0;
    while (std::getline(file, line)) {
        if (line == "END" || y >= DUNGEON_HEIGHT) break;
        std::stringstream ss(line);
        std::string token;
        int x = 0;
        while (ss >> token && x < DUNGEON_WIDTH) {
            char cellType = ' ';
            int hardness = 0;
            if (token == "X") {
                cellType = ' ';
                ss >> hardness;
            } else if (token == ".") {
                cellType = '.';
                ss >> hardness;
            } else if (token == "#") {
                cellType = '#';
                ss >> hardness;
            } else if (token == "<" || token == ">") {
                cellType = token[0];
            } else {
                continue;
            }
            d.grid[y][x] = Cell(hardness, cellType);
            x++;
        }
        y++;
    }
}

void TextState::loadFog(Dungeon &d, std::ifstream &file){
    std::string line;
    // Wait for "FOG"
    while (std::getline(file, line)) {
        if (line == "FOG") break;
    }

    int y = 0;
    while (std::getline(file, line)) {
        if (line == "END" || y >= DUNGEON_HEIGHT) break;
        std::stringstream ss(line);
        std::string token;
        int x = 0;
        while (ss >> token && x < DUNGEON_WIDTH) {
            char cellType = ' ';
            if (token == "X") {
                cellType = ' ';
            } else if (token == ".") {
                cellType = '.';
            } else if (token == "#") {
                cellType = '#';
            } else if (token == "<" || token == ">") {
                cellType = token[0];
            }
            d.fog[y][x] = Cell(0, cellType); // Hardness is always 0 for fog
            x++;
        }
        y++;
    }
}