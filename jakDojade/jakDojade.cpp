#include <iostream>

#include "Vector.h"
#include "String.h"
#include "Queue.h"
#include "Heap.h"
#include "HashMap1.h"
#include <chrono>

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

struct JiI
{
    int i;
    int j;
};

struct flight
{
    string_ source;
    string_ destination;
    int time;
};

bool inside_map(const int i, const int j, const int w, const int h) {
    return i >= 0 && j >= 0 && j < h && i < w ;
}

void bfs(const int n, const int m, const Vector<int>& arr, Vector<Vector<edge>>& edges, const int i, const int j) {
    Vector<bool> explored(n * m, false);

    const int start_city = arr[i * m + j];

    queue<Pair> q;
    q.push({{i, j}, 0});
    explored[i * m + j] = true;

    constexpr int dx[] = { 0, 1, 0, -1 };
    constexpr int dy[] = { 1, 0, -1, 0 };

    while (!q.empty()) {
        auto [location, distance] = q.front();
        q.pop();
        const auto [x, y] = location;
        const int current_city = arr[x * m + y];
   
        // town
        if (current_city >= 0 && current_city != start_city) {
            edges[start_city].push({ current_city, distance });
            continue;
        }

        for (int k = 0; k < 4; k++) {
            const int new_i = x + dx[k];
            const int new_j = y + dy[k];

            if (!inside_map(new_i, new_j, n, m) || arr[new_i * m + new_j] == -2 || explored[new_i * m + new_j]) continue;
            q.push({ {new_i, new_j}, distance + 1 });
            explored[new_i * m + new_j] = true;
        }
    }

    return;
}

void dijkstra(const int n, const int m, Vector<Vector<edge>>& edges, int start_index, int end_index, bool path1, HashMap_id& hash_id, HashMap_str& hash_city)
{

    Heap min_heap;

    Vector<int> distances(n * m, 1e9);

	Vector<int> previous( n * m);

    distances[start_index] = 0;
    min_heap.insert({ start_index, 0 });

    while (!min_heap.is_empty())
    {
        edge n1 = min_heap.get_top();

        auto& neighbor = edges[n1.city];

        min_heap.delete_top();

        for (int j = 0; j < neighbor.get_size(); j++) {
            int edge_weight = neighbor[j].distance;
            int adj_node = neighbor[j].city;

            if (n1.distance + edge_weight < distances[adj_node])
            {
                distances[adj_node] = n1.distance + edge_weight;
                previous[adj_node] = (n1.city);
                min_heap.insert({ adj_node, distances[adj_node] });
            }
        }
    }


    if( path1 == false )
    {
        cout << distances[end_index] << endl;
    }
    else
    {
        cout << distances[end_index] << " ";

        Vector<int> path;
        int current_node = end_index;

        while (current_node != start_index)
        {
            path.push(current_node);
            current_node = previous[current_node];
        }

        path.push(start_index); 
        path.reverse();

        for (int i = 0; i < path.get_size(); i++)
        {
        	if( path[i] != start_index && path[i] != end_index ) 
                cout << hash_id.retrieve(path[i]).get_str()<< " ";
        }
        cout << endl;
    }
    
    return;
}

string_ name(const int m, const int n, Vector<char>& arr, const int i, int j)
{
    string_ city_name;

    int j1 = j;

    if( j - 1 >= 0 && isalnum(arr[i * n + (j - 1)]))
    {
        j--;
        while (j >= 0 && isalnum(arr[i * n + j]))
        {
            city_name.append(arr[i * n + j]);
            j--;
        }
        city_name.flip();
    }

    city_name.append(arr[i * n + j1]);

    if(j1 + 1 < n && isalnum(arr[i * n + j1 + 1])){
        j1++;
        while (j1 < n && isalnum(arr[i * n + j1]))
        {
            city_name.append(arr[i * n + j1]);
            j1++;
        }
    }

    return city_name;
}

void get_city_name(const int n, const int m, Vector<char>& arr, Vector<int>& normal_array, HashMap_id& hash_id, HashMap_str& hash_city, Vector<JiI>& cities)
{
	const int cities_size = cities.get_size();

    for (int i = 0; i < cities_size; i++)
    {
	    const int city_i = cities[i].i;
        const int city_j = cities[i].j;

        const int start_index = city_i * m + city_j;
	    const int normal_array_value = normal_array[start_index];

        for (int i1 = city_i - 1; i1 <= city_i + 1; i1++)
        {
            for (int j1 = city_j - 1; j1 <= city_j + 1; j1++)
            {
                if ((j1 >= 0 && j1 < m && i1 >= 0 && i1 < n) && isalnum(arr[i1 * m + j1]))
                {
                    string_ city_name = name(n, m, arr, i1, j1);

                    hash_id.insert(normal_array_value, city_name);
                    hash_city.insert(city_name, normal_array_value);
                    break;
                }
            }
        }
    };
}

flight divide(Vector<Vector<edge>>& edges, string_ temp)
{
    int length = 0, buffer = 0;
    Vector<string_> f1;
    flight h;
    int k = 0;

	for( int i = 0; i < temp.str_size(); i++)
	{
        if (temp[i] == ' ') {
            length = i - buffer;
            f1.push(temp.substr(buffer, length));
            buffer = buffer + length + 1;
        	length = 0;
            k++;
        }
        if (k == 2)
        {
            length = temp.str_size() - buffer;
            f1.push(temp.substr(buffer, length));
            break;
        }
        
		length++;
	}

    return { f1[0], f1[1], atoi(f1[2].get_str())};
}

void add_flight(flight f1, Vector<Vector<edge>>& edges, HashMap_id& hash_id, HashMap_str& hash_city)
{
	const edge e2 = { hash_city.retrieve(f1.destination), f1.time };

    edges[hash_city.retrieve(f1.source)].push(e2);

    return;
}

void get_queries(const int n, const int m, flight f1, Vector<Vector<edge>>& edges, HashMap_id& hash_id, HashMap_str& hash_city)
{
	const int src = hash_city.retrieve(f1.source);

	const int dest = hash_city.retrieve(f1.destination);

	dijkstra(n, m, edges, src, dest, f1.time, hash_id, hash_city);

}

int main()
{
    int n, m; char zn;

    cin >> m >> n;

    Vector<Vector<edge>> edges(m * n, Vector<edge>());

    HashMap_id hash_id;
    HashMap_str hash_city;

    Vector<JiI> cities;

    Vector<char> arr(m * n);

    Vector<int> normal_array(m * n);

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
                cities.push({i, j});
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


    get_city_name(n, m, arr, normal_array, hash_id, hash_city, cities);

    auto start_time = chrono::high_resolution_clock::now();

    for( int i = 0; i < cities.get_size(); i++)
    {
        bfs(n, m, normal_array, edges, cities[i].i, cities[i].j);
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto result = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    cout << "ile: " << result << endl;

    int k = 0;
    cin >> k;

    int a = 0;

    flight h;

    char* wiersz = new char[64];
    fgets(wiersz, 64, stdin);

    if (k == 0) {}
    else
    {
        while ( a < k) {
            fgets(wiersz, 64, stdin);
            h = divide(edges, wiersz);
            add_flight(h, edges, hash_id, hash_city);
            a++;
        }
    }
   

    a = 0;

    int z = 0; // liczba zapytan
    cin >> z;

    fgets(wiersz, 64, stdin);

    while (a < z) {
        fgets(wiersz, 64, stdin);
        h = divide(edges, wiersz);
        get_queries(n, m, h, edges, hash_id, hash_city);
        a++;
    }
}

