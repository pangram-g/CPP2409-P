#include "header.h"

// 특정 좌표로 커서 옮기기
void Gotxy(int x, int y)
{
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    COORD Pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 특정 좌표의 문자를 읽는 함수
char GetCharAtPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Invalid console handle.\n";
        return '\0';
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "Failed to get console screen buffer info.\n";
        return '\0';
    }

    CHAR_INFO charInfo;
    COORD bufferSize = {1, 1};
    COORD bufferCoord = {0, 0};
    SMALL_RECT readRegion = {static_cast<SHORT>(x), static_cast<SHORT>(y),
                             static_cast<SHORT>(x), static_cast<SHORT>(y)};

    if (!ReadConsoleOutput(hConsole, &charInfo, bufferSize, bufferCoord, &readRegion)) {
        std::cerr << "Failed to read character at (" << x << ", " << y << ")\n";
        return '\0';
    }

    return charInfo.Char.AsciiChar; // 읽은 문자 반환
}

/*void PathFinding(Position *s, Position *e)
{
    Position temp = *door1;
    Position prev = temp;
    int count = 0;

    while (s->x != e->x || temp.y != e->y)
    {
        if (abs(s->x - 1 - e->x) < abs(s->x - e->x) && (GetCharAtPosition(s->x - 1, s->y) == ' '))
        {
            s->x -= 1;
        }
        else if (abs(s->x + 1 - e->x) < abs(s->x - e->x) && (GetCharAtPosition(s->x + 1, s->y) == ' '))
        {
            s->x += 1;
        }
        else if (abs(s->y - 1 - e->y) < abs(s->y - e->y) && (GetCharAtPosition(s->x, s->y + 1) == ' '))
        {
            s->y -= 1;
        }
        else if (abs(s->y + 1 - e->y) < abs(s->y - e->y) && (GetCharAtPosition(s->x, s->y - 1) == ' '))
        {
            s->y += 1;
        }
        else
        {
            if (count == 0)
            {
                temp = prev;
                count++;
                continue;
            }
            else
            {
                break;
            }
        }

        Gotxy(temp.x, temp.y);
        cout << "#";
        getchar();
    }
}*/