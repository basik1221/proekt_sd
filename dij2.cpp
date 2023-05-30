#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <chrono>
#include <queue>

using namespace std;

vector<vector<int>> tworzenie_grafu(int n, int min_waga, int max_waga) {
    vector<vector<int>> macierz_sasiedztwa(n, vector<int>(n, 0));  // tworzenie macierzy sąsiedztwa jako zerowej macierzy n x n

    srand(time(NULL));  // generator liczb losowych

   
    vector<bool> odwiedzone(n, false); // stworzenie wektora z odwiedzonymi wierzchołkami

    
    int wezel0 = rand() % n;// wybór losowego wierzchołka początkowego
    odwiedzone[wezel0] = true;//wierzcholek odwiedzony

    // Tworzenie grafu
    for (int i = 0; i < n; i++) { //petla iterujaca po wszystkich wierzcholkach 
        if (!odwiedzone[i]) { //jesli wierzchlek nie zostal odwiedzony 
            
            vector<int> dostepnewierzcholki;
            for (int j = 0; j < n; j++) {
                if (odwiedzone[j]) {
                    dostepnewierzcholki.push_back(j);
                }
            }

            int wierzcholek = dostepnewierzcholki[rand() % dostepnewierzcholki.size()];// wybór losowego wierzchołka docelowego spośród poprzednio odwiedzonych wierzchołków

            
            int waga = rand() % (max_waga - min_waga + 1) + min_waga;// wygenerowanie losowej wagi

           
            macierz_sasiedztwa[i][wierzcholek] = waga; // ustawienie wartości w macierzy sąsiedztwa
            macierz_sasiedztwa[wierzcholek][i] = waga;

            odwiedzone[i] = true; //dodanie wierzcholka do odwiedzonych
        }
    }

    return macierz_sasiedztwa;
}

vector<int> dijkstra(const vector<vector<int>>& macierz_sasiedztwa, int wierzcholek0) {
    int n = macierz_sasiedztwa.size(); //pobranie wielkosci macierzy 
    vector<int> odleglosc(n, numeric_limits<int>::max()); //tworzenie wektora odleglosci
    vector<bool> odwiedzone(n, false); //tworzenie wektora z odiwedzonymi wierczholkami

    odleglosc[wierzcholek0] = 0;//przypisanie 0 do wartosci odleglosci poczatkowego wierzcholka

    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;// kolejka priorytetowa przechowująca wierzchołki do odwiedzenia
    pq.push(make_pair(odleglosc[wierzcholek0], wierzcholek0)); //dodanie odleglosci dla 0 wierzcholka 

    while (!pq.empty()) {  //dopoki kolejka nie jest pusta
        int u = pq.top().second; //pobranie wierzcholka o najwyzszym priorytetcie, najkortszej odleglosci
        pq.pop(); //usuniecie go z kolejki

        if (odwiedzone[u]) {
            continue;
        }

        odwiedzone[u] = true; //przypisanie wierczolka do odwiedzonych

        for (int v = 0; v < n; v++) {//itercja po wszystkich wierzcholkach
            if (macierz_sasiedztwa[u][v] > 0 && odleglosc[u] != numeric_limits<int>::max()) { //jesli polaczenie istnieje 
                int nowa_odleglosc = odleglosc[u] + macierz_sasiedztwa[u][v];//nowa odleglosc to suma aktualnej odleglosci i wagi pomiedzy dwoma wierzcholkami
                if (nowa_odleglosc < odleglosc[v]) { //jesli nowa odleglosc jest mniejsza dodanie jej do koljeki
                    odleglosc[v] = nowa_odleglosc;
                    pq.push(make_pair(odleglosc[v], v));
                }
            }
        }
    }

    return odleglosc;
}


int main() {
    auto start1 = std::chrono::high_resolution_clock::now();
    int n = 5000;  // liczba wierzcholkow w grafie
    int min_waga = 1;  // minimalna waga krawędzi
    int max_waga = 10;  // maksymalna waga krawędzi

    vector<vector<int>> graf = tworzenie_grafu(n, min_waga, max_waga);

    // Wyświetlanie macierzy sąsiedztwa
   // for (int i = 0; i < n; i++) {
    //    for (int j = 0; j < n; j++) {
    //        cout << graph[i][j] << " ";
    //    }
    //    cout << endl;
   // }
    auto end1 = std::chrono::high_resolution_clock::now();
    int wierzcholek0 = 0;  // Wierzchołek początkowy
    auto start2 = std::chrono::high_resolution_clock::now();

    vector<int> distances = dijkstra(graf, wierzcholek0);

    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    // Wyświetlanie odległości od wierzchołka początkowego do wszystkich innych wierzchołków
    for (int i = 0; i < n; i++) {
        cout << "Odleglosc od wierzcholka " << wierzcholek0 << " do " << i << ": " << distances[i] << endl;
    }
    cout << "czas wykonywania funkcji dijkstry: " << duration2.count() << endl;
    cout << "czas tworzenia grafu: " << duration1.count() << endl;
    return 0;
}
