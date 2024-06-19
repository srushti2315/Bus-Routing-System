#include <iostream>
#include <fstream>
#include "functions.cpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main() {
  
    ifstream file(("./assets/routes2.json"));
    json data;
    file >> data;
    file.close();


    Graph graph;


    for (const auto& place : data["places"]) {
        graph.addVertex(place["id"], place["place_name"], stod(place["latitude"].get<string>()), stod(place["longitude"].get<string>()));
    }


    for (const auto& connection : data["connections"]) {
        graph.addEdge(connection["source"], connection["destination"], stod(connection["weight"].get<string>()));
    }

    // Take input from the user for source and destination names
    string sourceName, destinationName;
    cout << "Enter source place name: ";
    getline(cin, sourceName);
    sourceName = trim(sourceName); // Trim trailing spaces
    cout << "Enter destination place name: ";
    getline(cin, destinationName);
    destinationName = trim(destinationName); // Trim trailing spaces

    // Get corresponding vertex IDs
    string sourceId, destinationId;
    for (const auto& place : data["places"]) {
        if (compareIgnoreCase(place["place_name"], sourceName)) {
            sourceId = place["id"];
        }
        if (compareIgnoreCase(place["place_name"], destinationName)) {
            destinationId = place["id"];
        }
    }

    // Check if both source and destination IDs are valid
    if (sourceId.empty() || destinationId.empty()) {
        cout << "Invalid place names." << endl;
        return 1;
    }

    // Find the shortest path
    list<string> path = graph.shortestPath(sourceId, destinationId);
    if (!path.empty()) {
        double distance = graph.getVertex(destinationId)->distance;
        cout << "Distance of shortest path: " << distance << endl;
        cout << "Shortest path from " << sourceName << " to " << destinationName << ":" << endl;
        for (const auto& vertex : path) {
            cout << graph.getVertex(vertex)->place_name << " -> ";
        }
        cout << endl;
         // Write latitude and longitude to file
        ofstream outFile("latlng.txt");
        if (outFile.is_open()) {
            outFile << "lat:" << graph.getVertex(sourceId)->latitude << " ";
            outFile << "long:" << graph.getVertex(sourceId)->longitude << " ";
            outFile << "lat:" << graph.getVertex(destinationId)->latitude << " ";
            outFile << "long:" << graph.getVertex(destinationId)->longitude << " ";
            outFile.close();
            cout << "Latitude and longitude written to latlng.txt successfully." << endl;
        } else {
            cerr << "Unable to open file." << endl;
            return 1;
        }
    }
    

    return 0;
}