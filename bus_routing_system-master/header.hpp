#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <queue>
#include <limits>

using namespace std;

struct Vertex {
    string id;
    string place_name;
    double latitude;
    double longitude;
    list<pair<string, double>> connections;
    double distance; // Distance from the source vertex
    string previous; // Previous vertex in the shortest path
    bool visited;    // Flag to mark if the vertex has been visited
};

class Graph {
private:
    unordered_map<string, Vertex*> vertices;

public:
    Graph();
    ~Graph();
    void addVertex(const string& id, const string& place_name, double latitude, double longitude);
    void addEdge(const string& source, const string& destination, double weight);
    Vertex* getVertex(const string& id);
    string trim(const string& str);
    bool compareIgnoreCase(const string& str1, const string& str2);
    string getVertexIdByPlaceName(const string& placeName); // Declaration of the new method
    void display();
    void clear();
    void dijkstra(const string& source);
    list<string> shortestPath(const string& source, const string& destination);
};