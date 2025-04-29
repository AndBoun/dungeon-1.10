//
// Created By Andrew Boun on 4/2/2025
//

#ifndef PC_HPP
#define PC_HPP
#include <character/Character.hpp>
#include <utils/Point.hpp>
#include <dungeon/base/Cell.hpp>

const int PC_SPEED = 10; // Speed of the player character

class PC : public Character
{
public:
    Item *weapon_slot = nullptr; 
    Item *offhand_slot = nullptr;
    Item *range_slot = nullptr;
    Item *armor_slot = nullptr;
    Item *helmet_slot = nullptr;
    Item *cloak_slot = nullptr;
    Item *gloves_slot = nullptr;
    Item *boots_slot = nullptr;
    Item *amulet_slot = nullptr;   
    Item *light_slot = nullptr;
    Item *ring_slot_1 = nullptr;
    Item *ring_slot_2 = nullptr;

    std::vector<Item*> get_equipment() const {
        return {
            weapon_slot,
            offhand_slot,
            range_slot,
            armor_slot,
            helmet_slot,
            cloak_slot,
            gloves_slot,
            boots_slot,
            amulet_slot,
            light_slot,
            ring_slot_1,
            ring_slot_2
        };
    }

    std::vector<Dice> damDices = {};


    PC();
    PC(Point position);
    ~PC();

    void updatePCAttributes();
    int getDamage() override;
};

#endif