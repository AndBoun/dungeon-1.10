//
// Created By Andrew Boun on 4/2/2025
//

#include <character/Character.hpp>
#include <dungeon/base/Cell.hpp>

Character::Character() : hp(100), position(Point()), speed(0), symbol(' '), alive(true), ID(-1), dice_dam(2, 3, 4) {}
Character::Character(Point position, int speed, char symbol, bool alive, int ID)
    : hp(100), position(position), speed(speed), symbol(symbol), alive(alive), ID(ID), dice_dam(2, 3, 4) {}

// Character::~Character() {}

const Point& Character::getPosition() const {
    return position;
}
int Character::getSpeed() const {
    return speed;
}

char Character::getSymbol() const {
    return symbol;
}
bool Character::isAlive() const {
    return alive;
}

void Character::setPosition(Point position) {
    this->position = position;
}

void Character::setAlive(bool alive) {
    this->alive = alive;
}