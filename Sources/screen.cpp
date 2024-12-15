#include "header.h"

// 화면 세팅
void ScreenSetUp()
{

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    if (resize_term(MAX_HEIGHT, MAX_WIDTH) == ERR)
    {
        cerr << "Error: Unable to resize terminal!" << endl;
        endwin();
        return;
    }
    refresh();

    srand(time(NULL));
}

// 유저 정보 불러오기
void CoutGameInformation(Level *level)
{
    if (!level || !level->player)
    {
        cerr << "오류 : 레벨이나 유저가 초기화되지 않음" << endl;
        return;
    }

    cerr << "디버그 : Level = " << level->level
         << ", Player Hp = " << level->player->health
         << ", Max Hp = " << level->player->maxhealth
         << ", Attack = " << level->player->attack << endl;

    refresh();
    mvprintw(45, 1, "Level: %d | Hp: %d(%d) | Attack: %d      ",
             level->level, level->player->health,
             level->player->maxhealth, level->player->attack);
    cout << "디버그 : 정보가 불러와짐" << endl;
    refresh();
}