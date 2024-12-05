#include "header.h"

Monster::Monster(int x, int y, int h) : coordinate({x, y}), health(h) {};

// 몬스터 종류별로 생성
Monster *CreateMonster(int x, int y, int w)
{
    Monster *monster;
    monster = new Monster;

    monster->coordinate.x = x;
    monster->coordinate.y = y;
    switch (w)
    {
    // 거미
    case 0:
        monster->health = 2;
        monster->attack = 1;
        monster->speed = 1;
        monster->pathfinding = 1; // 랜덤 이동
        monster->script = 'S';

    // 고블린
    case 1:
        monster->health = 2;
        monster->attack = 1;
        monster->speed = 1;
        monster->pathfinding = 1; // 랜덤 이동
        monster->script = 'G';

    // 추적자
    case 2:
        monster->health = 2;
        monster->attack = 1;
        monster->speed = 1;
        monster->pathfinding = 2; // 추적 이동
        monster->script = 'H';
    }

    return monster;
}
// 몬스터
void MonsterSetting()
{
    for (int i = 0; i < number; i++)
    {
        MonsterSetting(int x, int y, int w)
    }
}
// 총 몬스터 수를 정하는 함수
void AddMonster(int num) // 소환될 몬스터수
{
    srand(time(NULL));
    int number = rand() % 1 + 2;
    for (int x; x < number; x++)
    {
    }
}

void SetStartPosition(Monster *monster, Map *map)
{
    char buffer[8];
    monster->coordinate.x = (rand() % (map->width - 2)) + map->coordinate.x + 1;
    monster->coordinate.y = (rand() % (map->height - 2)) + map->coordinate.y + 1;

    mvprintw(monster->coordinate.y,monster->coordinate.x,monster->script);
}