//
// Created By Andrew Boun on 4/22/2025
//

#include <ui/ui.hpp>

void ui::render_equipment(Dungeon &d)
{
    clear();

    render_top_bar(COLOR_PLAYER_ID, "In Equipment View, press 'q' or ESC to exit");

    mvprintw(2, 0, "Weapon: %s", Item::print_name_symbol(d.pc.weapon_slot).c_str());
    mvprintw(3, 0, "Offhand: %s", Item::print_name_symbol(d.pc.offhand_slot).c_str());
    mvprintw(4, 0, "Ranged: %s", Item::print_name_symbol(d.pc.range_slot).c_str());
    mvprintw(5, 0, "Armor: %s", Item::print_name_symbol(d.pc.armor_slot).c_str());
    mvprintw(6, 0, "Helmet: %s", Item::print_name_symbol(d.pc.helmet_slot).c_str());
    mvprintw(7, 0, "Cloak: %s", Item::print_name_symbol(d.pc.cloak_slot).c_str());
    mvprintw(8, 0, "Gloves: %s", Item::print_name_symbol(d.pc.gloves_slot).c_str());
    mvprintw(9, 0, "Boots: %s", Item::print_name_symbol(d.pc.boots_slot).c_str());
    mvprintw(10, 0, "Amulet: %s", Item::print_name_symbol(d.pc.amulet_slot).c_str());
    mvprintw(11, 0, "Light: %s", Item::print_name_symbol(d.pc.light_slot).c_str());
    mvprintw(12, 0, "Ring 1: %s", Item::print_name_symbol(d.pc.ring_slot_1).c_str());
    mvprintw(13, 0, "Ring 2: %s", Item::print_name_symbol(d.pc.ring_slot_2).c_str());

    refresh();

    int input;
    do
    {
        timeout(-1);
        input = getch();

        if (input == 'Q')
        {
            destroy_ncurses();
            printf("Game terminated by user\n");
            exit(0);
            break;
        }
    } while (input != 'q' && input != 'e' && input != 27);

    clear_top_bar();
    render_grid_default(d);
}

void ui::render_inventory(Dungeon &d)
{
    clear();

    int size = d.getPC().items.size();
    int i = 0;

    render_top_bar(COLOR_PLAYER_ID, "In Inventory, press 'q' or ESC to exit");

    int line = 2; // starting line
    for (; i < size; i++)
    {
        mvprintw(line++, 0, "Slot %d : %s", i, Item::print_name_symbol(d.getPC().items[i]).c_str());
    }

    for (; i < 10 /* max inventory size*/; i++)
    {
        mvprintw(line++, 0, "Slot %d : EMPTY", i);
    }

    refresh();

    int input;
    do
    {
        timeout(-1);
        input = getch();

        quit_game(d, input);
    } while (input != 'q' && input != 'i' && input != 27);

    clear_top_bar();
    render_grid_default(d);
}

