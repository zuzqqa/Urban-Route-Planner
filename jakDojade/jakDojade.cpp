#include <iostream>

#include "Vector.h"
#include "String.h"
#include "Queue.h"
#include "Heap.h"
#include "HashMap1.h"

constexpr int dx[] = { 0, 1, 0, -1 };
constexpr int dy[] = { 1, 0, -1, 0 };

using namespace std;

struct shift {
    int i, j;
};

struct coord {
    int x, y;
};

struct Pair {
    coord location;
    int distance;
};

struct flight
{
    string_ destination;
    string_ source;
    int time;
};

bool inside_map(const int i, const int j, const int w, const int h) {
    return i >= 0 && j >= 0 && j < w && i < h;
}

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
}

int dijkstra(const int n, const int m, Vector<Vector<edge>>& edges, int start_index, int end_index)
{
    Heap min_heap;
    Vector<int> distances(n * m);

    for (int i = 0; i < n * m; i++) distances[i] = 1e9;

    distances[start_index] = 0;
    min_heap.insert({ start_index, 0 });

    while (!min_heap.is_empty())
    {
        edge n1 = min_heap.get_top();

        min_heap.print_heap();

        auto& neighbor = edges[n1.city];

        min_heap.delete_top();

        for (int j = 0; j < neighbor.get_size(); j++) {
            int edge_weight = neighbor[j].distance;
            int adj_node = neighbor[j].city;

            if (n1.distance + edge_weight < distances[adj_node])
            {
                distances[adj_node] = n1.distance + edge_weight;
                min_heap.insert({ adj_node, distances[adj_node] });
            }
        }
    }

    cout << "DYSTANS " << distances[end_index] << endl;
    return distances[end_index];
}

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

void get_city_name(const int n, const int m, const char* arr, Vector<int>& normal_array, HashMap_id& hash_id, HashMap_str& hash_city)
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
                            string_ city_name(name(n, m, arr, i1, j1));
                        	hash_id.insert(normal_array[i * m + j], city_name);

                            string_ city_name1(name(n, m, arr, i1, j1));
                            hash_city.insert(city_name, normal_array[i * m + j]);
                        } 
                    }
                }
            }
        }
    }
}

flight divide(Vector<Vector<edge>>& edges, string_ temp)
{
    int length = 0, buffer = 0;
    Vector<string_> f1;
    flight h;

    cout << "Dlugosc nazwy miasta: " << temp.str_size() << endl;
	for( int i = 0; i < temp.str_size(); i++)
	{
        if (temp[i] == ' ' || temp[i] == '\n') {
            cout << "subs: " << temp.substr(buffer, length - 1).get_str() << endl;
            f1.push(temp.substr(buffer, length));
            cout << length << endl;
            buffer = i + 1;
        	length = 0;
        }

		length++;
	}

    return { f1[0], f1[1], atoi(f1[2].get_str())};
}

void add_flight(flight f1, Vector<Vector<edge>>& edges, HashMap_id& hash_id, HashMap_str& hash_city)
{
   
    edge e1 = { hash_city.retrieve(f1.source), f1.time };
    edge e2 = { hash_city.retrieve(f1.destination), f1.time };

    edges[e2.city].push(e1);
    edges[e1.city].push(e2);

    return;
}

void get_queries(const int n, const int m, flight f1, Vector<Vector<edge>>& edges, HashMap_id& hash_id, HashMap_str& hash_city)
{
    int src = hash_city.retrieve(f1.source);
    cout << "Source: " << endl;
    int dest = hash_city.retrieve(f1.destination);
    cout << "Destination: " << endl;
    cout<<dijkstra(n, m, edges, src, dest);
}

int main()
{
    int n, m; char zn;
    Vector<Vector<edge>> edges;

    cin >> n >> m;

    HashMap_id hash_id;
    HashMap_str hash_city;

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

    bool are_there_roads = false;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i * m + j] == '*') {
                normal_array[i * m + j] = i * m + j;
            }
            else if (arr[i * m + j] == '#') {
                normal_array[i * m + j] = -1;
                are_there_roads = true;
            }
            else
            {
                normal_array[i * m + j] = -2;
            }
        }
    }

    get_city_name(n, m, arr, normal_array, hash_id, hash_city);


    for( int i = 0; i < m; i++)
    {
	    for( int j = 0; j < n; j++)
	    {
            if(arr[i*m + j] == '*')
            bfs(n, m, normal_array, edges, i, j);
	    }
    }

    int k = 0; // liczba polaczen lotniczych
    cin >> k;

    int a = 0;

    flight h;

    char* wiersz = new char[64];

    while (a < k && fgets(wiersz, 64, stdin)) {
        string_ a_string(wiersz);
        h = divide(edges, wiersz);
        add_flight(h, edges, hash_id, hash_city);
        a++;
    }

    a = 0;

    int z = 0; // liczba zapytan
    cin >> z;

    while (a <= z && fgets(wiersz, 64, stdin)) {
        string_ a_string(wiersz);
        h = divide(edges, wiersz);
        get_queries(n, m, h, edges, hash_id, hash_city);
        a++;
    }

}

