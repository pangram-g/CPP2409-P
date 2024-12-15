#include "header.h"

// 좌표 추가 함수
void addPositionYX(vector<vector<int>>& frontier, int frontierCount, int y, int x) {
    frontier[frontierCount][0] = y;
    frontier[frontierCount][1] = x;
}

// 특정 위치 검사 함수
int CheckCoordinate(int y, int x) {
    char temp = mvinch(y, x);

    if (temp == '.' || temp == '|' || temp == '-') {
        return 0;
    } else {
        return 1;
    }
}

// 주변 위치를 추가하는 함수
int addNeighbors(vector<vector<int>>& frontier, int frontierCount, vector<vector<vector<int>>>& cameFrom, int y, int x) {
    // 북쪽
    if (y > 0 && cameFrom[y - 1][x][0] < 0 && CheckCoordinate(y - 1, x)) {
        addPositionYX(frontier, frontierCount, y - 1, x);
        frontierCount++;
        cameFrom[y - 1][x][0] = y;
        cameFrom[y - 1][x][1] = x;
    }

    // 남쪽
    if (y < (MAX_HEIGHT - 1) && cameFrom[y + 1][x][0] < 0 && CheckCoordinate(y + 1, x)) {
        addPositionYX(frontier, frontierCount, y + 1, x);
        frontierCount++;
        cameFrom[y + 1][x][0] = y;
        cameFrom[y + 1][x][1] = x;
    }

    // 동쪽
    if (x < (MAX_WIDTH - 1) && cameFrom[y][x + 1][0] < 0 && CheckCoordinate(y, x + 1)) {
        addPositionYX(frontier, frontierCount, y, x + 1);
        frontierCount++;
        cameFrom[y][x + 1][0] = y;
        cameFrom[y][x + 1][1] = x;
    }

    // 서쪽
    if (x > 0 && cameFrom[y][x - 1][0] < 0 && CheckCoordinate(y, x - 1)) {
        addPositionYX(frontier, frontierCount, y, x - 1);
        frontierCount++;
        cameFrom[y][x - 1][0] = y;
        cameFrom[y][x - 1][1] = x;
    }

    return frontierCount;
}

// 경로 찾기 함수
void PathFind(Position* start, Position* end) {
    if (start->x < 0 || start->x >= MAX_WIDTH || start->y < 0 || start->y >= MAX_HEIGHT ||
        end->x < 0 || end->x >= MAX_WIDTH || end->y < 0 || end->y >= MAX_HEIGHT) {
        printw("Error: Invalid door coordinates.\n");
        return;
    }

    vector<vector<int>> frontier(MAX_HEIGHT * MAX_WIDTH, vector<int>(2, 0));
    vector<vector<vector<int>>> cameFrom(MAX_HEIGHT, vector<vector<int>>(MAX_WIDTH, vector<int>(2, -1)));

    int frontierIndex = 0;
    int frontierCount = 0;

    // 초기화
    cameFrom[start->y][start->x][0] = -9;
    cameFrom[start->y][start->x][1] = -9;

    addPositionYX(frontier, frontierCount, start->y, start->x);
    frontierCount++;

    while (frontierIndex < frontierCount) {
        int y = frontier[frontierIndex][0];
        int x = frontier[frontierIndex][1];

        frontierIndex++;

        if (y == end->y && x == end->x) {
            break;
        }

        if (frontierIndex < frontier.size()) {
            frontierCount = addNeighbors(frontier, frontierCount, cameFrom, y, x);
        }
    }

    int y = end->y;
    int x = end->x;

    while (y != start->y || x != start->x) {
        int tempY = y;

        if (tempY >= 0 && tempY < MAX_HEIGHT && x >= 0 && x < MAX_WIDTH) {
            y = cameFrom[tempY][x][0];
            x = cameFrom[tempY][x][1];
            mvprintw(y, x, "+");
        } else {
            cerr<<"Error: Pathfinding out of bounds."<<endl;
            break;
        }
    }
}
