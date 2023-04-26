#include <iostream>

#include "Vector.h"
#include "String.h"
#include "Queue.h"

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

bool inside_map(const int i, const int j, const int w, const int h) {
    return i >= 0 && j >= 0 && j < w && i < h;
}

// :D
void bfs(const int n, const int m, const Vector<int>& arr, Vector<Vector<edge>>& edges, const int i, const int j) {
    Vector<bool> explored(n * m);

    for(int i1 = 0; i1 < n; i1++)
    {
	    for(int j1 = 0; j1 < m; j1++)
	    {
            explored[i1 * m + j1] = false;
	    }
    }

    const int start_city = arr[i * m + j];

    edges.reserve(m * n);

    queue<Pair> q;

    q.push({{i, j}, 0});
    explored[i * n + j] = true;

    Vector<edge> empty;

    for (int o = 0; o < m * n; o++) {
        edges.push(Vector<edge>());
    }

    while (!q.empty()) {
        auto [location, distance] = q.front();
        auto [x, y] = location;

        q.pop();

        // town
        if (arr[x * m + y] >= 0 && arr[x * m + y] != start_city) {
            cout << "City found" << endl;
            edges[start_city].push({ arr[x * m + y], distance });
            continue;
        }

        for (int k = 0; k < 4; k++) {
            const int new_i = x + dx[k];
            const int new_j = y + dy[k];
            if (!inside_map(new_i, new_j, n, m)) continue;
            if (arr[new_i * m + new_j] == -2) continue;
            if (explored[new_i * m + new_j]) continue;

            q.push({ {new_i, new_j}, distance + 1 });
            explored[new_i * m + new_j] = true;
        }
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
                           string_ city_name = name(n, m, arr, i1, j1);
                        } 
                    }
                }
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

    Vector<int> normal_array(n * m);

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
                normal_array[i * m + j] = i * m + j;
            }
            else if (arr[i * m + j] == '#') {

	            arr1[i * m + j] = -1;
                normal_array[i * m + j] = -1;
                are_there_roads = true;
            }
            else
            {
                arr1[i * m + j] = -2;
                normal_array[i * m + j] = -2;
            }
        }
    }

    cout << arr1[3 * m + 8] << endl;
   for (int i = 0; i < n; i++) {
   		for (int j = 0; j < m; j++) {
   			cout << normal_array[i * m + j] << " ";
   		}
   		cout << endl;
   }

    for( int i = 0; i < m; i++)
    {
	    for( int j = 0; j < n; j++)
	    {
            if(arr[i*m + j] == '*')
            bfs(n, m, normal_array, edges, i, j);
	    }
    }

    for (int i = 0; i < edges.get_size(); i++) {
        if (edges[i].get_empty()) continue;

        cout << "City : " << i << endl;
        auto& neighbor = edges[i];

        for (int j = 0; j < neighbor.get_size(); j++) {
            cout << neighbor[j].city << " " << neighbor[j].distance << ", ";
        }

        cout << endl;
    }
}

