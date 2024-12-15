#include "header.h"

Monster *CreateMonster(int h, int a, int sp, int p, char s)
{
    Monster *monster;
    monster = new Monster();

    monster->health = h;
    monster->attack = a;
    monster->speed = sp;
    monster->pathfinding = p; // 랜덤 이동 여부
    monster->script = s;
    monster->alive = 1;

    return monster;
}

// 몬스터가 죽을시 불려오는 함수
void DeathMonster(Monster *monster)
{
    mvprintw(monster->coordinate.y, monster->coordinate.x, ".");
    monster->alive = 0;
}

// 레벨에 따른 몬스터 종류별로 생성
Monster *SelectMonster(int level)
{
    int nummonster;
    switch (level)
    {
    case 1:
    case 2:
    case 3:
        nummonster = (rand() % 2) + 1;
        break;
    case 4:
    case 5:
        nummonster = (rand() % 2) + 2;
        break;
    case 6:
        nummonster = 3;
        break;
    }

    switch (nummonster)
    {
    // 거미
    case 1:
        return CreateMonster(2, 1, 1, 1, 'S');

    // 고블린
    case 2:
        return CreateMonster(2, 1, 1, 2, 'G');

    // 추적자
    case 3:
        return CreateMonster(3, 2, 1, 1, 'H');
    }

    return 0;
}

// 몬스터를 추가하는 함수
void AddMonster(Level *level) // 소환될 몬스터수
{
    level->monster = new Monster *[6];
    level->numberofmonsters = 0;

    for (int x = 0; x < level->numberofmaps; x++)
    {
        if (rand() % 2 == 0)
        {
            level->monster[level->numberofmonsters] = SelectMonster(level->level);
            SetStartPosition(level->monster[level->numberofmonsters], level->map[x]);
            level->numberofmonsters++;
        }
    }
}

// 몬스터 시작 좌표 정하는 함수
void SetStartPosition(Monster *monster, Map *map)
{
    monster->coordinate.x = (rand() % (map->width - 2)) + map->coordinate.x + 1;
    monster->coordinate.y = (rand() % (map->height - 2)) + map->coordinate.y + 1;
}

// 랜덤 이동 구현 함수
void PathFindingRandom(Position *coordinate)
{
    srand(time(NULL));
    int randomnum;
    randomnum = rand() % 5;
    switch (randomnum)
    {
    case 0: // 상단 이동
        if (mvinch(coordinate->y - 1, coordinate->x) == '.')
        {
            coordinate->y = coordinate->y - 1;
        }
        break;

    case 1: // 히단 이동
        if (mvinch(coordinate->y + 1, coordinate->x) == '.')
        {
            coordinate->y = coordinate->y + 1;
        }
        break;
    case 2: // 좌측 이동
        if (mvinch(coordinate->y, coordinate->x - 1) == '.')
        {
            coordinate->x = coordinate->x - 1;
        }
        break;
    case 3: // 우측 이동
        if (mvinch(coordinate->y, coordinate->x + 1) == '.')
        {
            coordinate->x = coordinate->x + 1;
        }
        break;
    case 4: // 제자리
        break;
    }
}

// 추적 이동 구현 함수
void PathFindingChase(Position *start, Position *end)
{
    if ((abs((start->x - 1) - end->x) < abs(start->x - end->x)) && (mvinch(start->y, start->x - 1) == '.'))
    {
        start->x = start->x - 1; // 좌측 이동
    }
    else if ((abs((start->x + 1) - end->x) < abs(start->x - end->x)) && (mvinch(start->y, start->x + 1) == '.'))
    {
        start->x = start->x + 1; // 하단 이동
    }
    else if ((abs((start->y + 1) - end->y) < abs(start->y - end->y)) && (mvinch(start->y + 1, start->x) == '.'))
    {
        start->y = start->y + 1; // 하단 이동
    }
    else if ((abs((start->y - 1) - end->y) < abs(start->y - end->y)) && (mvinch(start->y - 1, start->x) == '.'))
    {
        start->y = start->y - 1; // 상단 이동
    }
}

// 몬스터 움직임 함수(1=랜덤이동, 2=추적이동)
void MoveMonster(Level *level)
{
    for (int i = 0; i < level->numberofmonsters; i++)
    {
        if (level->monster[i]->alive == 0)
            continue;

        mvprintw(level->monster[i]->coordinate.y, level->monster[i]->coordinate.y, ".");

        if (level->monster[i]->pathfinding == 1)
        {
            PathFindingRandom(&(level->monster[i]->coordinate));
        }
        else if (level->monster[i]->pathfinding == 2)
        {
            PathFindingChase(&(level->monster[i]->coordinate), &(level->player->coordinate));
        }
    }
}

// 어떤 몬스터인지 받아오는 함수
Monster *GetTileMonster(Position *coordinate, Monster **monster)
{
    for (int x = 0; x < 6; x++)
    {
        if ((coordinate->x == monster[x]->coordinate.x) && (coordinate->y == monster[x]->coordinate.y))
        {
            return monster[x];
        }
    }
    return NULL;
}

// 몬스터 화면에 그리는 함수
void DrawMonster(Monster *monster)
{
    if (monster->alive)
    {
        mvprintw(monster->coordinate.y, monster->coordinate.x, "%c", monster->script);
    }
}
