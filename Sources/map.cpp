#include "map.h"
#include <time.h>
using namespace std;

Map::Map(int x, int y, int h, int w) : xPosition(x), yPosition(y), height(h), width(w)
{
    // 장소의 속성을 동적할당하여 배열로 만듦
    Attribute = new int *[height];
    for (int i = 0; i < height; ++i)
    {
        Attribute[i] = new int[width];
        for (int j = 0; j < width; ++j)
        {
            Attribute[i][j] = 0; // 0으로 초기화
        }
    }
}

Map::~Map()
{
    // 동적할당된 속성을 동적할당 해제문
    for (int i = 0; i < height; ++i)
    {
        delete[] Attribute[i];
    }
    delete[] Attribute;
}

void SetAttribute(Map *map, int x, int y, int A)
{
    if (x >= 0 && x < map->height && y >= 0 && y < map->width)
    {
        map->Attribute[x][y] = A; // int A에 적은 속성값 부여
    }
}
// 호출만 하므로 const사용으로 변화를 주지않음
int GetAttribute(const Map *map, int x, int y)
{
    if (x >= 0 && x < map->height && y >= 0 && y < map->width)
    {
        return map->Attribute[x][y];
    }
    return -1; // 유효하지 않은 좌표일 경우
}

// 특정 좌표로 커서 옮기기
void Gotxy(int x, int y)
{
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    COORD Pos = {static_cast<SHORT>(y), static_cast<SHORT>(x)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

Map *createMap(int x, int y, int h, int w)
{
    Map *newmap = new Map(x, y, h, w);

    newmap->xPosition = x;
    newmap->yPosition = y;
    newmap->height = h;
    newmap->width = w;
    // 문을 랜덤한 위치에 만듦
    srand(time(NULL));
    // 위쪽문
    newmap->door[0].x = rand() % (w - 2) + (newmap->xPosition) + 1;
    newmap->door[0].y = newmap->yPosition;

    // 좌측문
    newmap->door[1].y = rand() % (h - 2) + (newmap->yPosition) + 1;
    newmap->door[1].x = newmap->xPosition;

    // 밑 문
    newmap->door[2].x = rand() % (w - 2) + (newmap->xPosition);
    newmap->door[2].y = (newmap->yPosition) + (newmap->height);
    // 우측문
    newmap->door[3].y = rand() % (h - 2) + (newmap->yPosition) + 1;
    newmap->door[3].x = (newmap->xPosition) + (newmap->width) - 1;

    return newmap;
}

Map **mapSetup()
{
    int rows = 3; // 장소 수 설정
    Map **maps = new Map *[rows];
    maps[0] = createMap(13, 13, 6, 8);
    maps[1] = createMap(40, 2, 6, 8);
    maps[2] = createMap(40, 10, 6, 8);
    //connectDoor(maps[0]->door[3], maps[2]->door[1]);
    return maps;
}

void drawMap(Map *R)
{
    int x, y;

    // 장소 생성시 위 아래 ------형태로 출력
    for (x = R->xPosition; x < (R->xPosition) + (R->width); x++)
    {
        Gotxy(R->yPosition, x);
        cout << "-";
        SetAttribute(R, R->yPosition - R->yPosition, x - R->xPosition, 1);
        Gotxy((R->yPosition) + (R->height), x);
        cout << "-";
        SetAttribute(R, (R->yPosition) + (R->height) + 1 - R->yPosition, x - R->xPosition, 1);
    }
    // 장소 생성시 좌우 |....| 형태로 출력
    for (y = R->yPosition + 1; y < (R->yPosition) + (R->height); y++)
    {
        Gotxy(y, R->xPosition);
        cout << "|";
        SetAttribute(R, y - R->yPosition, 0, 1);
        Gotxy(y, (R->xPosition) + (R->width) - 1);
        cout << "|";
        SetAttribute(R, y - R->yPosition, (R->width) - 1, 1);
        for (x = R->xPosition + 1; x < (R->xPosition) + (R->width - 1); x++)
        {
            Gotxy(y, x);
            cout << ".";
        }
    }
    for (int i = 0; i < 4; i++)
    {
        Gotxy(R->door[i].y, R->door[i].x);
        cout << "D";
        SetAttribute(R, R->door[i].y - R->yPosition, R->door[i].x - R->xPosition, 2);
    }
}

/*void connectDoor(Position door1, Position door2)
{

    return 1;
}*/