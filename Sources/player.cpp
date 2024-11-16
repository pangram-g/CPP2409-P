#include "player.h"
using namespace std;

Player::Player() : xPosition(0), yPosition(0), health(20) {}

Player *playerSetup()
{
    Player *newPlayer;
    newPlayer = new Player;

    newPlayer->xPosition = 14;
    newPlayer->yPosition = 14;
    newPlayer->health = 20;

    Gotxy(newPlayer->xPosition, newPlayer->yPosition);
    cout << "@"; // 유저를 나타내는 문자

    return newPlayer;
}
