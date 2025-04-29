//
// Created by Andrew Boun on 3/24/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <ui/ui.hpp>

// #define COLOR_DEFAULT_ID 1
// #define COLOR_PLAYER_ID 2
// #define COLOR_STAIR_ID 3
// #define COLOR_SUCCESS_ID 3
// #define COLOR_MONSTER_ID 4
// #define COLOR_ERROR_ID 5
// #define COLOR_WARNING_ID 6


void ui::init_ncurses() {
    initscr();
    raw();                 // Disable line buffering
    keypad(stdscr, TRUE);  // Enable special keys
    noecho();              // Don't echo input characters
    curs_set(0);           // Hide cursor
    start_color();         // Enable colors
    use_default_colors();  // Use default colors
    timeout(0);            // Non-blocking input

    init_pair(COLOR_DEFAULT_ID, COLOR_WHITE, -1);           // Default
    init_pair(COLOR_PLAYER_ID, COLOR_WHITE, COLOR_YELLOW);  // Player
    init_pair(COLOR_STAIR_ID, COLOR_GREEN, -1);             // Stairs and Success
    init_pair(COLOR_MONSTER_ID, COLOR_CYAN, COLOR_RED);     // Monster
    init_pair(COLOR_ERROR_ID, COLOR_RED, -1);               // ERROR
    init_pair(COLOR_WARNING_ID, COLOR_YELLOW, -1);          // Warning
}

void ui::init_NPC_colors(std::vector<NPC*> npcs){
    for (size_t i = 0; i < npcs.size(); i++){
        int color_pair_id = 20 + (i % 100);
        init_pair(color_pair_id, npcs[i]->color[0], npcs[i]->color[0]);
    }
}

void ui::init_item_colors(std::vector<Item*> items){
    for (size_t i = 0; i < items.size(); i++){
        int color_pair_id = 120 + (i % 100);
        init_pair(color_pair_id, items[i]->color, -1);
    }
}

void ui::destroy_ncurses() {
    endwin();
}


int ui::get_input(Dungeon &d) {
    bool is_dist_map = false;

    while (1) {
        timeout(-1);
        int input = getch();
        clear_top_bar(false);
        int result = 0;
        
        
        // Process directional keys
        switch (input) {
            case '7': // move up-left
            case 'y':
                result = handle_player_movement(d, d.getPC().getPosition().getX() - 1, d.getPC().getPosition().getY() - 1);
                break;
                
            case '8': // move up
            case 'k':
                result = handle_player_movement(d,d.getPC().getPosition().getX(), d.getPC().getPosition().getY() - 1);
                break;
                
            case '9': // move up-right
            case 'u':
                result = handle_player_movement(d,d.getPC().getPosition().getX() + 1, d.getPC().getPosition().getY() - 1);
                break;
                
            case '6': // move right
            case 'l':
                result = handle_player_movement(d,d.getPC().getPosition().getX() + 1, d.getPC().getPosition().getY());
                break;
                
            case '3': // move down-right
            case 'n':
                result = handle_player_movement(d,d.getPC().getPosition().getX() + 1, d.getPC().getPosition().getY() + 1);
                break;
                
            case '2': // move down
            case 'j':
                result = handle_player_movement(d,d.getPC().getPosition().getX(), d.getPC().getPosition().getY() + 1);
                break;
                
            case '1': // move down-left
            case 'b':
                result = handle_player_movement(d,d.getPC().getPosition().getX() - 1, d.getPC().getPosition().getY() + 1);
                break;
                
            case '4': // move left
            case 'h':
                result = handle_player_movement(d,d.getPC().getPosition().getX() - 1, d.getPC().getPosition().getY());
                break;
            
            case '5':
            case '.':
            case ' ': 
                render_top_bar(COLOR_WARNING_ID, "Player Skipped Their Turn");
                return 1; // Skip turn
                
            case '<': // Up stairs
                result = handle_player_movement(d, -2, -2); // -2 for up stairs
                break;
                
            case '>': // Down stairs
                result = handle_player_movement(d, -3, -3); // -3 for down stairs
                break;
            
            case 'f':
                d.setFogStatus(!d.getFogStatus());
                if (d.getFogStatus()) {
                    render_top_bar(COLOR_SUCCESS_ID, "Fog of War Enabled");
                    render_grid(d, d.getFog(), true); // fog is on
                } else {
                    render_top_bar(COLOR_SUCCESS_ID, "Fog of War Disabled");
                    render_grid(d, d.getGrid()); // fog is off
                }
                continue;
            
            case 'g':
                // if (teleport(d)) result = 1;
                teleport(d);
                d.update_fog_grid();
                if (d.getNumMonsters() == 0) result = 1; // all monsters dead, stop game by returning
                if (d.getFogStatus()) {
                    render_grid(d, d.getFog(), true); // fog is on
                } else {
                    render_grid(d, d.getGrid()); // fog is off
                }
                is_dist_map = false; // reset distance map
                break;


            case 'q':
                render_top_bar(COLOR_ERROR_ID, "Press 'shift + q' to quit");
                break;
                
            case 'Q':
                destroy_ncurses();
                printf("Game terminated by user\n");
                exit(0);
                break;
            
            case 'm': // Monster list
                result = 0; // no movement, run loop again
                handle_monster_list(d);
                break;

            case 'L': // Inspect monster
                result = 0; // no movement, run loop again
                selectMonster(d);
                break;

            case 'D': // non-tunneling dist map
                result = 0; // no movement, run loop again
                if (is_dist_map) {
                    if (d.getFogStatus()) {
                        render_grid(d, d.getFog(), true); // fog is on
                    } else {
                        render_grid(d, d.getGrid()); // fog is off
                    }
                } else {
                    printDistanceMap(d.getNonTunnelingDistanceMap());
                }
                is_dist_map = !is_dist_map; // toggle dist map
                break;
            
            case 'T': // tunneling dist map
                result = 0; // no movement, run loop again
                if (is_dist_map) {
                    if (d.getFogStatus()) {
                        render_grid(d, d.getFog(), true); // fog is on
                    } else {
                        render_grid(d, d.getGrid()); // fog is off
                    }
                } else {
                    printDistanceMap(d.getTunnelingDistanceMap());
                }
                is_dist_map = !is_dist_map; // toggle dist map
                break;
            
            case 'i': // Inventory
                result = 0; // no movement, run loop again
                render_inventory(d);
                break;
            
            case 'e': // Equipment
                result = 0; // no movement, run loop again
                render_equipment(d);
                break;
            
            case 'I': // Inspect item
                result = 0; // no movement, run loop again
                inspect_item(d);
                break;

            case 'x': // Expunge item
                result = 0; // no movement, run loop again
                expunge_item(d);
                break;
                
            case 'd': // Drop item
                result = 0; // no movement, run loop again
                drop_item(d);
                break;   

            case 't': // Take off item
                result = 0; // no movement, run loop again
                take_off_item(d);
                break;
            
            case 'w': // Wear item
                result = 0; // no movement, run loop again
                wear_item(d);
                break;
                
            default:
                render_top_bar(COLOR_ERROR_ID, "Invalid Input");
                continue; // Get input again
        }
        
        // Process the result from movement
        if (result == MOVEMENT_STAIRS) return MOVEMENT_STAIRS;
        if (result == 1) return 1;
    }
}

int ui::handle_player_movement(Dungeon &d, int x, int y) {

    // Avoid \t to keep centering of top bar message
    // render_top_bar(
    //     COLOR_DEFAULT_ID,
    //     "Player Previously at: (%d, %d)          Player Currently At: (%d, %d)",
    //     d.getPC().getPosition().getX(), d.getPC().getPosition().getY(), x, y
    // );

    int move_result = d.movePC(x, y);
    
    if (move_result == 0) { // invalid move
        render_top_bar(COLOR_ERROR_ID, "Invalid Player Movement, Try Again");
        return 0;  // Return invalid movement code
    } else if (move_result == MOVEMENT_STAIRS) {
        render_top_bar(COLOR_STAIR_ID, "Player uses stairs");
        return MOVEMENT_STAIRS; // Return stairs code
    }

    return 1; // Return successful movement
}
