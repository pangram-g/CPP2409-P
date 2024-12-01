// 장소에 대한 헤더파일

#pragma once

#include <iostream>
#include <windows.h>
using namespace std;

class Position{
    public:
    int x;
    int y;
};

// 클래스로 장소에 대한 기본정보 구현
class Map
{
public:
    int xPosition; // 장소가 시작되는 x좌표
    int yPosition; // 장소가 시작되는 y좌표
    int height;    // 장소의 높이(세로길이)
    int width;     // 장소의 길이(가로길이)
    Position door[4];// 장소의 문
    // 0=바닥, 1=벽, 2=문
    int **Attribute; // 장소의 속성

    Map(int x = 0, int y = 0, int h = 0, int w = 0); // 생성자 선언
    ~Map();                                          // 소멸자 선언
};
// 속성 설정 함수
void SetAttribute(Map *map, int x, int y, int A);

// 속성 확인 함수
int GetAttribute(Map *map, int x, int y);

// 장소를 특정장소에 만들기위한 좌표이동 함수
void Gotxy(int x, int y);

// 장소 생성 함수
Map *createMap(int x, int y, int h, int w);

// 장소 설정 함수
Map **mapSetup();

// 장소 만드는 함수
void drawMap(Map *R);

// 장소 문과 문 연결 함수
void connectDoor(Map *map1, Position *door1, Map *map2, Position *door2);
