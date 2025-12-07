#pragma once
#include <vector>
#include <cmath>
#include <map>
#include <string>

struct Vector3 {
    float x, y, z;
    float DistanceTo(const Vector3& other) const {
        return (float)std::sqrt(std::pow(other.x - x, 2) + 
                                std::pow(other.y - y, 2) + 
                                std::pow(other.z - z, 2));
    }
};

struct Node {
    int id;
    Vector3 position;
    std::vector<int> neighbors;
};

struct PathResult {
    bool found;
    std::vector<int> pathNodeIDs;
    float totalDistance;
};

extern std::vector<Node> g_Nodes;
extern std::map<unsigned int, int> g_GtaToInternalID;

void AddNode(int id, float x, float y, float z);
void ConnectNodes(int id1, int id2);
PathResult FindPath(int startID, int endID);
bool LoadGTANodes(const std::string& filepath);
bool GetNodePos(int id, float& x, float& y, float& z);