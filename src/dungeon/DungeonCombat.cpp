//
// Created By Andrew Boun on 4/21/2025
//

#include <dungeon/Dungeon.hpp>
#include <ui/ui.hpp>

// Character taking damage, and the amount of damage
bool Dungeon::attackCharacter(Character *c, int damage, Character *attacker){
    if (c->isAlive()){
        c->hp -= damage;

        if (c->hp <= 0){
            if (c->symbol == PLAYER){
                killPC();
                ui::render_top_bar(
                    COLOR_ERROR_ID,
                    "PC Killed by monster: %c",
                    attacker->symbol
                );
            } else {
                ui::render_top_bar(
                    COLOR_SUCCESS_ID,
                    "PC killed monster: %c",
                    getNPCs()[getNPCID(c->position)]->symbol
                );
                killNPC(c->getPosition());
            }
        }
        else if (c->symbol != PLAYER){
            ui::render_top_bar(
                COLOR_DEFAULT_ID,
                "PC attacked monster: %c     with damage: %d",
                getNPCs()[getNPCID(c->position)]->symbol,
                damage
            );
        } 


        return true;
    }
    return false;
}