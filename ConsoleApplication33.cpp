#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
const int INF = std::numeric_limits<int>::max();

struct Node {
    int odl = INF;
    std::vector<std::pair<int, int>> pol;
};

void dijkstra(int start, std::vector<Node>& wezel) {
    int dystans, a, b;
    wezel[start].odl = 0;

    std::set<std::pair<int, int>> krawedzie; //odleglosc od źródła, ( -> b)

    // dodanie wszystkich wag krawędzi oraz numery wierzchołków docelowych
    for (int i = 0; i < wezel[start].pol.size(); i++)
        krawedzie.insert({ wezel[start].pol[i].second, wezel[start].pol[i].first });

    while (!krawedzie.empty()) // dopóki w secie są jeszcze jakieś krawędzie do analizy
    {
        // pobranie najkrótszej ścieżki oraz wierzchołek, do którego ona prowadzi
        dystans = krawedzie.begin()->first; // dystans
        b = krawedzie.begin()->second;      // wierzchołek

        wezel[b].odl = std::min(dystans, wezel[b].odl); // ustawienie długości najkrótszej ścieżki

        // usunięcie krawędzi z seta
        krawedzie.erase(krawedzie.begin());

        for (int i = 0; i < wezel[b].pol.size(); i++) // przeglądam wszysktie połączenia z wierzchołka b
        {
            // biorę tylko te połączenia z wierzchołkami, do których odleglosć jest równa nieskończonosć
            if (wezel[wezel[b].pol[i].first].odl == INF)
                krawedzie.insert(std::make_pair(wezel[b].pol[i].second + dystans, wezel[b].pol[i].first));
        }
    }
}

void wyswietlGraf(const std::vector<Node>& wezel) {
    for (int i = 0; i < wezel.size(); i++) {
        std::cout << "Wierzcholek " << i << ": ";
        for (const auto& polaczenie : wezel[i].pol) {
            std::cout << "(" << polaczenie.first << ", " << polaczenie.second << ") ";
        }
        std::cout << std::endl;
    }
}

int main() {
    auto start1 = std::chrono::high_resolution_clock::now();
    int n = 10; // Liczba wierzchołków

    // Tworzenie wektora wierzchołków
    std::vector<Node> wezel(n);

    std::srand(std::time(0)); // Inicjalizacja generatora liczb pseudolosowych

    for (int i = 0; i < n; i++) {
        int liczbaKrawedzi = std::rand() % (n - 3) + 1;
        for (int j = 0; j < liczbaKrawedzi; j++) {
            int target = i;
            while (target == i) {
                target = std::rand() % n;
            }
            int weight = std::rand() % 10 + 1;
            wezel[i].pol.push_back({ target, weight });
            wezel[target].pol.push_back({ i, weight }); // Dodanie krawędzi w drugą stronę
        }
    }

    int startVertex = 0; // Wierzchołek źródłowy
    auto end1 = std::chrono::high_resolution_clock::now();
    //wyswietlGraf(wezel);
    auto start2 = std::chrono::high_resolution_clock::now();
    dijkstra(startVertex, wezel);
    auto end2 = std::chrono::high_resolution_clock::now();
    // Wyświetlanie odległości od źródła do wszystkich wierzchołków
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    for (int i = 0; i < n; ++i) {
        std::cout << "Odleglosc od " << startVertex << " do " << i << ": " << wezel[i].odl << std::endl;
    }
    cout << "czas tworzenia grafu: " << duration1.count() << endl;
    cout << "czas wykonywania funkcji dijkstry: " << duration2.count() << endl;

    return 0;
}
