//
// Created by Andrew Boun on 4/22/25.
//

#include <dungeon/Dungeon.hpp>
#include <ui/ui.hpp>
#include <string>

bool ui::displayMonsterInfo(Dungeon &d, Point p){
    int npc_id = d.getNPCID(p);
    if (npc_id == -1) return false;

    clear();    
    std::vector<std::string> display_list;
    std::string desc = d.npcs[npc_id]->desc;

    render_top_bar(COLOR_PLAYER_ID, "Viewing Monster Info, press 'esc' or 'q' to exit");

    display_list.push_back("Name: " + d.npcs[npc_id]->name);
    display_list.push_back("Symbol: " + std::string(1, d.npcs[npc_id]->symbol));
    display_list.push_back("HP: " + std::to_string(d.npcs[npc_id]->hp));
    display_list.push_back("Speed: " + std::to_string(d.npcs[npc_id]->speed));
    display_list.push_back("Position: (" + std::to_string(p.getX()) + ", " + std::to_string(p.getY()) + ")");

    std::string abilities;
    int desc_id = d.npcs[npc_id]->descID;
    for (size_t i = 0; i < d.npcDescList[desc_id].abil.size(); i++){
        if (i == 0) {
            abilities += d.npcDescList[desc_id].abil[i];
        } else {
            abilities += ", " + d.npcDescList[desc_id].abil[i];
        }
    }
    display_list.push_back("Abilities: " + abilities);

    Dice dice = d.npcs[npc_id]->dice_dam;
    display_list.push_back("Damage: " + std::to_string(dice.base) + "+" + std::to_string(dice.numDice) + "d" + std::to_string(dice.numSides));

    display_list.push_back("Rarity: " + std::to_string(d.npcs[npc_id]->rrty));
    display_list.push_back(""); // Empty line for spacing

    // Process description text into lines
    std::string current_line;
    for (size_t i = 0; i < desc.length(); i++) {
        if (current_line.length() >= 78 || desc[i] == '\n') {
            display_list.push_back(current_line);
            current_line.clear();
        } else {
            current_line += desc[i];
        }
    }
    
    int scroll = 0;
    render_scrollable_list(2, 24, scroll, display_list);
    while (true){
        timeout(-1);
        int input = getch();
    
        if (input == KEY_UP) {
            scroll = render_scrollable_list(2, 24, --scroll, display_list);
        }
        else if (input == KEY_DOWN) {
            scroll = render_scrollable_list(2, 24, ++scroll, display_list);
        }

        if (input == 'q' || input == 27 || input == 'L') {
            // Clear the screen and return to the main menu
            clear();
            if (d.getFogStatus()) {
                render_grid(d, d.getFog(), true /* fog is on */);
            } else {
                render_grid(d, d.getGrid());
            }
    
            render_top_bar(COLOR_SUCCESS_ID, "Exited monster selection mode");
            break;
        }

        if (input == 'Q'){
            destroy_ncurses();
            printf("Game terminated by user\n");
            exit(0);
            break;
        }
    }

    return true;
}


bool ui::selectMonster(Dungeon &d){
    std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT> grid_copy = d.getGrid();
    int result = 0;

    int x = d.getPC().getPosition().getX();
    int y = d.getPC().getPosition().getY();
    char prev = d.getGrid()[y][x].getType();

    render_top_bar(COLOR_PLAYER_ID, "In monster selection mode, press 't' to inspect, or 'q' to cancel");

    while (1) {
        prev = grid_copy[y][x].getType();
        grid_copy[y][x].setType('*');

        render_grid(d, grid_copy);

        grid_copy[y][x].setType(prev);

        timeout(-1);
        int input = getch();
        render_top_bar(COLOR_PLAYER_ID, "In monster selection mode, press 't' to inspect, or 'q' to cancel");

        switch (input){
            case 't':
                if (displayMonsterInfo(d, Point(x, y)) == false){
                    result = 0;
                    render_top_bar(COLOR_ERROR_ID, "No Monster to Inspect");
                } else {
                    result = 1;
                    // render_top_bar(COLOR_SUCCESS_ID, "Teleported to (%d, %d)", x, y);
                }
                break;
                
            
            case 'h':
            case '4':
                x--;
                break;

            case 'j':
            case '2':
                y++;
                break;

            case 'k':
            case '8':
                y--;
                break;
                
            case 'l':
            case '6':
                x++;
                break;

            case 'y':
            case '7':
                x--;
                y--;
                break;

            case 'u':
            case '9':
                x++;
                y--;
                break;

            case 'b':  
            case '1':
                x--;
                y++;
                break;

            case 'n':
            case '3':
                x++;
                y++;
                break;
            
            case 27:
            case 'L':
            case 'q':
                if (d.getFogStatus()) {
                    render_grid(d, d.getFog(), true /* fog is on */);
                } else {
                    render_grid(d, d.getGrid());
                }
                render_top_bar(COLOR_SUCCESS_ID, "Exited monster selection mode");
                return false;
                break;

            case 'Q':
                destroy_ncurses();
                printf("Game terminated by user\n");
                exit(0);
                break;
        };
        if (x < 1) x = 1;
        if (x >= DUNGEON_WIDTH - 1) x = DUNGEON_WIDTH - 2;
        if (y < 1) y = 1;
        if (y >= DUNGEON_HEIGHT - 1) y = DUNGEON_HEIGHT - 2;

        if (result) break;
    }
    
    return true;
}
