#include <iostream>
#include "Map.h"
#include "Player.h"
#include "command.h"
using namespace std;

int screenSetup();

int main()
{
    int ch;

    // screenSetup();
    Map **maps = mapSetup(); // 여러 개의 맵 생성
    for (int i = 0; i < 3; ++i)
    {
        drawMap(maps[i]); // 생성된 맵들을 차례로 화면에 출력
    }

    Player *user = playerSetup(); // 유저 생성

    // main loop
    while ((ch = getch()) != 'q')
    {
        Handleinput(ch, user, maps[0]);
    }

    // 동적 할당된 맵 메모리 해제
    for (int i = 0; i < 3; ++i)
    {
        delete maps[i];
    }
    delete[] maps;
    // user = *playerSetup();
    // while(())
    // getch();
    // endwin();
    return 0;
}

int screenSetup()
{
    return 0;
}
