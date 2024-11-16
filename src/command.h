// 입력에 대한 헤더파일
#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include "player.h"
#include "map.h"
using namespace std;

void PlayerMove(int y, int x, Player *user);

void Handleinput(int input, Player *user, Map *map);

void checkPosition(int newy, int newx, Player *user); // 장소 유효성 검사
