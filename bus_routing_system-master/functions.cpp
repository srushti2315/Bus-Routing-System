#include"header.hpp"

Graph::Graph() {}

Graph::~Graph() {
    clear();
}

void Graph::addVertex(const string& id, const string& place_name, double latitude, double longitude) {
    if (vertices.find(id) == vertices.end()) {
        Vertex* newVertex = new Vertex;
        newVertex->id = id;
        newVertex->place_name = place_name;
        newVertex->latitude = latitude;
        newVertex->longitude = longitude;
        newVertex->distance = numeric_limits<double>::infinity(); // Initialize distance to infinity
        newVertex->previous = ""; // Initialize previous vertex as empty string
        newVertex->visited = false; // Initialize visited flag as false
        vertices[id] = newVertex;
    }
}

void Graph::addEdge(const string& source, const string& destination, double weight) {
    Vertex* srcVertex = getVertex(source);
    Vertex* destVertex = getVertex(destination);

    if (srcVertex && destVertex) {
        srcVertex->connections.push_back(make_pair(destination, weight));
    }
}

Vertex* Graph::getVertex(const string& id) {
    if (vertices.find(id) != vertices.end()) {
        return vertices[id];
    }
    return nullptr;
}

// Trim function to remove trailing spaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Case-insensitive string comparison
bool compareIgnoreCase(const string& str1, const string& str2) {
    if (str1.length() != str2.length()) {
        return false;
    }
    return equal(str1.begin(), str1.end(), str2.begin(), [](char a, char b) {
        return tolower(a) == tolower(b);
    });
}

string Graph::getVertexIdByPlaceName(const string& placeName) {
    for (auto& pair : vertices) {
        if (pair.second->place_name == placeName) {
            return pair.first;
        }
    }
    return ""; // Return empty string if place name not found
}


void Graph::display() {
    for (auto& pair : vertices) {
        cout << "Vertex ID: " << pair.second->id << endl;
        cout << "Place Name: " << pair.second->place_name << endl;
        cout << "Latitude: " << pair.second->latitude << endl;
        cout << "Longitude: " << pair.second->longitude << endl;
        cout << "Connections:" << endl;
        for (auto& connection : pair.second->connections) {
            cout << " -> " << connection.first << " (Weight: " << connection.second << ")" << endl;
        }
        cout << endl;
    }
}

void Graph::clear() {
    for (auto& pair : vertices) {
        delete pair.second;
    }
    vertices.clear();
}


void Graph::dijkstra(const string& source) {
    // Reset distances and visited flags
    for (auto& pair : vertices) {
        pair.second->distance = numeric_limits<double>::infinity();
        pair.second->visited = false;
        pair.second->previous = "";
    }

    // Set distance of source vertex to 0
    vertices[source]->distance = 0;

    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        string current = pq.top().second;
        pq.pop();

        if (vertices[current]->visited) continue;

        vertices[current]->visited = true;

        for (auto& connection : vertices[current]->connections) {
            string neighbor = connection.first;
            double weight = connection.second;

            if (!vertices[neighbor]->visited && vertices[current]->distance + weight < vertices[neighbor]->distance) {
                vertices[neighbor]->distance = vertices[current]->distance + weight;
                vertices[neighbor]->previous = current;
                pq.push(make_pair(vertices[neighbor]->distance, neighbor));
            }
        }
    }
}

list<string> Graph::shortestPath(const string& source, const string& destination) {
    dijkstra(source);

    list<string> path;
    string current = destination;

    while (current != "" && current != source) {
        path.push_front(current);
        current = vertices[current]->previous;
    }

    if (current == source) {
        path.push_front(source);
    }

    return path;
}