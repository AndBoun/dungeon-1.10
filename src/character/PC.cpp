//
// Created By Andrew Boun on 4/2/2025
//

#include <character/PC.hpp>

PC::PC() : Character(Point(), PC_SPEED, '@', true, 0) {}
PC::PC(Point position)
    : Character(position, PC_SPEED,'@', true, 0) {}
PC::~PC() {}

void PC::updatePCAttributes() {
    speed = 10;
    damDices.clear();
    
    for (auto& item : get_equipment()) {
        if (item != nullptr) {
            speed += item->speed;

            damDices.push_back(item->dice_dam);
        }
    }
}

int PC::getDamage() {
    int totalDamage = dice_dam.getRandNum();

    for (auto& dice : damDices) {
        totalDamage += dice.getRandNum();
    }

    return totalDamage;
}