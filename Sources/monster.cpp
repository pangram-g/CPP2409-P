#include "header.h"

Monster::Monster(int x, int y, int h) : coordinate({x, y}), health(h) {};

Monster *MonsterSetting(int x, int y, int w)
{
    Monster *monster;
    monster = new Monster;

    monster->coordinate.x = x;
    monster->coordinate.y = y;
    /*switch (w)
    {
    // 거미
    case 0:
        monster->health = 2;
        monster->attack = 1;
        monster->speed = 1;
        monster->pathfinding = 1;//foseja dlehd

    // 고블린
    case 1:

    // 추적자
    case 2:


    }*/
    monster->coordinate.x = x;

    Gotxy(monster->coordinate.x, monster->coordinate.y);
    cout << "@";

    return monster;
}

/*int AddMonster(){
    int x;

}*/
