#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <stdexcept>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#include "../Graph.hpp"

template <typename T> class Graph;

namespace storage {
    template <typename V> void import(Graph<V>& graph, const std::string& fileName, bool customPath = false) {
        std::ifstream file(customPath ? fileName : ("data/" + fileName));
        if (!file.is_open()) 
            throw std::invalid_argument("Failed to open file: " + fileName);

        std::string jsonString;
        std::string line;
        while (std::getline(file, line)) 
            jsonString += line;

        file.close();

        nlohmann::json data = nlohmann::json::parse(jsonString);

        if (data["directed"] != graph.isDigraph()) {
            throw std::invalid_argument("Graph type mismatch.");
        }

        graph.clear();

        for (const auto& vertex : data["vertices"]) {
            V v = vertex["id"].get<V>();
            graph.addVertex(v);
        }

        for (const auto& link : data["edges"]) {
            V source = link["source"].get<V>();
            V target = link["target"].get<V>();
            double weight = link["weight"].get<double>();
            graph.addEdge(source, target, weight);
        }
    }

    template <typename V> void exportJSON(Graph<V>& graph, const std::string& fileName, bool customPath = false) {
        nlohmann::json data;
        data["directed"] = graph.isDigraph();
        data["multigraph"] = false;

        nlohmann::json vertices = nlohmann::json::array();

        for (const V& vertex : graph.vertices()) {
            nlohmann::json node;
            node["id"] = vertex;
            vertices.push_back(node);
        }

        nlohmann::json links = nlohmann::json::array();

        for (const Edge<V>& edge : graph.edgeList()) {
            nlohmann::json link;
            link["source"] = edge.getSource();
            link["target"] = edge.getDestination();
            link["weight"] = edge.getWeight();
            links.push_back(link);
        }

        data["edges"] = links;
        std::string json =  data.dump(4); 

        std::ofstream file(customPath ? fileName : ("data/" + fileName));
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << fileName << std::endl;
        } else {
            file << json;
            file.close();
        }
    }

    template <typename V> void plot(Graph<V>& graph, std::string pngFileName = "", bool showInAWindow = false) {
        if (!pngFileName.empty() && !pngFileName.ends_with(".png")) {
            pngFileName = pngFileName.substr(0, pngFileName.find_last_of('.')) + ".png";
        }
        
        std::string filename = "tmp/toPlot.json";
        exportJSON(graph, filename, true);
        std::cout << "Graph exported to " << filename << std::endl;

        std::string command = "python src/scripts/graph_visualizer.py ";
        command += filename;
        command += (showInAWindow ? " true " : " false ");
        command += pngFileName;
        int result = std::system(command.c_str());
        if (result == 0) {
            std::cout << "Graph image generated successfully." << std::endl;
        } else {
            std::cout << "Failed to generate graph image." << std::endl;
        }

        std::remove(filename.c_str());
    }

    template <typename V> void draw(Graph<V>& graph) {
        std::string command = "python src/scripts/graph_drawer.py";
        int result = std::system(command.c_str());
        if (result == 0) {
            std::cout << "Graph drawer executed successfully." << std::endl;
        } else {
            std::cout << "Failed to execute drawer." << std::endl;
        }
    
        try {
            import(graph, "tmp/importable.json", true);
            std::cout << "Graph imported successfully!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "No graph to import!" << std::endl;
        }

        std::remove("tmp/importable.json");
    }
};

#endif