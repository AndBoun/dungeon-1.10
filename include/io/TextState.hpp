//
// Created By Andrew Boun on 4/29/2025
//

#ifndef TEXTSTATE_HPP
#define TEXTSTATE_HPP

#include <dungeon/Dungeon.hpp>
#include <fstream>

class TextState
{
public:
    TextState() = default;
    ~TextState() = default;

    static void saveState(Dungeon &d);
    static void loadState(Dungeon &d);

private:
    static void saveRooms(Dungeon &d, std::ofstream &file);
    static void saveStairs(Dungeon &d, std::ofstream &file); //up stairs and down stairs
    static void saveItems(Dungeon &d, std::ofstream &file);
    static void saveNPCs(Dungeon &d, std::ofstream &file);
    static void savePC(Dungeon &d, std::ofstream &file);
    static void saveNumMonsters(Dungeon &d, std::ofstream &file);
    static void saveGrid(Dungeon &d, std::ofstream &file);
    static void saveFog(Dungeon &d, std::ofstream &file); // fog grid in isFog boolean

    static void loadRooms(Dungeon &d, std::ifstream &file);
    static void loadStairs(Dungeon &d, std::ifstream &file); //up stairs and down stairs
    static void loadItems(Dungeon &d, std::ifstream &file);
    static void loadNPCs(Dungeon &d, std::ifstream &file);
    static void loadPC(Dungeon &d, std::ifstream &file);
    static void loadNumMonsters(Dungeon &d, std::ifstream &file);
    static void loadGrid(Dungeon &d, std::ifstream &file);  
    static void loadFog(Dungeon &d, std::ifstream &file); // fog grid in isFog boolean
};

#endif // TEXTSTATE_HPP