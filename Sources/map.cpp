#include "map.h"
#include <time.h>
using namespace std;

Map::Map(int x, int y, int h, int w) : xPosition(x), yPosition(y), height(h), width(w)
{
    // 장소의 속성을 동적할당하여 배열로 만듦
    Attribute = new int *[width];
    for (int i = 0; i < width; ++i)
    {
        Attribute[i] = new int[height];
        for (int j = 0; j < height; ++j)
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
    if (x >= 0 && x < map->width && y >= 0 && y < map->height)
    {
        map->Attribute[x][y] = A; // int A에 적은 속성값 부여
    }
}

int GetAttribute(Map *map, int x, int y)
{
    if (x >= 0 && x < map->width && y >= 0 && y < map->height)
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
    newmap->door[2].y = (newmap->yPosition) + (newmap->height)-1;
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
    connectDoor(maps[0], &(maps[0]->door[3]), maps[2], &(maps[2]->door[1]));
    return maps;
}

void drawMap(Map *R)
{
    int x, y;

    // 장소 생성시 위 아래 ------형태로 출력 및 속성 부여
    for (x = 0; x < R->width; ++x)
    {
        // 상단 경계
        Gotxy(R->yPosition, R->xPosition + x); 
        cout << "-";
        SetAttribute(R, 0, x, 1); // 속성: 상단 경계 (벽)

        // 하단 경계
        Gotxy(R->yPosition + R->height - 1, R->xPosition + x);
        cout << "-";
        SetAttribute(R, R->height - 1, x, 1); // 속성: 하단 경계 (벽)
    }

    // 장소 생성시 좌우 |....| 형태로 출력 및 속성 부여
    for (y = 1; y < R->height - 1; ++y)
    {
        // 좌측 경계
        Gotxy(R->yPosition + y, R->xPosition);
        cout << "|";
        SetAttribute(R, y, 0, 1); // 속성: 좌측 경계 (벽)

        // 우측 경계
        Gotxy(R->yPosition + y, R->xPosition + R->width - 1);
        cout << "|";
        SetAttribute(R, y, R->width - 1, 1); // 속성: 우측 경계 (벽)

        // 내부 바닥
        for (x = 1; x < R->width - 1; ++x)
        {
            Gotxy(R->yPosition + y, R->xPosition + x);
            cout << ".";
            SetAttribute(R, y, x, 0); // 속성: 내부 바닥 (바닥)
        }
    }

    // 문 출력 및 속성 부여
    for (int i = 0; i < 4; i++)
    {
        Gotxy(R->door[i].y, R->door[i].x);
        cout << "D";
        SetAttribute(R, R->door[i].y - R->yPosition, R->door[i].x - R->xPosition, 2); // 속성: 문
    }
}

void connectDoor(Map *map1, Position *door1, Map *map2, Position *door2)
{
    int currentX = door1->x;
    int currentY = door1->y;

    // 다른 방까지 이동
    while (currentX != door2->x || currentY != door2->y)
    {
        if (currentX != door2->x)
        {
            if (door2->x > currentX)
            {
                currentX += 1; // 오른쪽으로 한 칸 이동
            }
            else
            {
                currentX -= 1; // 왼쪽으로 한 칸 이동
            }
        }
        else if (currentY != door2->y)
        {
            if (door2->y > currentY)
            {
                currentY += 1; // 아래로 한 칸 이동
            }
            else
            {
                currentY -= 1; // 위로 한 칸 이동
            }
        }

        if ((currentX == map1->xPosition + 1 || currentX == map1->xPosition + map1->width - 2) &&
            (currentY == map1->yPosition + 1 || currentY == map1->yPosition + map1->height - 2))
        {
            continue; // 경계를 넘지 않음
        }

        // 연결 경로 표시
        Gotxy(currentY, currentX);
        cout << "#";

        // 속성 부여
        if (map1->xPosition <= currentX && currentX < map1->xPosition + map1->width &&
            map1->yPosition <= currentY && currentY < map1->yPosition + map1->height)
        {
            SetAttribute(map1, currentY - map1->yPosition, currentX - map1->xPosition, 0);
        }
    }

    // 마지막 점에 문 설정
    Gotxy(door2->y, door2->x);
    cout << "D";
    SetAttribute(map2, door2->y - map2->yPosition, door2->x - map2->xPosition, 2);
}
