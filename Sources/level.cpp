#include "header.h"

Level *LevelSetUp(int upcount)
{
    Level *level = new Level();

    level->level = upcount;
    level->numberofmaps = 6;
    level->map = MapSetUp();
    ConnectDoor(level);
    level->tiles = saveLevelPositions();
    level->player = PlayerSetUp();
    PlayerSetStartPosition(level->map, level->player);

    AddMonster(level);

    return level;
}

void DrawLevel(Level *level)
{
    // 장소 출력
    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_WIDTH; x++)
            mvaddch(y, x, level->tiles[y][x]);
    }
    // 몬스터 출력
    for (int i = 0; i < level->numberofmonsters; i++)
    {
        DrawMonster(level->monster[i]);
    }
    DrawPlayer(level->player);  // 유저 출력
    CoutGameInformation(level); // 유저 정보 출력
    refresh();
}

char **saveLevelPositions()
{
    char **positions = new char *[MAX_HEIGHT];
    for (int y = 0; y < MAX_HEIGHT; ++y)
    {
        positions[y] = new char[MAX_WIDTH];
        for (int x = 0; x < MAX_WIDTH; ++x)
        {
            if (y >= 0 && y < MAX_HEIGHT && x >= 0 && x < MAX_WIDTH)
            {
                positions[y][x] = mvinch(y, x); // curses에서 특정 위치의 문자 가져오기
            }
            else
            {
                positions[y][x] = ' '; // 유효하지 위치면 기본값 설정
            }
        }
    }
    return positions;
}
