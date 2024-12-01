#include "command.h"
#include "player.h"
#include "map.h"
#include <windows.h>

using namespace std;


// 유저 움직임 함수
void playerMove(int x, int y, Player *user)
{
    Gotxy(user->yPosition, user->xPosition);
    cout << ".";
    user->xPosition = x;
    user->yPosition = y;
    Gotxy(user->yPosition, user->xPosition);
    cout << "@";
}

// 장소 유효성 검사
void checkPosition(int newy, int newx, Player *user, Map *map)
{
    // 특정 좌표의 속성 확인
    int Attribute = GetAttribute(map, newy - map->yPosition, newx - map->xPosition);

    // 속성이 '0' (통로)일 경우에만 이동
    if (Attribute == 0 || Attribute == 2) {
        playerMove(newy, newx, user);
    }
}

void Handleinput(int input, Player *user, Map *map)
{
    int newy;
    int newx;
    switch (input)
    {
    case 'w':
    case 'W':
        newy = user->yPosition - 1;
        newx = user->xPosition;
        break;
    case 's':
    case 'S':
        newy = user->yPosition + 1;
        newx = user->xPosition;

        break;
    case 'a':
    case 'A':
        newy = user->yPosition;
        newx = user->xPosition - 1;

        break;
    case 'd':
    case 'D':
        newy = user->yPosition;
        newx = user->xPosition + 1;

        break;
    default:
        break;
    }

    checkPosition(newx, newy, user, map);
}
