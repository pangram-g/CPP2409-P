//유저에 대한 정보 헤더파일

#pragma once

#include <iostream>
#include "hp.h"
#include <windows.h>
using namespace std;

class Player
{
public:
    int xPosition, yPosition, health;
    Player();
};

Player *playerSetup();

void Gotxy(int x, int y);

