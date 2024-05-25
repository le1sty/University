#include "graph.hpp"
#include "algorithms.hpp"
#include "queue.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <iomanip>

const int INF = std::numeric_limits<int>::max();

Graph::Graph(int n) : n(n) {
    graph = new int* [n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
        for (int j = 0; j < n; j++) {
            graph[i][j] = INF;
        }
    }
}

Graph::~Graph() {
    if (graph != nullptr) {
        for (int i = 0; i < n; i++) {
            delete[] graph[i];
        }
        delete[] graph;
    }
}


void Graph::inputGraph() {
    for (int i = 0; i < n; ++i) {
        std::cout << "Ребра из вершины " << i + 1 << ": ";
        for (int j = 0; j < n; ++j) {
            std::string s;
            while (true) {
                try {
                    std::cin >> s;
                    if (s == "e") {
                        graph[i][j] = INF;
                    }
                    else {
                        int weight = std::stoi(s);
                        if (i == j || weight == 0) {
                            graph[i][j] = INF;
                        }
                        else {
                            graph[i][j] = weight;
                        }
                    }
                    break;
                }
                catch (const std::exception& e) {
                    std::cout << "Некорректный ввод. Вес ребра должен быть положительным числом больше нуля или 'e', если ребра нет.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (graph[i][j] != graph[j][i]) {
                clearGraph();
                throw std::runtime_error("Граф не является симметричным. Граф удален.");
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (graph[i][j] != INF) {
                graph[j][i] = graph[i][j];
            }
        }
    }
    std::cout << "Граф создан.\n";
}

void Graph::clearGraph() {
    for (int i = 0; i < n; ++i) {
        delete[] graph[i];
    }
    delete[] graph;
    graph = nullptr;
}

void Graph::addNode() {
    if (graph == nullptr) {
        throw std::runtime_error("Граф не инициализирован. Сначала введите граф (опция 1).");
    }
    int** newGraph = new int* [n + 1];
    for (int i = 0; i < n + 1; i++) {
        newGraph[i] = new int[n + 1];
        for (int j = 0; j < n + 1; j++) {
            if (i < n && j < n) {
                newGraph[i][j] = graph[i][j];
            }
            else {
                newGraph[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    graph = newGraph;
    n++;
    std::cout << "Вершина добавлена.\n";
}

void Graph::removeNode() {
    if (graph == nullptr) {
        throw std::runtime_error("Граф не инициализирован. Сначала введите граф (опция 1).");
    }
    std::cout << "Введите номер вершины, которую хотите удалить или -1 чтобы выбрать другой алгоритм: ";
    int node;
    std::cin >> node;
    if (node == -1) {
        return;
    }
    if (node <= 0 || node > n || !std::cin) {
        throw std::runtime_error("Некорректный ввод!");
    }
    node--; 
    int** newGraph = new int* [n - 1];
    for (int i = 0, ni = 0; i < n; i++) {
        if (i == node) continue;
        newGraph[ni] = new int[n - 1];
        for (int j = 0, nj = 0; j < n; j++) {
            if (j == node) continue;
            newGraph[ni][nj] = graph[i][j];
            nj++;
        }
        ni++;
    }

    for (int i = 0; i < n; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    graph = newGraph;
    n--;
    std::cout << "Вершина удалена.\n";
}

void Graph::addEdge() {
    if (graph == nullptr) {
        throw std::runtime_error("Граф не инициализирован. Сначала введите граф (опция 1).");
    }
    int start, end, weight;
    std::cout << "Введите из какой вершины провести ребро, или -1 чтобы выбрать другой алгоритм: ";
    std::cin >> start;
    if (start == -1) {
        return;
    }
    if (start <= 0 || start > n || !std::cin) {
        throw std::runtime_error("Некорректный ввод! Вершина должна быть в диапазоне от 1 до " + std::to_string(n));
    }
    std::cout << "Введите в какую вершину провести ребро: ";
    std::cin >> end;
    if (end <= 0 || end > n || !std::cin) {
        throw std::runtime_error("Некорректный ввод! Вершина должна быть в диапазоне от 1 до " + std::to_string(n));
    }
    std::cout << "Введите вес ребра: ";
    std::cin >> weight;
    if (!std::cin) {
        throw std::runtime_error("Некорректный ввод! Вес ребра должен быть целым числом.");
    }

    if (start == end) {
        weight = 0;
    }

    graph[start - 1][end - 1] = weight;
    graph[end - 1][start - 1] = weight;
    std::cout << "Ребро создано.\n";

}


void Graph::removeEdge() {
    if (graph == nullptr) {
        throw std::runtime_error("Граф не инициализирован. Сначала введите граф (опция 1).");
    }
    int start, end;
    std::cout << "Введите вершину, из которой хотите удалить ребро, или -1 чтобы выбрать другой алгоритм: ";
    std::cin >> start;
    if (start == -1) {
        return ;
    }
    if (start <= 0 || start > n || !std::cin) {
        throw std::runtime_error("Некорректный ввод! Вершина должна быть в диапазоне от 1 до " + std::to_string(n));
    }
    std::cout << "Введите вершину, в которую ведет ребро, которое хотите удалмть: ";
    std::cin >> end;
    if (end <= 0 || end > n || !std::cin) {
        throw std::runtime_error("Некорректный ввод! Вершина должна быть в диапазоне от 1 до " + std::to_string(n));
    }
    graph[start - 1][end - 1] = INF;
    graph[end - 1][start - 1] = INF;
    std::cout << "Ребро удалена. \n";

}

void Graph::findEdges() {
    if (graph == nullptr) {
        throw std::runtime_error("Граф не инициализирован. Сначала введите граф (опция 1).");
    }
    int weight;
    std::cout << "Введите вес искомого ребра, или -1 чтобы выбрать другой алгоритм: ";
    std::cin >> weight;
    if (weight == -1) {
        return;
    }
    if (weight <= 0) {
        throw std::runtime_error("Некорректный ввод! Ребро должно иметь вес больше 0");
    }

    bool hasEdges = false;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (graph[i][j] == weight) {
                hasEdges = true;
                std::cout << "Ребро весом " << weight << " есть между вершинами " << i + 1 << " и " << j + 1 << std::endl;
            }
        }
    }

    if (!hasEdges) {
        std::cout << "Ребра весом " << weight << " не существует" << std::endl;
    }
}

void Graph::printGraph() {
    if (graph == nullptr) {
        throw std::runtime_error("Граф не инициализирован. Сначала введите граф (опция 1).");
    }
    std::cout << "Матрица смежности графа:\n";

    std::cout << "    ";
    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(5) << i + 1;
    }
    std::cout << "\n";

    std::cout << "    ";
    for (int i = 0; i < n; ++i) {
        std::cout << "-----";
    }
    std::cout << "\n";

    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(2) << i + 1 << " |";
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] == INF) {
                std::cout << std::setw(5) << "0";
            }
            else {
                std::cout << std::setw(5) << graph[i][j];
            }
        }
        std::cout << "\n";
    }
}

bool Graph::isLinked() {
    if (graph == nullptr) {
        throw std::runtime_error("Граф не инициализирован. Сначала введите граф (опция 1).");
    }

    int start, end;
    std::cout << "Введите одну вершину ребра: ";
    std::cin >> start;
    std::cout << "Введите вторую вершину ребра: ";
    std::cin >> end;

    if (start <= 0 || start > n || end <= 0 || end > n) {
        throw std::runtime_error("Некорректные вершины.");
    }

    if (graph[start - 1][end - 1] != INF) {
        std::cout << "Вершины " << start << " и " << end << " связаны.\n";
        return true;
    }
    else {
        std::cout << "Вершины " << start << " и " << end << " не связаны.\n";
        return false;
    }
}

bool Graph::hasNegativeEdges() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] < 0) {
                return true;
            }
        }
    }
    return false;
}

int Graph::getNodeCount() const {
    return n;
}


void Graph::runDijkstra(int start) {
    if (graph == nullptr) {
        throw std::runtime_error("Граф не инициализирован. Сначала введите граф (опция 1).");
    }
    dijkstra((const int**)graph, start, n);
}


int Graph::runGetTreeDiameter() {
    if (graph == nullptr) {
        throw std::runtime_error("Граф не инициализирован. Сначала введите граф (опция 1).");
    }
    getTreeDiameter((const int**) graph, n);
}

void Graph::runWaveAlgorithm(int start, int end) {
    if (graph == nullptr) {
        throw std::runtime_error("Граф не инициализирован. Сначала введите граф (опция 1).");
    }
    waveAlgorithm((const int**)graph, n, start, end);
}
