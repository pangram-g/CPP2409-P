#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <limits.h>
#include <ncurses/ncurses.h>
using namespace std;


class Position
{
public:
    int x, y; // 각 개체의 x,y좌표
};
void PathFinding(Position *s, Position *e);

class Map
{
public:
    Position coordinate; // 장소가 시작되는 x,y좌표
    int height, width;   // 장소의 가로,세로길이
    Position **doors;    // 문들의 좌표

    Map(int x, int y, int w, int h); // 생성자 선언
    ~Map();                          // 소멸자 선언
};

class Player
{
public:
    Position coordinate; // 유저의 x,y좌표
    int health;          // 유저의 체력
    string item;         // 유저의 장비

    Player(int x = 0, int y = 0, int h = 20); // 생성자 선언
    ~Player();                                // 소멸자 선언
};

class Monster
{
public:
    char script;
    Position coordinate; // 몬스터의 x,y좌표
    int health;
    int attack;
    int speed;
    int pathfinding;
    Monster(int x = 0, int y = 0, int h = 20);
};

// 장소 관련 함수
Map **MapSetUp();
Map *CreateMap(int x, int y, int w, int h);
void DrawMap(Map *map);
void ConnectDoor(Position *door1, Position *door2);

// 플레이어 관련 함수
Player *PlayerSetUp();

// 기능 함수
void PlayerMove(int x, int y, Player *user);
void Handleinput(int input, Player *user);
void CheckPosition(int newy, int newx, Player *user); // 장소 유효성 검사

// 몬스터 함수
Monster *CreateMonster(int x, int y, int w);
void MonsterSetting();
int AddMonster();
void SetStartPosition(Monster *monster, Map *map);
