#include "header.h"

/*Game::Game(int currentlevel) : currentlevel(currentlevel)
{
    for (int i = 0; i < 10; i++)
    {
        level[i] = nullptr;
    }
}

Game::~Game()
{
    for (int i = 0; i < 10; i++)
    {
        if (level[i] != nullptr)
        {
            delete level[i]; // 동적 메모리 해제
            level[i] = nullptr;
        }
    }
}*/

void Rendering(Game *game)
{
    clear();
    //CoutGameInformation(game->level[(game->currentlevel) - 1]);
    DrawLevel(game->level[game->currentlevel - 1]);
    refresh();
}

void GameLoop(Game *game)
{
    int ch = '\0';
    Position *position;
    Level *level;

    if (game->currentlevel == 0)
    {
        game->level[game->currentlevel] = LevelSetUp(1);
        game->currentlevel++;
    }
    level = game->level[(game->currentlevel) - 1];

    // 메인 루프
    while (ch != 'q')
    {
        position = HandleInput(ch, level->player);
        CheckPosition(position, level);
        MoveMonster(level);

        Rendering(game);
        refresh();
        if (level->player->health <= 0)
        {
            game->currentlevel = 0;
            return;
        }
        ch = getch();
    }
}