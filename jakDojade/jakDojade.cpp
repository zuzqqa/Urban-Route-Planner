#include <iostream>

#include "Vector.h"
#include "String.h"
#include "Queue.h"

using namespace std;

struct shift {
    int i, j;
};

struct edge {
    int city;
    int distance;
};

struct coord {
    int x, y;
};

struct Pair {
    coord location;
    int distance;
};

// :D
void bfs(const int n, const int m, const int* arr, Vector<Vector<edge>>& edges, const int i, const int j) {
    Vector explored(m * n, false);
  
    const int startCity = arr[i * m + j];

    Queue<Pair> q;

    q.push({{i, j}, 0});
    explored[i * m + j] = true;

    while (!q.empty()) {
        auto [location, distance] = q.front();
        auto [x, y] = location;

        // town
        if (arr[x * m + y] >= 0 && arr[x * m + y] != startCity) {
            edges[startCity].push({ arr[x * m + y], distance });
            continue;
        }

        if (arr[(x - 1)]){
            //czy to pole jest przejezdne czyli != -2 i jestesmy na mapie q.push({{x -1 lub cos tam no,y}}, distance + 1) explored od nowych kordow = true;
        }

    }

};

shift getName() {
    shift shifts[] = {
       {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1} };

    // czy jestem na mapie

    // isalNum

    // w prawo i w lewo  i zapisuje nazwe, memcpy
}

int main()
{
    int n, m, c;
    Vector<String> vec;
    cin >> n >> m;

    char* arr = new char[n * m];

    int* arr1 = new int[n * m];

    shift shifts[] = {
       {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1} };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i * m + j] = getchar();
        }
    }

    bool areThereRoads = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i * m + j] == '*') {
                /// <summary>
                /// /
                /// </summary>
                /// <returns></returns>
                arr1[i * m + j] = i * m + j;
            }
            else if (arr[i * m + j] == '.') arr1[i * m + j] = -2;
            else if (arr[i * m + j] == '#') {
                arr1[i * m + j] = -1;
                areThereRoads = true;
            }
        }
    }
}

