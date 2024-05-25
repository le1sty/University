#include "algorithms.hpp"
#include "queue.hpp"
#include <iostream>
#include <limits>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

void dijkstra(const int** graph, int start, int n) {
    int* dist = new int[n];
    int* parent = new int[n];
    bool* visited = new bool[n];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = false;
    }

    dist[start - 1] = 0;

    for (int i = 0; i < n - 1; i++) {
        int minDist = INF, u = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] <= minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) {
            break; 
        }

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != INF && !visited[v] && dist[u] != INF) {
                int newDist = dist[u] + graph[u][v];

                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    parent[v] = u;
                }
            }
        }
    }

    std::cout << "Кратчайший путь от вершины " << start << ":\n";
    for (int i = 0; i < n; i++) {
        if (i == start - 1) {
            std::cout << i + 1 << ": нет пути от вершины " << start << " до вершины " << i + 1 << "\n";
        }
        else if (dist[i] == INF) {
            std::cout << i + 1 << ": нет пути от вершины " << start << " до вершины " << i + 1 << "\n";
        }
        else {
            std::cout << i + 1 << ": " << dist[i] << "\n";
        }
    }

    delete[] dist;
    delete[] parent;
    delete[] visited;
}
 
int getTreeDiameter(const int** graph, int n) {
    int maxDiameter = 0;

    for (int i = 0; i < n; ++i) {
        int* dist = new int[n];
        int* parent = new int[n];
        bool* visited = new bool[n];

        for (int j = 0; j < n; ++j) {
            dist[j] = INF;
            parent[j] = -1;
            visited[j] = false;
        }

        dist[i] = 0;

        for (int j = 0; j < n - 1; ++j) {
            int minDist = INF, u = -1;

            for (int k = 0; k < n; ++k) {
                if (!visited[k] && dist[k] <= minDist) {
                    minDist = dist[k];
                    u = k;
                }
            }

            if (u == -1) {
                break;
            }

            visited[u] = true;

            for (int v = 0; v < n; ++v) {
                if (graph[u][v] != INF && !visited[v] && dist[u] != INF) {
                    int newDist = dist[u] + graph[u][v];

                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        parent[v] = u;
                    }
                }
            }
        }

        int longestPath = 0;
        for (int j = 0; j < n; ++j) {
            if (dist[j] > longestPath) {
                longestPath = dist[j];
            }
        }

        if (longestPath > maxDiameter) {
            maxDiameter = longestPath;
        }

        delete[] dist;
        delete[] parent;
        delete[] visited;
    }

    return maxDiameter;
}

void waveAlgorithm(const int** graph, int n, int start, int end) {
    start--;
    end--;

    int* dist = new int[n];
    bool* visited = new bool[n];
    int* prev = new int[n];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
        prev[i] = -1;
    }

    dist[start] = 0;
    MyQueue q(n);
    q.push({ start, 0 });
    visited[start] = true;

    while (!q.isEmpty()) {
        Node node = q.pop();
        int v = node.vertex;

        for (int u = 0; u < n; u++) {
            if (graph[v][u] != INF && !visited[u]) {
                visited[u] = true;
                dist[u] = dist[v] + graph[v][u];
                prev[u] = v;
                q.push({ u, node.level + 1 });

                if (u == end) {
                    break;
                }
            }
        }
    }

    if (dist[end] == INF) {
        std::cout << "Путь не найден\n";
        delete[] dist;
        delete[] visited;
        delete[] prev;
        return;
    }

    int* path = new int[n];
    int pathLen = 0;
    for (int at = end; at != -1; at = prev[at]) {
        path[pathLen++] = at;
    }

    std::cout << "Кратчайший путь: ";
    for (int i = pathLen - 1; i >= 0; i--) {
        std::cout << path[i] + 1 << " ";
    }
    std::cout << "\nДлина пути: " << dist[end] << std::endl;

    delete[] dist;
    delete[] visited;
    delete[] prev;
    delete[] path;
}