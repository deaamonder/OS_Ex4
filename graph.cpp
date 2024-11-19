#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unistd.h>
#include <mutex>
#include <algorithm>
#include <memory>

using namespace std;


class Graph {
public:
    int vertices;
    vector<vector<int>> adjList;

    Graph(int v) : vertices(v), adjList(v) {}

    void addEdge(int u, int v) {
        if (u != v && find(adjList[u].begin(), adjList[u].end(), v) == adjList[u].end()) {
            adjList[u].push_back(v);
            adjList[v].push_back(u); 
        }
    }

    void printGraph() {
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (int j : adjList[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
    }
};


bool hasEulerianCircuit(Graph& g) {
    for (int i = 0; i < g.vertices; i++) {
        if (g.adjList[i].size() % 2 != 0)
            return false;
    }
    return true;
}


Graph createRandomGraph(int vertices, int edges, int seed) {
    Graph g(vertices);
    srand(seed);
    for (int i = 0; i < edges; i++) {
        int u = rand() % vertices;
        int v = rand() % vertices;
        g.addEdge(u, v);
    }
    return g;
}

void memoryLeakExample(int argc, char *argv[]) {
    string string_so_far;

    for (int i = 0; i < argc; i++) {
        if (!string_so_far.empty()) {
            string_so_far += " ";
        }
        string_so_far += argv[i];
    }

    cout << "You entered: " << string_so_far << endl;
}


class Singleton {
private:
    static shared_ptr<Singleton> instance;
    static mutex mtx;

    Singleton() {}

public:
    static shared_ptr<Singleton> getInstance() {
        lock_guard<mutex> lock(mtx);
        if (!instance) {
            instance = shared_ptr<Singleton>(new Singleton());
        }
        return instance;
    }
};

shared_ptr<Singleton> Singleton::instance = nullptr;
mutex Singleton::mtx;


int main(int argc, char *argv[]) {
    int vertices = 5, edges = 7, seed = time(0);

    
    int opt;
    while ((opt = getopt(argc, argv, "v:e:s:")) != -1) {
        switch (opt) {
            case 'v': vertices = atoi(optarg); break;
            case 'e': edges = atoi(optarg); break;
            case 's': seed = atoi(optarg); break;
            default:
                cerr << "Usage: " << argv[0] << " -v vertices -e edges -s seed\n";
                return 1;
        }
    }

    Graph g = createRandomGraph(vertices, edges, seed);
    g.printGraph();

    
    if (hasEulerianCircuit(g)) {
        cout << "The graph has an Eulerian Circuit." << endl;
    } else {
        cout << "The graph does not have an Eulerian Circuit." << endl;
    }

    
    memoryLeakExample(argc, argv);

    
    shared_ptr<Singleton> s = Singleton::getInstance();

    return 0;
}
