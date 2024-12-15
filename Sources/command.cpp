#include "header.h"

using namespace std;

// 유저 이동 함수
Position *HandleInput(int input, Player *user)
{
    Position *newposition = new Position();

    switch (input)
    {
    // 위 이동
    case 'w':
    case 'W':
        newposition->x = user->coordinate.x;
        newposition->y = user->coordinate.y - 1;
        break;
    // 아래 이동
    case 's':
    case 'S':
        newposition->x = user->coordinate.x;
        newposition->y = user->coordinate.y + 1;
        break;
    // 왼쪽 이동
    case 'a':
    case 'A':
        newposition->x = user->coordinate.x - 1;
        newposition->y = user->coordinate.y;
        break;
    // 오른쪽 이동
    case 'd':
    case 'D':
        newposition->x = user->coordinate.x + 1;
        newposition->y = user->coordinate.y;
        break;
    default:
        delete newposition;
        break;
    }

    return newposition;
}

// 유저 움직임 함수
void PlayerMove(Position *newPosition, Player *user)
{
    user->coordinate.x = newPosition->x;
    user->coordinate.y = newPosition->y;
}

// 장소 유효성 검사
void CheckPosition(Position *position, Level *level)
{
    Player *user = level->player;
    int space;
    switch (mvinch(position->y, position->x))
    {
    // 갈 수 있는 장소면 이동
    case '.':
    case '#':
    case '+':
        PlayerMove(position, user);
        break;
    // 적이면 전투 발생
    case 'S':
    case 'G':
    case 'H':
        Combat(user, GetTileMonster(position, level->monster), 1);
    default:
        break;
    }
}

void Combat(Player *player, Monster *monster, int order)
{
    // 유저의 공격
    if (order == 1)
    {
        monster->health -= player->attack;
        if (monster->health > 0)
        {
            player->health -= monster->attack;
        }
        else
        {
            DeathMonster(monster);
        }
    }
    // 몬스터의 공격
    else if (order == 2)
    {
        player->health -= monster->attack;
        if (player->health > 0)
        {
            monster->health -= player->attack;
        }
    }
}