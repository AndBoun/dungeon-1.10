//
// Created By Andrew Boun on 4/16/2025
//

#include <dungeon/Dungeon.hpp>
#include <ui/ui.hpp>

bool Dungeon::pickUpItem(PC &character){

    int itemID = getItemID(character.getPosition());

    if (itemID == -1) {
        return false; // No item at the character's position
    }

    if (character.symbol == PLAYER){

        if (!addToEquipment(character, itemID) && character.items.size() < 10) {
            character.items.push_back(items[itemID]);
        }
        else {
            return false; // Inventory is full
        }

        items[itemID]->pos = Point(-1, -1); // Remove item from the dungeon
        items[itemID]->inInventory = true; // Mark item as in inventory 
    
        if (items[itemID]->art) {
            itemDescList[items[itemID]->descID].canBeGenerated = false;
        }
    
        ui::render_top_bar(
            COLOR_SUCCESS_ID,
            "Picked up a %s: %c",
            items[itemID]->type.c_str(),
            items[itemID]->symbol
        );
    }
    

    return true;
}

bool Dungeon::addToEquipment(PC &character, int itemID){
    if (character.symbol != PLAYER) return false;

    std::string type = items[itemID]->type;

    if (type == WEAPON && pc.weapon_slot == nullptr) {
        character.weapon_slot = items[itemID];
    }
    else if (type == OFFHAND && pc.offhand_slot == nullptr) {
        character.offhand_slot = items[itemID];
    }
    else if (type == RANGED && pc.range_slot == nullptr) {
        character.range_slot = items[itemID];
    }
    else if (type == ARMOR && pc.armor_slot == nullptr) {
        character.armor_slot = items[itemID];
    }
    else if (type == HELMET && pc.helmet_slot == nullptr) {
        character.helmet_slot = items[itemID];
    }
    else if (type == CLOAK && pc.cloak_slot == nullptr) {
        character.cloak_slot = items[itemID];
    }
    else if (type == GLOVES && pc.gloves_slot == nullptr) {
        character.gloves_slot = items[itemID];
    }
    else if (type == BOOTS && pc.boots_slot == nullptr) {
        character.boots_slot = items[itemID];
    }
    else if (type == AMULET && pc.amulet_slot == nullptr) {
        character.amulet_slot = items[itemID];
    }
    else if (type == LIGHT && pc.light_slot == nullptr) {
        character.light_slot = items[itemID];
    }
    else if (type == RING) {
        if (!character.ring_slot_1) {
            character.ring_slot_1 = items[itemID];
        }
        else if (!character.ring_slot_2) {
            character.ring_slot_2 = items[itemID];
        }
        else {
            return false; // No available ring slots
        }
    } 
    else {
        return false;
    }

    items[itemID]->inInventory = true; // Mark item as in inventory
    items[itemID]->pos = Point(-1, -1); // Remove item from the dungeon
    character.updatePCAttributes();

    ui::render_top_bar(
        COLOR_SUCCESS_ID,
        "Picked up a %s: %c",
        items[itemID]->type.c_str(),
        items[itemID]->symbol
    );
    return true;
}