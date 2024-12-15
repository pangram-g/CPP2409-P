#include "header.h"

// 유저 설정
Player *PlayerSetUp()
{
    Player *user;
    user = new Player;
    user->health = 20;
    user->maxhealth = 20;
    user->attack = 1;

    return user;
}

// 유저 시작 위치
void PlayerSetStartPosition(Map **map, Player *user)
{
    user->coordinate.x = map[3]->coordinate.x + 1;
    user->coordinate.y = map[3]->coordinate.y + 1;
}

// 유저 화면에 생성
void DrawPlayer(Player *player)
{
    mvprintw(player->coordinate.y, player->coordinate.x, "@");
    move(player->coordinate.y, player->coordinate.x);
}
