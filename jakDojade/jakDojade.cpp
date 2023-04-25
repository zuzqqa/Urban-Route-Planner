#include <iostream>

#include "Vector.h"
#include "String.h"
#include "Queue.h"

constexpr int shift_size = 3;
constexpr int dx[] = { 0, 1, 0, -1 };
constexpr int dy[] = { 1, 0, -1, 0 };

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
  
    const int start_city = arr[i * m + j];

    queue<Pair> q;

    q.push({{i, j}, 0});
    explored[i * m + j] = true;

    while (!q.empty()) {
        auto [location, distance] = q.front();
        auto [x, y] = location;

        // town
        if (arr[x * m + y] >= 0 && arr[x * m + y] != start_city) {
            edges[start_city].push({ arr[x * m + y], distance });
            continue;
        }

        for (int i = 0; i < shift_size; i++)
        {
            if ((dy[i] >= 0 && dy[i] < m && dx[i] >= 0 && dx[i] < n) && arr[(x + dx[i]) * m + (y + dy[i])] != -2)
            {
                q.push({ {x + dx[i], y + dy[i]}, distance + 1 });
                explored[(x + dx[i]) * m + (y + dy[i])] = true;
            }
        }
    }

    for( int i = 0; i < q.size(); i++)
    {
        cout << q[i].distance << " " << q[i].location.x << q[i].location.y;
    }

    return;
};

string_ name(const int n, const int m, const char* arr, const int i, int j)
{
    string_ city_name;

    int j1 = j;

    if( j - 1 >= 0 && isalnum(arr[i * m + (j - 1)]))
    {
        j--;
        while (j >= 0 && isalnum(arr[i * m + j]))
        {
            city_name.append(arr[i * m + j]);
            j--;
        }
        city_name.flip();
    }

    city_name.append(arr[i * m + j1]);

    if(j1 + 1 < n && isalnum(arr[i * m + j1 + 1])){
        j1++;
        while (j1 < n && isalnum(arr[i * m + j1]))
        {
            city_name.append(arr[i * m + j1]);
            j1++;
        }
    }

    return city_name;
}

void get_city_name(const int n, const int m, const char* arr)
{
    string_ city_name;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i * m + j] == '*')
            {
                for (int i1 = i - 1; i1 <= i + 1; i1++)
                {
                    for (int j1 = j - 1; j1 <= j + 1; j1++)
                    {
                        if ((j1 >= 0 && j1 < m && i1 >= 0 && i1 < n) && isalnum(arr[i1 * m + j1]))
                        {
                           city_name = name(n, m, arr, i1, j1);
                        }
                    }
                }
                cout << city_name.get_str() << endl;
            }
        }
    }
}

int main()
{
    int n, m, c; char zn;
    Vector<Vector<edge>> edges;

    cin >> n >> m;

    const auto arr = new char[n * m];

    const auto arr1 = new int[n * m];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            zn = getchar();
            if (zn != '\n') {
                arr[i * m + j] = zn;
            }
            else j--;
        }
    }

    get_city_name(n, m, arr);

    bool are_there_roads = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i * m + j] == '*') {
                arr1[i * m + j] = i * m + j;
            }
            else if (arr[i * m + j] == '#') {

	            arr1[i * m + j] = -1;
                are_there_roads = true;
            }
            else
            {
                arr1[i * m + j] = -2;
            }
        }
    }

   for (int i = 0; i < n; i++) {
   		for (int j = 0; j < m; j++) {
            bfs(n, m, arr1, edges, i, j);
   			cout << arr1[i * m + j];
   		}
   		cout << endl;
   }
}

