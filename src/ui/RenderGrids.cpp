//
// Created by Andrew Boun on 4/22/25.
//

#include <ui/ui.hpp>    

// Render game over message
void ui::render_game_over(Dungeon &d) {
    // clear();

    clear_status_1();
    clear_status_2();
    
    render_grid(d, d.getGrid()); // Render the grid without fog
    
    if (!d.getPC().isAlive()) {
        // render_top_bar(COLOR_ERROR_ID, "Player Died, press 'q' to quit");
    } else if (!d.isBossAlive) {
        render_top_bar(COLOR_SUCCESS_ID, "BOSS Killed, press 'q' to quit");
    }
    
    
    // Render top bar handles rerendering, so we don't need to call it again

    int input;
    do {
        timeout(-1);
        input = getch();
    } while (input != 'q' && input != 'Q');
}

void ui::render_grid(const Dungeon &d, const std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT> &grid, bool is_fog_on) {

    // Get player position and radius
    int pc_x = d.pc.getPosition().getX();
    int pc_y = d.pc.getPosition().getY();

    int start_x = std::max(0, pc_x - 2);
    int end_x = std::min(DUNGEON_WIDTH - 1, pc_x + 2);

    int start_y = std::max(0, pc_y - 2);
    int end_y = std::min(DUNGEON_HEIGHT - 1, pc_y + 2);

    // Draw the dungeon grid with colors based on cell type
    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            char cell_type = grid[y][x].getType();
            Point current_point = Point(x, y);
            attron(COLOR_PAIR(COLOR_DEFAULT_ID)); 
            

            if (d.isUpStair(current_point) || d.isDownStair(current_point)) {
                attron(COLOR_PAIR(COLOR_STAIR_ID));
            }

            int current_npc_id = d.getNPCID(current_point);
            if ( // only render player and monsters in radius if fog is on
                !is_fog_on || (
                    (x >= start_x && x <= end_x) &&
                    (y >= start_y && y <= end_y)
                )
            ){
                if (d.getItemID(current_point) != -1) {
                    int item_color_pair_id = 120 + (d.getItemID(current_point) % 100);
                    attron(COLOR_PAIR(item_color_pair_id));
                    cell_type = (cell_type == '*') ? '*' : d.items[d.getItemID(current_point)]->symbol;
                }

                if (current_point == d.pc.getPosition()){
                    attron(COLOR_PAIR(COLOR_PLAYER_ID));
                    cell_type = (cell_type == '*') ? '*' : d.pc.getSymbol();
                }
                else if (current_npc_id != -1) {
                    int color_pair_id = 20 + (current_npc_id % 100);
                    attron(COLOR_PAIR(color_pair_id));
                    cell_type = (cell_type == '*') ? '*' : d.npcs[current_npc_id]->getSymbol();
                }
            }
            
            mvaddch(y + 1, x, cell_type);
        }
    }

    ui::render_pc_status(d); // Render the player's status

    refresh();
}

void ui::printDistanceMap(const std::array<std::array<int, DUNGEON_WIDTH>, DUNGEON_HEIGHT> &distanceMap) {
    const int INF = 99999999;

    // Clear the screen
    clear();

    // Print distance map content with side borders
    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            int cellValue = distanceMap[y][x];
            char ch;
            if (cellValue == INF) {
                ch = ' ';
            } else if (cellValue == 0) {
                ch = PLAYER;
            } else {
                ch = '0' + (cellValue % 10);
            }
            mvaddch(y + 1, x, ch);
        }
    }

    // Print bottom border

    refresh();
}