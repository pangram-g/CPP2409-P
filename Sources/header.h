#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <windows.h>
// #include <conio.h>
#include <limits.h>
#include <ctime>
#include <ncurses/ncurses.h>
using namespace std;

// 전역 변수
const int MAX_HEIGHT = 50;
const int MAX_WIDTH = 100;

class Position
{
public:
    int x, y; // 각 개체의 x,y좌표
};

class Door
{
public:
    Position coordinate; // 장소에 있는 문의 좌표
    int connect;         // 문 연결여부
};

class Map
{
public:
    Position coordinate; // 장소가 시작되는 x,y좌표
    int height, width;   // 장소의 가로,세로길이
    Door *doors;         // 문
    int numberofdoors;   // 문 개수

    ~Map(); // 소멸자 선언
};

class Player
{
public:
    Position coordinate;   // 유저의 x,y좌표
    int health, maxhealth; // 유저의 체력
    string item;           // 유저의 장비
    int attack;            // 유저의 공격력
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
    int alive;
};

class Level
{
public:
    char **tiles;
    int level;
    int numberofmaps;
    Map **map;
    Monster **monster;
    int numberofmonsters;
    Player *player;
};

class Game
{
public:
    Level *level[10];
    int currentlevel;

    // Game(int currentlevel);
    // ~Game();
};

// 전체 게임 관련 함수
void Rendering(Game *game);
void GameLoop(Game *game);

// 레벨 관련 함수
Level *LevelSetUp(int upcount);
void DrawLevel(Level *level);
char **saveLevelPositions();

// 화면 관련 함수
void ScreenSetUp();
void CoutGameInformation(Level *level);

// 장소 관련 함수
Map **MapSetUp();
Map *CreateMap(int fleid, int numofdoor);
void DrawMap(Map *map);
void ConnectDoor(Level *level);

// 플레이어 관련 함수
Player *PlayerSetUp();
void PlayerSetStartPosition(Map **map, Player *user);
void DrawPlayer(Player *player);

// 기능 함수
void PlayerMove(Position *newPosition, Player *user);
Position *HandleInput(int input, Player *user);
void CheckPosition(Position *position, Level *level); // 장소 유효성 검사
void Combat(Player *player, Monster *monster, int command);

// 몬스터 함수
Monster *CreateMonster(int h, int a, int sp, int p, char s);
Monster *SelectMonster(int level);
Monster *GetTileMonster(Position *coordinate, Monster **monster);
void AddMonster(Level *level);
void SetStartPosition(Monster *monster, Map *map);
void DeathMonster(Monster *monster);
void MoveMonster(Level *level);
void PathFindingRandom(Position *coordinate);
void PathFindingChase(Position *start, Position *end);
void DrawMonster(Monster *monster);

// pathfind 함수
void addPositionYX(vector<vector<int>> &frontier, int frontierCount, int y, int x);
int CheckCoordinate(int y, int x);
int addNeighbors(vector<vector<int>> &frontier, int frontierCount, vector<vector<vector<int>>> &cameFrom, int y, int x);
void PathFind(Position *start, Position *end);
