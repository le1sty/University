#include "graph.hpp"
#include <iostream>
#include <limits>

const int INF = std::numeric_limits<int>::max();

void printMenu() {
    std::cout << "---------------------------------\n";
    std::cout << "Меню:\n";
    std::cout << "1.  Ввести граф\n";
    std::cout << "2.  Вывести граф\n";
    std::cout << "3.  Добавить вершину\n";
    std::cout << "4.  Удалить вершину\n";
    std::cout << "5.  Добавить ребро\n";
    std::cout << "6.  Удалить ребро\n";
    std::cout << "7.  Проверить наличие ребра\n";
    std::cout << "8.  Поиск ребра по весу\n";
    std::cout << "9.  Определить диаметр дерева\n";
    std::cout << "10. Запустить алгоритм Дейкстры\n";
    std::cout << "11. Запустить волновой алгоритм\n";
    std::cout << "0.  Выйти\n";
    std::cout << "\n";
    std::cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Ru");
    Graph* graph = nullptr;
    bool running = true;

    while (running) {

        printMenu();
        int choice;
        std::cin >> choice;
        std::cout << "---------------------------------\n";

        try {
            switch (choice) {
            case 1: {
                int n;
                while (true) {
                    std::cout << "Введите количество вершин графа: ";
                    std::cin >> n;
                    if (n < 0 || !std::cin) {
                        std::cout << "Количество вершин должно быть положительным числом!\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else {
                        break;
                    }
                }
                if (graph != nullptr) {
                    delete graph;
                }
                graph = new Graph(n);
                graph->inputGraph();
                break;
            }
            case 2:
                if (graph == nullptr) {
                    std::cout << "Сначала введите граф (опция 1).\n";
                }
                else {
                    graph->printGraph();
                }
                break;
            case 3:
                if (graph == nullptr) {
                    std::cout << "Сначала введите граф (опция 1).\n";
                }
                else {
                    graph->addNode();
                }
                break;
            case 4:
                if (graph == nullptr) {
                    std::cout << "Сначала введите граф (опция 1).\n";
                }
                else {
                    graph->removeNode();
                }
                break;
            case 5:
                if (graph == nullptr) {
                    std::cout << "Сначала введите граф (опция 1).\n";
                }
                else {
                    graph->addEdge();
                }
                break;
            case 6:
                if (graph == nullptr) {
                    std::cout << "Сначала введите граф (опция 1).\n";
                }
                else {
                    graph->removeEdge();
                }
                break;
            case 7:
                if (graph == nullptr) {
                    std::cout << "Сначала введите граф (опция 1).\n";
                }
                else {
                    graph->isLinked();
                }
                break;
            case 8:
                if (graph == nullptr) {
                    std::cout << "Сначала введите граф (опция 1).\n";
                }
                else {
                    graph->findEdges();
                }
                break;
            case 9:
                if (graph == nullptr) {
                    std::cout << "Сначала введите граф (опция 1).\n";
                }
                else {
                    try {
                        int diameter = graph->runGetTreeDiameter();
                        std::cout << "Диаметр дерева: " << diameter << std::endl;
                    }
                    catch (const std::runtime_error& e) {
                        std::cout << e.what() << std::endl;
                    }
                }
                break;
            case 10:
                if (graph == nullptr) {
                    std::cout << "Сначала введите граф (опция 1).\n";
                }
                else {
                    int start;
                    std::cout << "Введите начальную вершину поиска: ";
                    std::cin >> start;
                    if (start <= 0 || start > graph->getNodeCount() || !std::cin) {
                        std::cout << "Некорректный ввод!\n";
                    }
                    else {
                        graph->runDijkstra(start);
                    }
                }
                break;
            case 11:
                if (graph == nullptr) {
                    std::cout << "Сначала введите граф (опция 1).\n";
                }
                else {
                    int start, end;
                    std::cout << "Введите начальную вершину поиска: ";
                    std::cin >> start;
                    std::cout << "Введите конечную вершину поиска: ";
                    std::cin >> end;
                    if (start <= 0 || start > graph->getNodeCount() || end <= 0 || end > graph->getNodeCount() || !std::cin) {
                        std::cout << "Некорректный ввод!\n";
                    }
                    else {
                        graph->runWaveAlgorithm(start, end);
                    }
                }
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Некорректный выбор. Попробуйте снова.\n";
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if (graph != nullptr) {
        delete graph; 
    }

    return 0;
}
