//
// Created By Andrew Boun on 4/2/2025
//

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <utils/Dice.hpp>
#include <vector>
#include <optional>
#include <set>
#include <utils/Point.hpp>

// Item type string constants
static const std::string WEAPON = "WEAPON";
static const std::string OFFHAND = "OFFHAND";
static const std::string RANGED = "RANGED";
static const std::string ARMOR = "ARMOR";
static const std::string HELMET = "HELMET";
static const std::string CLOAK = "CLOAK";
static const std::string GLOVES = "GLOVES";
static const std::string BOOTS = "BOOTS";
static const std::string RING = "RING";
static const std::string AMULET = "AMULET";
static const std::string LIGHT = "LIGHT";
static const std::string SCROLL = "SCROLL";
static const std::string BOOK = "BOOK";
static const std::string FLASK = "FLASK";
static const std::string GOLD = "GOLD";
static const std::string AMMUNITION = "AMMUNITION";
static const std::string FOOD = "FOOD";
static const std::string WAND = "WAND";
static const std::string CONTAINER = "CONTAINER";

class Item
{
public:
    Point pos;
    std::string name;
    std::string desc;
    std::string type;
    int color;
    int hit;
    Dice dice_dam;
    int dodge;
    int def;
    int weight;
    int speed;
    int attr;
    int val;
    bool art;
    int rrty;
    char symbol;

    int ID; // id in array of items in dungeon
    int descID;
    bool inInventory = false; // Flag to indicate if the item is in the inventory

    Item();
    Item(std::string type, int color,
         int hit, Dice dice_dam, int dodge, int def, int weight, int speed,
         int attr, int val, bool art, int rrty);
    ~Item();

    static std::string print_name_symbol(Item *item){
        if (item == nullptr) {
            return "EMPTY";
        }
        std::string name = item->name;
        char symbol = item->symbol;
        return name + " (" + symbol + ")";
    }
};

#endif