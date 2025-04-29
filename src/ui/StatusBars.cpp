//
// Created By Andrew Boun on 4/21/2025
//

#include <dungeon/Dungeon.hpp>
#include <ui/ui.hpp>
#include <string>
#include <cstring>

void ui::render_centered_line(int line, int color_id, const char *format, ...) {
    char message[100];
    va_list args;
    
    // Format the string with the variable arguments
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);
    
    // Clear the line
    move(line, 0);
    clrtoeol();
    
    // Set color and print message
    attron(COLOR_PAIR(color_id));
    mvprintw(line, (DUNGEON_WIDTH - strlen(message)) / 2, "%s", message);
    attroff(COLOR_PAIR(color_id));
    
    refresh();
}

void ui::clear_bar(int line, bool refreshImmediately){
    move(line, 0);
    clrtoeol();
    if (refreshImmediately) refresh();
}

void ui::render_pc_status(const Dungeon &d) {
    render_status_1(
        COLOR_DEFAULT_ID,
        "Position: (%d, %d)    HP: %d    Number of Monsters: %d",
        d.pc.position.getX(),
        d.pc.position.getY(),
        d.pc.hp,
        d.numMonsterAlive
    );
}