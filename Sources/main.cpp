#include "header.h"

int main()
{
    ScreenSetUp();

    char ch;
    Game game;
    game.currentlevel = 0;
    Position *position;
    Level *level;

    // level = LevelSetUp(1);
    // CoutGameInformation(level);
    /*for (int i = 0; i < 50; i++)
    {
        mvprintw(i, 0, "%d", i % 10);
    }
    for (int i = 1; i < 100; i++)
    {
        mvprintw(0, i, "%d", i % 10);
    }*/

    GameLoop(&game);

    endwin();
    return 0;
}