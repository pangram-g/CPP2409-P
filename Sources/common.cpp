#include "header.h"



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