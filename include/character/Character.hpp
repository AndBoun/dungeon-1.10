//
// Created By Andrew Boun on 4/2/2025
//

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <utils/Point.hpp>
#include <dungeon/base/Cell.hpp>
#include <item/Item.hpp>

class Character
{
public:
    int hp; // Hit points
    Point position; // Position of the character
    int speed;
    // Cell currentCell; // Current cell character is in
    char symbol; // Symbol to represent the character
    bool alive;
    int ID;

    Dice dice_dam;

    std::vector<Item*> items;

    // Constructor and Destructor
    Character();
    Character(Point position, int speed, char symbol, bool alive, int ID);
    virtual ~Character() {
        // Free items handled by Dungeon
    }

    // Getters
    virtual const Point& getPosition() const;
    virtual int getSpeed() const;
    // virtual const Cell& getCurrentCell() const;
    virtual char getSymbol() const;
    virtual bool isAlive() const;
    virtual int getDamage() {
        return dice_dam.getRandNum();
    }

    // Setters
    virtual void setPosition(Point position);
    // virtual void setCurrentCell(Cell current_cell);
    virtual void setAlive(bool Alive);
};
    
#endif