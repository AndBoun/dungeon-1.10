//
// Created By Andrew Boun on 4/29/2025
//

#include <io/TextState.hpp>
#include <iostream>

void TextState::saveState(Dungeon &d){
    const char* home = std::getenv("HOME");
    std::ofstream file(std::string(home) + "/.rlg327/state.txt");
    if (!file.is_open()){
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    saveRooms(d, file);
    saveStairs(d, file); //up stairs and down stairs
    saveItems(d, file);                     
    saveNPCs(d, file);
    savePC(d, file);
    saveNumMonsters(d, file);
    saveGrid(d, file);
    saveFog(d, file); // fog grid in isFog boolean

    file.close();
}

void TextState::saveNPCs(Dungeon &d, std::ofstream &file){
    file << "NPCS" << std::endl;
    for (auto npc : d.getNPCs()){
        file << "BEGIN NPC" << std::endl;
        file << "hp " << npc->hp << std::endl;
        file << "position " << npc->position.getX() << " " << npc->position.getY() << std::endl;
        file << "speed " << npc->speed << std::endl;
        file << "symbol " << npc->symbol << std::endl;
        file << "alive " << npc->alive << std::endl;
        file << "ID " << npc->ID << std::endl;
        // file << "dice_dam " << npc->dice_dam.base << " " << npc->dice_dam.numDice << " " << npc->dice_dam.numSides << std::endl;
        // file << "intelligent " << npc->intelligent << std::endl;
        // file << "telepathy " << npc->telepathy << std::endl;
        // file << "tunneling " << npc->tunneling << std::endl;
        // file << "erratic " << npc->erratic << std::endl;
        // file << "passive " << npc->passive << std::endl;
        // file << "pickUp " << npc->pickUp << std::endl;
        // file << "destroy " << npc->destroy << std::endl;
        // file << "unique " << npc->unique << std::endl;
        // file << "boss " << npc->boss << std::endl;
        file << "pcPosition " << npc->pcPosition.getX() << " " << npc->pcPosition.getY() << std::endl;
        file << "descID " << npc->descID << std::endl;
        file << "canBeGenerated " << d.npcDescList[npc->descID].canBeGenerated << std::endl;
        // file << "name " << npc->name << std::endl;
        // file << "desc " << npc->desc << std::endl;
        // file << "color ";
        // for (auto color : npc->color){
        //     file << color << " ";
        // }
        // file << "rrty " << npc->rrty << std::endl;
        file << "END NPC" << std::endl;
    }
    file << "END" << std::endl;
    file << std::endl;
}

void TextState::saveItems(Dungeon &d, std::ofstream &file){
    file << "ITEMS" << std::endl;
    for (auto item : d.items){
        file << "BEGIN ITEM" << std::endl;
        file << "pos " << item->pos.getX() << " " << item->pos.getY() << std::endl;
        // file << "name " << item->name << std::endl;
        // file << "desc " << item->desc << std::endl;
        // file << "type " << item->type << std::endl;
        // file << "color " << item->color << std::endl;
        file << "hit " << item->hit << std::endl;
        // file << "dice_dam " << item->dice_dam.base << " " << item->dice_dam.numDice << " " << item->dice_dam.numSides << std::endl;
        file << "dodge " << item->dodge << std::endl;
        file << "def " << item->def << std::endl;
        file << "weight " << item->weight << std::endl;
        file << "speed " << item->speed << std::endl;
        file << "attr " << item->attr << std::endl;
        file << "val " << item->val << std::endl;
        // file << "art " << item->art << std::endl;
        file << "rrty " << item->rrty << std::endl;
        file << "symbol " << item->symbol << std::endl;
        file << "ID " << item->ID << std::endl;
        file << "descID " << item->descID << std::endl;
        file << "inInventory " << item->inInventory << std::endl;
        file << "canBeGenerated " << d.itemDescList[item->descID].canBeGenerated << std::endl;
        file << "END ITEM" << std::endl;
    }
    file << "END" << std::endl;
    file << std::endl;
}

void TextState::saveGrid(Dungeon &d, std::ofstream &file){
    file << "GRID" << std::endl;
    for (int i = 0; i < DUNGEON_HEIGHT; i++){
        for (int j = 0; j < DUNGEON_WIDTH; j++){
            char cell = d.grid[i][j].getType();
            if (d.grid[i][j].getType() == ' ') cell = 'X';
            file << cell << " " << d.grid[i][j].getHardness() << " ";
        }
        file << std::endl;
    }
    file << "END" << std::endl;
}

void TextState::saveFog(Dungeon &d, std::ofstream &file){
    file << "FOG" << std::endl;
    for (int i = 0; i < DUNGEON_HEIGHT; i++){
        for (int j = 0; j < DUNGEON_WIDTH; j++){
            char cell = d.fog[i][j].getType();
            if (d.fog[i][j].getType() == ' ') cell = 'X';
            file << cell << " ";
        }
        file << std::endl;
    }
    file << "END" << std::endl;
    file << std::endl;

}

void TextState::saveRooms(Dungeon &d, std::ofstream &file){
    file << "ROOMS" << std::endl;
    for (auto room : d.rooms){
        file << "BEGIN ROOM" << std::endl;
        file << "width " << room.getWidth() << std::endl;
        file << "height " << room.getHeight() << std::endl;
        file << "topLeft " << room.getTopLeft().getX() << " " << room.getTopLeft().getY() << std::endl;
        file << "END ROOM" << std::endl;
    }
    file << "END" << std::endl;
    file << std::endl;

}

void TextState::saveStairs(Dungeon &d, std::ofstream &file){
    file << "UPSTAIRS" << std::endl;
    for (auto stair : d.up_stairs){
        file << "BEGIN STAIR" << std::endl;
        file << "location " << stair.getX() << " " << stair.getY() << std::endl;
        file << "END STAIR" << std::endl;
    }
    file << "END" << std::endl;
    file << std::endl;


    file << "DOWNSTAIRS" << std::endl;
    for (auto stair : d.down_stairs){
        file << "BEGIN STAIR" << std::endl;
        file << "location " << stair.getX() << " " << stair.getY() << std::endl;
        file << "END STAIR" << std::endl;
    }
    file << "END" << std::endl;
    file << std::endl;

}

void TextState::savePC(Dungeon &d, std::ofstream &file){
    PC pc = d.getPC();
    file << "PC" << std::endl;
    file << "hp " << pc.hp << std::endl;
    file << "position " << pc.position.getX() << " " << pc.position.getY() << std::endl;
    file << "speed " << pc.speed << std::endl;
    file << "symbol " << pc.symbol << std::endl;
    file << "alive " << pc.alive << std::endl;
    file << "ID " << pc.ID << std::endl;
    file << "dice_dam " << pc.dice_dam.base << " " << pc.dice_dam.numDice << " " << pc.dice_dam.numSides << std::endl;
    file << "weapon_slot " << (pc.weapon_slot ? pc.weapon_slot->ID : -1) << std::endl;
    file << "offhand_slot " << (pc.offhand_slot ? pc.offhand_slot->ID : -1) << std::endl;
    file << "range_slot " << (pc.range_slot ? pc.range_slot->ID : -1) << std::endl;
    file << "armor_slot " << (pc.armor_slot ? pc.armor_slot->ID : -1) << std::endl;
    file << "helmet_slot " << (pc.helmet_slot ? pc.helmet_slot->ID : -1) << std::endl;
    file << "cloak_slot " << (pc.cloak_slot ? pc.cloak_slot->ID : -1) << std::endl;
    file << "gloves_slot " << (pc.gloves_slot ? pc.gloves_slot->ID : -1) << std::endl;
    file << "boots_slot " << (pc.boots_slot ? pc.boots_slot->ID : -1) << std::endl;
    file << "amulet_slot " << (pc.amulet_slot ? pc.amulet_slot->ID : -1) << std::endl;
    file << "light_slot " << (pc.light_slot ? pc.light_slot->ID : -1) << std::endl;
    file << "ring_slot_1 " << (pc.ring_slot_1 ? pc.ring_slot_1->ID : -1) << std::endl;
    file << "ring_slot_2 " << (pc.ring_slot_2 ? pc.ring_slot_2->ID : -1) << std::endl;
    file << "damDices ";
    for (auto dice : pc.damDices){
        file << dice.base << " " << dice.numDice << " " << dice.numSides << " ";
    }
    file << std::endl;
    file << "items ";
    for (auto item : pc.items){
        file << item->ID << " ";
    }
    file << std::endl;
    file << "END" << std::endl;
    file << std::endl;
}

void TextState::saveNumMonsters(Dungeon &d, std::ofstream &file){
    file << "NUMMONSTERS" << std::endl;
    file << d.getNumMonsters() << std::endl;
    file << "END" << std::endl;
    file << std::endl;
}
