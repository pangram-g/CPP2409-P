#include "header.h"
#include <ctime>

Map::Map(int x, int y, int w, int h) : coordinate({x, y}), width(w), height(h)
{
    doors = new Position *[4]; // 문은 4개
    for (int i = 0; i < 4; ++i)
    {
        doors[i] = new Position{0, 0}; // 초기화
    }
}

Map::~Map()
{
    for (int i = 0; i < 4; ++i)
    {
        delete doors[i]; // 각 문 해제
    }
    delete[] doors;
}

Map **MapSetUp()
{
    int setup = 3; // 장소 수 설정
    Map **maps = new Map *[setup];
    maps[0] = CreateMap(13, 13, 8, 6);
    maps[1] = CreateMap(40, 2, 8, 6);
    maps[2] = CreateMap(40, 10, 8, 6);
    ConnectDoor(maps[0]->doors[3], maps[2]->doors[1]);
    return maps;
}

Map *CreateMap(int x, int y, int w, int h)
{
    Map *newmap = new Map(x, y, w, h);

    // 문을 랜덤한 위치에 만듦
    srand(time(NULL));
    // 위쪽문
    newmap->doors[0]->x = (rand() % (newmap->width - 2)) + 1 + (newmap->coordinate.x);
    newmap->doors[0]->y = newmap->coordinate.y;

    // 좌측문
    newmap->doors[1]->x = newmap->coordinate.x;
    newmap->doors[1]->y = (rand() % (newmap->height - 2)) + 1 + (newmap->coordinate.y);

    // 밑 문
    newmap->doors[2]->x = (rand() % (newmap->width - 2)) + 1 + (newmap->coordinate.x);
    newmap->doors[2]->y = (newmap->coordinate.y) + (newmap->height) - 1;
    // 우측문
    newmap->doors[3]->x = (newmap->coordinate.x) + (newmap->width) - 1;
    newmap->doors[3]->y = (rand() % (newmap->height - 2)) + 1 + (newmap->coordinate.y);

    return newmap;
}

void DrawMap(Map *map)
{
    int x, y;

    for (x = map->coordinate.x; x < map->coordinate.x + map->width; ++x)
    {
        mvprintw(map->coordinate.y, x, "-");                   // 상단
        mvprintw(map->coordinate.y + map->height - 1, x, "-"); // 하단
    }

    // 좌우 경계와 내부 그리기
    for (y = map->coordinate.y + 1; y < map->coordinate.y + map->height - 1; ++y)
    {
        mvprintw(y, map->coordinate.x, "|");                   // 좌측
        mvprintw(y, map->coordinate.x + map->width - 1, "|"); // 우측

        for (x = map->coordinate.x + 1; x < map->coordinate.x + map->width - 1; ++x)
        {
            mvprintw(y, x, ".");
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        mvprintw(map->doors[i]->y, map->doors[i]->x, "D");
    }
}

void ConnectDoor(Position *door1, Position *door2)
{
    Position temp;
    Position pre;

    int count = 0;

    temp.x = door1->x;
    temp.y = door1->y;
    pre = temp;

    // 다른 방까지 이동
    while (1)
    {
        // 왼쪽으로 이동
        if ((abs((temp.x - 1) - door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x - 1) == ' '))
        {
            pre.x = temp.x;
            temp.x = temp.x - 1;
        }
        // 오른쪽으로 이동
        else if ((abs((temp.x + 1) - door2->x) < abs(temp.x - door2->x)) && (mvinch(temp.y, temp.x + 1) == ' '))
        {
            pre.x = temp.x;
            temp.x = temp.x + 1;
        }
        // 아래로 이동
        else if ((abs((temp.y + 1) - door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y + 1, temp.x) == ' '))
        {
            pre.y = temp.y;
            temp.y = temp.y + 1;
        }
        // 위로 이동
        else if ((abs((temp.y - 1) - door2->y) < abs(temp.y - door2->y)) && (mvinch(temp.y - 1, temp.x) == ' '))
        {
            pre.y = temp.y;
            temp.y = temp.y - 1;
        }
        else
        {
            if (count == 0)
            {
                temp = pre;
                count++;
                continue;
            }
            else
            {
                break;
            }
        }

        // 경로 출력
        mvprintw(temp.y, temp.x, "#");

        // 경로 확인을 위해 대기
        getchar();
    }
}