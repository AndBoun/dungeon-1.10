//
// Created By Andrew Boun on 4/22/2025
//

#include <ui/ui.hpp>

void ui::inspect_item(Dungeon &d)
{

    Item *item = get_item_from_inventory(d);

    if (item == nullptr)
    {
        return;
    }

    Dice dice = item->dice_dam;

    std::vector<std::string> display_list = {
        "Name: " + item->name,
        "Type: " + item->type,
        "Symbol: " + std::string(1, item->symbol),
        "Hit: " + std::to_string(item->hit),
        "Damage: " + std::to_string(dice.base) + "+" + std::to_string(dice.numDice) + "d" + std::to_string(dice.numSides),
        "Dodge: " + std::to_string(item->dodge),
        "Defense: " + std::to_string(item->def),
        "Weight: " + std::to_string(item->weight),
        "Speed: " + std::to_string(item->speed),
        "Attribute: " + std::to_string(item->attr),
        "Value: " + std::to_string(item->val),
        "Art: " + std::to_string(item->art),
        "Rarity: " + std::to_string(item->rrty),
        "" // Empty line for spacing
    };

    // Process description text into lines
    std::string desc = item->desc;
    std::string current_line;
    for (size_t i = 0; i < desc.length(); i++)
    {
        if (current_line.length() >= 78 || desc[i] == '\n')
        {
            display_list.push_back(current_line);
            current_line.clear();
        }
        else
        {
            current_line += desc[i];
        }
    }

    int scroll = 0;
    clear();
    render_top_bar(COLOR_PLAYER_ID, "In Item Inspection Mode, press 'q' or ESC to exit");
    render_scrollable_list(2, 24, scroll, display_list);
    while (true)
    {
        timeout(-1);
        int input = getch();

        if (input == KEY_UP)
        {
            scroll = render_scrollable_list(2, 24, --scroll, display_list);
        }
        else if (input == KEY_DOWN)
        {
            scroll = render_scrollable_list(2, 24, ++scroll, display_list);
        }

        if (input == 'q' || input == 27 || input == 'I')
        {
            // Clear the screen and return to the main menu
            clear();
            render_grid_default(d);

            render_top_bar(COLOR_SUCCESS_ID, "Exited item inspection mode");
            break;
        }

        quit_game(d, input);
    }

    return;
}

void ui::expunge_item(Dungeon &d){
    render_top_bar(COLOR_PLAYER_ID, "Expunge");
    Item *item = get_item_from_inventory(d);
    if (item == nullptr){ return; }


    item->inInventory = false;
    item->pos = Point(-1, -1);

    int id = item->ID;
    
    // Remove item from inventory, let destructor handle deletion
    for (size_t i = 0; i < d.getPC().items.size(); i++){
        if (d.pc.items[i]->ID == id){
            d.getPC().items.erase(d.getPC().items.begin() + i);
            break;
        }
    }

    clear_top_bar(false);
    clear_bar(1, false);
    render_grid_default(d);
}

void ui::drop_item(Dungeon &d){
    render_top_bar(COLOR_PLAYER_ID, "Drop");
    Item *item = get_item_from_inventory(d);
    if (item == nullptr){ return; }

    item->inInventory = false;
    item->pos = d.getPC().getPosition();
    

    for (size_t i = 0; i < d.getPC().items.size(); i++){
        if (d.pc.items[i]->ID == item->ID){
            d.getPC().items.erase(d.getPC().items.begin() + i);
            break;
        }
    }

    

    clear_top_bar();
    render_grid_default(d);
}

void ui::wear_item(Dungeon &d) {
    render_top_bar(COLOR_PLAYER_ID, "Wear");
    Item *item = get_item_from_inventory(d);
    if (item == nullptr){ return; }

    int inventory_id = 0; //get inventory id of item
    for (size_t i = 0; i < d.getPC().items.size(); i++){
        if (d.pc.items[i]->ID == item->ID){
            inventory_id = i;
            break;
        }
    }

    Item *temp_item = nullptr;
    if (item->type == WEAPON) {
        temp_item = d.getPC().weapon_slot;
        d.getPC().weapon_slot = item;
    } else if (item->type == OFFHAND) {
        temp_item = d.getPC().offhand_slot;
        d.getPC().offhand_slot = item;
    } else if (item->type == RANGED) {
        temp_item = d.getPC().range_slot;
        d.getPC().range_slot = item;
    } else if (item->type == ARMOR) {
        temp_item = d.getPC().armor_slot;
        d.getPC().armor_slot = item;
    } else if (item->type == HELMET) {
        temp_item = d.getPC().helmet_slot;
        d.getPC().helmet_slot = item;
    } else if (item->type == CLOAK) {
        temp_item = d.getPC().cloak_slot;
        d.getPC().cloak_slot = item;
    } else if (item->type == GLOVES) {
        temp_item = d.getPC().gloves_slot;
        d.getPC().gloves_slot = item;
    } else if (item->type == BOOTS) {
        temp_item = d.getPC().boots_slot;
        d.getPC().boots_slot = item;
    } else if (item->type == AMULET) {
        temp_item = d.getPC().amulet_slot;
        d.getPC().amulet_slot = item;
    } else if (item->type == LIGHT) {
        temp_item = d.getPC().light_slot;
        d.getPC().light_slot = item;
    } else if (item->type == RING) {
        // Prefer first empty slot, or swap with ring_slot_1 if both filled
        if (d.getPC().ring_slot_1 == nullptr) {
            temp_item = nullptr;
            d.getPC().ring_slot_1 = item;
        } else if (d.getPC().ring_slot_2 == nullptr) {
            temp_item = nullptr;
            d.getPC().ring_slot_2 = item;
        } else {
            temp_item = d.getPC().ring_slot_1;
            d.getPC().ring_slot_1 = item;
        }
    }

    // Remove item from inventory and add swapped item back if needed
    d.getPC().items.erase(d.getPC().items.begin() + inventory_id);
    if (temp_item != nullptr) {
        d.getPC().items.push_back(temp_item);
    }
    d.pc.updatePCAttributes();

    clear_top_bar();
    render_grid_default(d);
}

void ui::take_off_item(Dungeon &d){
    render_top_bar(COLOR_PLAYER_ID, "Take Off");
    Item *item = get_item_from_equipment(d);
    if (item == nullptr){ return; }

    d.pc.items.push_back(item);

    if (item->type == WEAPON) {
        d.getPC().weapon_slot = nullptr;
    } else if (item->type == OFFHAND) {
        d.getPC().offhand_slot = nullptr;
    } else if (item->type == RANGED) {
        d.getPC().range_slot = nullptr;
    } else if (item->type == ARMOR) {
        d.getPC().armor_slot = nullptr;
    } else if (item->type == HELMET) {
        d.getPC().helmet_slot = nullptr;
    } else if (item->type == CLOAK) {
        d.getPC().cloak_slot = nullptr;
    } else if (item->type == GLOVES) {
        d.getPC().gloves_slot = nullptr;
    } else if (item->type == BOOTS) {
        d.getPC().boots_slot = nullptr;
    } else if (item->type == AMULET) {
        d.getPC().amulet_slot = nullptr;
    } else if (item->type == LIGHT) {
        d.getPC().light_slot = nullptr;
    } else if (item->type == RING) {
        // Remove from both ring slots if present
        if (d.getPC().ring_slot_1 != nullptr && d.getPC().ring_slot_1->ID == item->ID) {
            d.getPC().ring_slot_1 = nullptr;
        } else if (d.getPC().ring_slot_2 != nullptr && d.getPC().ring_slot_2->ID == item->ID) {
            d.getPC().ring_slot_2 = nullptr;
        }
    }

    d.pc.updatePCAttributes();

    clear_top_bar();
    render_grid_default(d);
}