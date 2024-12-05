#include "header.h"

using namespace std;

// 유저 이동 함수
void Handleinput(int input, Player *user)
{
    int newx;
    int newy;
    switch (input)
    {
    // 위 이동
    case 'w':
    case 'W':
        newx = user->coordinate.x;
        newy = user->coordinate.y - 1;
        break;
    // 아래 이동
    case 's':
    case 'S':
        newx = user->coordinate.x;
        newy = user->coordinate.y + 1;
        break;
    // 왼쪽 이동
    case 'a':
    case 'A':
        newx = user->coordinate.x - 1;
        newy = user->coordinate.y;
        break;
    // 오른쪽 이동
    case 'd':
    case 'D':
        newx = user->coordinate.x + 1;
        newy = user->coordinate.y;
        break;
    default:
        break;
    }

    CheckPosition(newx, newy, user);
}

// 유저 움직임 함수
void PlayerMove(int x, int y, Player *user)
{
    mvprintw(user->coordinate.y, user->coordinate.x, ".");
    user->coordinate.x = x;
    user->coordinate.y = y;
    mvprintw(user->coordinate.y, user->coordinate.x, "@");
    move(user->coordinate.y, user->coordinate.x);
}

// 장소 유효성 검사
void CheckPosition(int newx, int newy, Player *user)
{
    int space;
    switch (mvinch(newy,newx))
    {
    case '.':
    case '#':
    case 'D':
        PlayerMove(newx, newy, user);
        break;
    default:
        move(user->coordinate.y, user->coordinate.x);
        break;
    }
}
