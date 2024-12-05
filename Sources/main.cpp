#include "header.h"

int main()
{
    //initscr();
    //refresh();
    int ch;
    // Map map(0,0,10,10);
    Map **maps = MapSetUp();
    for (int i = 0; i < 3; ++i)
    {
        DrawMap(maps[i]); // 생성된 맵들을 차례로 화면에 출력
    }
    Player *user = PlayerSetUp();
    Gotxy(5, 10); // 콘솔 커서를 (5, 10)으로 이동
    cout << "Hello at (5, 10)";
    
    //getch();
    while ((ch = getch()) != 'q')
    {
        Handleinput(ch, user, maps[0]);
    }
    
    for (int i = 0; i < 3; ++i)
    {
        delete maps[i];
    }
    delete[] maps;

   // endwin();
    return 0;
}