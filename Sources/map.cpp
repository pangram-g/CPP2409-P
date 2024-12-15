#include "header.h"

/*Map::Map(int x, int y, int w, int h) : coordinate({x, y}), width(w), height(h)
{
    numberofdoors = 4;
    doors = new Door[numberofdoors];
}
*/
Map::~Map()
{
    delete[] doors;
}

Map *CreateMap(int fleid, int numofdoor)
{
    Map *newmap = new Map();
    srand(time(NULL) + fleid);
    newmap->numberofdoors = numofdoor;

    switch (fleid)
    {
    case 0:
        newmap->coordinate = {0, 0};
        break;
    case 1:
        newmap->coordinate = {33, 0};
        break;
    case 2:
        newmap->coordinate = {66, 0};
        break;
    case 3:
        newmap->coordinate = {0, 20};
        break;
    case 4:
        newmap->coordinate = {33, 20};
        break;
    case 5:
        newmap->coordinate = {66, 20};
        break;
    }

    newmap->height = rand() % 6 + 4; // 최소 4 ~ 최대 9
    newmap->width = rand() % 14 + 4; // 최소 4 ~ 최대 17

    newmap->coordinate.x += rand() % (29 - newmap->width + 1);
    newmap->coordinate.y += rand() % (17 - newmap->height + 1);

    newmap->doors = new Door[numofdoor];
    for (int i = 0; i < numofdoor; i++)
    {
        newmap->doors[i].connect = 0;
        newmap->doors[i].coordinate = {0, 0};
    }

    // 위쪽문
    newmap->doors[0].coordinate.x = (rand() % (newmap->width - 2)) + 1 + (newmap->coordinate.x);
    newmap->doors[0].coordinate.y = newmap->coordinate.y;

    // 좌측문
    newmap->doors[1].coordinate.x = newmap->coordinate.x;
    newmap->doors[1].coordinate.y = (rand() % (newmap->height - 2)) + 1 + (newmap->coordinate.y);

    // 밑 문
    newmap->doors[2].coordinate.x = (rand() % (newmap->width - 2)) + 1 + (newmap->coordinate.x);
    newmap->doors[2].coordinate.y = (newmap->coordinate.y) + (newmap->height) - 1;
    // 우측문
    newmap->doors[3].coordinate.x = (newmap->coordinate.x) + (newmap->width) - 1;
    newmap->doors[3].coordinate.y = (rand() % (newmap->height - 2)) + 1 + (newmap->coordinate.y);

    return newmap;
}

void DrawMap(Map *map)
{
    int x, y;

    // 상단 하단 경계 그리기
    for (x = map->coordinate.x; x < map->coordinate.x + map->width; ++x)
    {
        mvprintw(map->coordinate.y, x, "-");                   // 상단
        mvprintw(map->coordinate.y + map->height - 1, x, "-"); // 하단
    }

    // 좌우 경계와 내부 그리기
    for (y = map->coordinate.y + 1; y < map->coordinate.y + map->height - 1; ++y)
    {
        mvprintw(y, map->coordinate.x, "|");                  // 좌측
        mvprintw(y, map->coordinate.x + map->width - 1, "|"); // 우측

        for (x = map->coordinate.x + 1; x < map->coordinate.x + map->width - 1; ++x)
        {
            mvprintw(y, x, ".");
        }
    }
    // 문 그리기
    for (int i = 0; i < 4; ++i)
    {
        mvprintw(map->doors[i].coordinate.y, map->doors[i].coordinate.x, "+");
    }
}

Map **MapSetUp()
{
    int setup = 6; // 장소 수 설정
    Map **maps = new Map *[setup];
    for (int i = 0; i < setup; i++)
    {
        maps[i] = CreateMap(i, 4);
        DrawMap(maps[i]);
    }
    return maps;
}

void ConnectDoor(Level *level) {
    srand(time(NULL));

    for (int i = 0; i < level->numberofmaps; i++) {
        for (int j = 0; j < level->map[i]->numberofdoors; j++) {
            if (level->map[i]->doors[j].connect == 1) {
                continue;
            }

            int count = 0;
            int maxAttempts = 10; // 문 연결 최대 시도 횟수
            bool connected = false;

            while (count < maxAttempts) {
                int randommap = rand() % level->numberofmaps;

                if (!level->map[randommap]) {
                    cerr << "오류: 장소 " << randommap << " 이 초기화 되어있지 않습니다." << endl;
                    count++;
                    continue;
                }

                int randomdoor = rand() % level->map[randommap]->numberofdoors;

                cout << "문 확인 : map[" << randommap << "] door[" << randomdoor << "] "
                     << "& map[" << i << "] door[" << j << "]" << endl;

                // 동일 맵이거나 이미 연결된 문이면 스킵
                if (level->map[randommap]->doors[randomdoor].connect == 1 || randommap == i) {
                    cout << "같은 맵에 있는 문이거나 연결된 문입니다." << endl;
                    count++;
                    continue;
                }

                // 문 좌표 유효성 검사 및 재생성
                if (level->map[randommap]->doors[randomdoor].coordinate.x <= 0 ||
                    level->map[randommap]->doors[randomdoor].coordinate.x >= MAX_WIDTH ||
                    level->map[randommap]->doors[randomdoor].coordinate.y <= 0 ||
                    level->map[randommap]->doors[randomdoor].coordinate.y >= MAX_HEIGHT ||
                    level->map[i]->doors[j].coordinate.x <= 0 ||
                    level->map[i]->doors[j].coordinate.x >= MAX_WIDTH ||
                    level->map[i]->doors[j].coordinate.y <= 0 ||
                    level->map[i]->doors[j].coordinate.y >= MAX_HEIGHT) {
                    cerr << "오류 : 문 좌표가 유효하지 않은, 다시 시작중..." << endl;
                    count++;
                    continue;
                }

                // 경로 탐색
                try {
                    PathFind(&level->map[randommap]->doors[randomdoor].coordinate,
                             &level->map[i]->doors[j].coordinate);

                    // 연결 성공
                    level->map[randommap]->doors[randomdoor].connect = 1;
                    level->map[i]->doors[j].connect = 1;
                    connected = true;
                    break;
                } catch (const exception &e) {
                    cerr << "경로 탐색 중 오류 발생 :" << e.what() << endl;
                    count++;
                    continue;
                }
            }

            // 연결 실패 시 경고 메시지
            if (!connected) {
                cerr << "map [" << j << "] 의 문 [" << i << "] 을 "
                     << maxAttempts << " 번 시도, 연결 실패." << endl;
            }
        }
    }
}






/*void ConnectDoor(Level *level)
{
    int randommap, randomdoor;
    int count;
    srand(time(NULL));

    for (int i = 0; i < level->numberofmaps; i++)
    {
        for (int j = 0; j < level->map[i]->numberofdoors; j++)
        {
            if (level->map[i]->doors[j].connect == 1)
            {
                continue;
            }

            count = 0;

            while (count < 2)
            {
                randommap = rand() % (level->numberofmaps);
                randomdoor = rand() % (level->map[randommap]->numberofdoors);

                if (level->map[randommap]->doors[randomdoor].connect == 1 || randommap == i)
                {
                    count++;
                    continue;
                }
                PathFind(&level->map[randommap]->doors[randomdoor].coordinate,&level->map[i]->doors[j].coordinate);
                level->map[randommap]->doors[randomdoor].connect = 1;
                level->map[i]->doors[j].connect = 1;
                break;
            }
        }
    }
}*/