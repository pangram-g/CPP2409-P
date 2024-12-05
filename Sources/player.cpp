#include "header.h"

Player::Player(int x, int y, int h) : coordinate({x, y}), health(h) {};

Player *PlayerSetUp()
{
    Player *user;
    user = new Player;

    user->coordinate.x = 14;
    user->coordinate.y = 14;
    user->health = 14;

    mvprintw(user->coordinate.y,user->coordinate.x,"@");

    return user;
}