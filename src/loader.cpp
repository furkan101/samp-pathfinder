#include "pathfinder.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

bool LoadGTANodes(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        int id;
        float x, y, z;
        
        if (!(ss >> id >> x >> y >> z)) continue;
        
        AddNode(id, x, y, z);
        
        int neighborID;
        while (ss >> neighborID) {
            ConnectNodes(id, neighborID);
        }
    }
    
    return true;
}