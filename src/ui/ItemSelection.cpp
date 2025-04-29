//
// Created By Andrew Boun on 4/22/2025
//

#include <ui/ui.hpp>

Item *ui::get_item_from_equipment(Dungeon &d)
{
    for (int line = 1; line < 24; line++){
        move(line, 0);
        clrtoeol();
    }

    render_centered_line(1, COLOR_DEFAULT_ID, "Select an item (a-l) or press 'q' or ESC to cancel");

    render_centered_line(
        12, 
        COLOR_DEFAULT_ID, 
        "%c  %c  %c  %c  %c  %c  %c  %c  %c  %c  %c  %c",
        d.pc.weapon_slot ? d.pc.weapon_slot->symbol : ' ',
        d.pc.offhand_slot ? d.pc.offhand_slot->symbol : ' ',
        d.pc.range_slot ? d.pc.range_slot->symbol : ' ',
        d.pc.armor_slot ? d.pc.armor_slot->symbol : ' ',
        d.pc.helmet_slot ? d.pc.helmet_slot->symbol : ' ',
        d.pc.cloak_slot ? d.pc.cloak_slot->symbol : ' ',
        d.pc.gloves_slot ? d.pc.gloves_slot->symbol : ' ',
        d.pc.boots_slot ? d.pc.boots_slot->symbol : ' ',
        d.pc.amulet_slot ? d.pc.amulet_slot->symbol : ' ',
        d.pc.light_slot ? d.pc.light_slot->symbol : ' ',
        d.pc.ring_slot_1 ? d.pc.ring_slot_1->symbol : ' ',
        d.pc.ring_slot_2 ? d.pc.ring_slot_2->symbol : ' '
    );
    render_centered_line(13, COLOR_DEFAULT_ID, "a  b  c  d  e  f  g  h  i  j  k  l");

    bool isValidInput = false;

    int input;
    Item *item;
    while (!isValidInput)
    {
        timeout(-1);
        input = getch();

        quit_game(d, input);

        switch (input)
        {
        case 'a':
            item = d.pc.weapon_slot;
            isValidInput = true;
            break;
        case 'b':
            item = d.pc.offhand_slot;
            isValidInput = true;
            break;
        case 'c':
            item = d.pc.range_slot;
            isValidInput = true;
            break;
        case 'd':
            item = d.pc.armor_slot;
            isValidInput = true;
            break;
        case 'e':
            item = d.pc.helmet_slot;
            isValidInput = true;
            break;
        case 'f':
            item = d.pc.cloak_slot;
            isValidInput = true;
            break;
        case 'g':
            item = d.pc.gloves_slot;
            isValidInput = true;
            break;
        case 'h':
            item = d.pc.boots_slot;
            isValidInput = true;
            break;
        case 'i':
            item = d.pc.amulet_slot;
            isValidInput = true;
            break;
        case 'j':
            item = d.pc.light_slot;
            isValidInput = true;
            break;
        case 'k':
            item = d.pc.ring_slot_1;
            isValidInput = true;
            break;
        case 'l':
            item = d.pc.ring_slot_2;
            isValidInput = true;
            break;
        case 'q':
        case 27: // ESC
            render_top_bar(COLOR_DEFAULT_ID, "Canceled");
            render_grid_default(d);
            return nullptr;
        default:
            render_top_bar(COLOR_ERROR_ID, "Invalid Input");
            continue;
        }

        if (item == nullptr)
        {
            render_top_bar(COLOR_ERROR_ID, "No Item to Inspect in this slot");
            isValidInput = false;
            continue;
        }
    }

    if (item == nullptr)
    {
        render_top_bar(COLOR_ERROR_ID, "No Item to Inspect in this slot");
        return nullptr;
    }

    return item;
}

Item *ui::get_item_from_inventory(Dungeon &d)
{
    for (int line = 1; line < 24; line++){
        move(line, 0);
        clrtoeol();
    }

    render_centered_line(1, COLOR_DEFAULT_ID, "Select an item (0-9) or press 'q' or ESC to cancel");

    render_centered_line(
        12, 
        COLOR_DEFAULT_ID, 
        "%c  %c  %c  %c  %c  %c  %c  %c  %c  %c",
        d.pc.items.size() >= 1 ? d.pc.items[0]->symbol : ' ',
        d.pc.items.size() >= 2 ? d.pc.items[1]->symbol : ' ',
        d.pc.items.size() >= 3 ? d.pc.items[2]->symbol : ' ',
        d.pc.items.size() >= 4 ? d.pc.items[3]->symbol : ' ',
        d.pc.items.size() >= 5 ? d.pc.items[4]->symbol : ' ',
        d.pc.items.size() >= 6 ? d.pc.items[5]->symbol : ' ',
        d.pc.items.size() >= 7 ? d.pc.items[6]->symbol : ' ',
        d.pc.items.size() >= 8 ? d.pc.items[7]->symbol : ' ',
        d.pc.items.size() >= 9 ? d.pc.items[8]->symbol : ' ',
        d.pc.items.size() >= 10 ? d.pc.items[9]->symbol : ' '
    );
    render_centered_line(13, COLOR_DEFAULT_ID, "0  1  2  3  4  5  6  7  8  9");

    bool isValidInput = false;

    int input;
    Item *item;
    while (!isValidInput)
    {
        timeout(-1);
        input = getch();

        quit_game(d, input);

        switch (input)
        {
        case '0':
            item = d.pc.items.size() >= 1 ? d.pc.items[0] : nullptr;
            isValidInput = true;
            break;
        case '1':
            item = d.pc.items.size() >= 2 ? d.pc.items[1] : nullptr;
            isValidInput = true;
            break;
        case '2':
            item = d.pc.items.size() >= 3 ? d.pc.items[2] : nullptr;
            isValidInput = true;
            break;
        case '3':
            item = d.pc.items.size() >= 4 ? d.pc.items[3] : nullptr;
            isValidInput = true;
            break;
        case '4':
            item = d.pc.items.size() >= 5 ? d.pc.items[4] : nullptr;
            isValidInput = true;
            break;
        case '5':
            item = d.pc.items.size() >= 6 ? d.pc.items[5] : nullptr;
            isValidInput = true;
            break;
        case '6':
            item = d.pc.items.size() >= 7 ? d.pc.items[6] : nullptr;
            isValidInput = true;
            break;
        case '7':
            item = d.pc.items.size() >= 8 ? d.pc.items[7] : nullptr;
            isValidInput = true;
            break;
        case '8':
            item = d.pc.items.size() >= 9 ? d.pc.items[8] : nullptr;
            isValidInput = true;
            break;
        case '9':
            item = d.pc.items.size() >= 10 ? d.pc.items[9] : nullptr;
            isValidInput = true;
            break;
        case 'q':
        case 27: // ESC
            render_top_bar(COLOR_DEFAULT_ID, "Canceled");
            render_grid_default(d);
            return nullptr;
        default:
            render_top_bar(COLOR_ERROR_ID, "Invalid Input");
            continue;
        }

        if (item == nullptr)
        {
            render_top_bar(COLOR_ERROR_ID, "No Item to Inspect in this slot");
            isValidInput = false;
            continue;
        }
    }

    if (item == nullptr)
    {
        render_top_bar(COLOR_ERROR_ID, "No Item to Inspect in this slot");
        return nullptr;
    }

    return item;
}