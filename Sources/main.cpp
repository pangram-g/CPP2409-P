#include "header.h"

int main()
{
    initscr();
    noecho();
    mvprintw(0, 0, "Test output");
    refresh();
    int ch;
    // Map map(0,0,10,10);
    Map **maps = MapSetUp();
    for (int i = 0; i < 3; ++i)
    {
        DrawMap(maps[i]); // 생성된 맵들을 차례로 화면에 출력
    }
    Player *user = PlayerSetUp();
    mvprintw(10, 5, "Hello at (5, 10)"); // 콘솔 커서를 (5, 10)으로 이동

    // getch();
    while ((ch = getch()) != 'q')
    {
        Handleinput(ch, user);
    }

    for (int i = 0; i < 3; ++i)
    {
        delete maps[i];
    }
    delete[] maps;

    endwin();
    return 0;
}