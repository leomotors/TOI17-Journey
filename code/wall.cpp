#include <bits/stdc++.h>
using namespace std;

char house[1002][1002];
bool isFlood[1002][1002]{false};

int R, C;

void flood(int i, int j) {
    if (isFlood[i][j])
        return;
    isFlood[i][j] = true;

    if (house[i][j] == 'X')
        return;

    if (i > 0 && house[i - 1][j] == '.')
        flood(i - 1, j);
    if (i <= R && house[i + 1][j] == '.')
        flood(i + 1, j);
    if (j > 0 && house[i][j - 1] == '.')
        flood(i, j - 1);
    if (j <= C && house[i][j + 1] == '.')
        flood(i, j + 1);
}

inline void getSurroundingFloods(int &co, int i, int j) {
    if (isFlood[i - 1][j])
        co++;
    if (isFlood[i + 1][j])
        co++;
    if (isFlood[i][j - 1])
        co++;
    if (isFlood[i][j + 1])
        co++;
}

int getWalls(int i, int j) {
    if (house[i][j] != 'X')
        return 0;

    house[i][j] = '.';

    int res = 0;
    getSurroundingFloods(res, i, j);
    res += getWalls(i - 1, j);
    res += getWalls(i + 1, j);
    res += getWalls(i, j - 1);
    res += getWalls(i, j + 1);

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;

    for (int i = 0; i < R; i++) {
        house[i][0] = '.';
        house[i][C + 1] = '.';
    }
    for (int j = 0; j < C; j++) {
        house[0][j] = '.';
        house[R + 1][j] = '.';
    }

    // * Input
    for (int i = 0; i < R; i++) {
        cin >> house[i] + 1;
        house[i][C + 1] = '.';
    }

    // * Flood
    for (int i = 0; i < R; i++) {
        flood(i, 0);
        flood(i, C + 1);
    }
    for (int j = 0; j < C; j++) {
        flood(0, j);
        flood(R + 1, j);
    }

    int maximumWall = 0;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            int currentWall = getWalls(i, j);
            maximumWall = max(maximumWall, currentWall);
        }
    }

    cout << maximumWall << "\n";
}
