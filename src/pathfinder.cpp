#include "pathfinder.h"
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <limits>

std::vector<Node> g_Nodes;

Node* GetNodeByID(int id) {
    for (auto& node : g_Nodes) {
        if (node.id == id) return &node;
    }
    return nullptr;
}

void AddNode(int id, float x, float y, float z) {
    Node n;
    n.id = id;
    n.position = {x, y, z};
    g_Nodes.push_back(n);
}

void ConnectNodes(int id1, int id2) {
    Node* n1 = GetNodeByID(id1);
    Node* n2 = GetNodeByID(id2);

    if (n1 && n2) {
        n1->neighbors.push_back(id2);
        n2->neighbors.push_back(id1);
    }
}

PathResult FindPath(int startID, int endID) {
    PathResult result;
    result.found = false;
    result.totalDistance = 0.0f;

    Node* startNode = GetNodeByID(startID);
    Node* endNode = GetNodeByID(endID);
    
    if (!startNode || !endNode) return result;

    typedef std::pair<float, int> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> openSet;

    std::unordered_map<int, int> cameFrom;
    std::unordered_map<int, float> gScore;
    std::unordered_map<int, float> fScore;

    for (const auto& node : g_Nodes) {
        gScore[node.id] = std::numeric_limits<float>::infinity();
        fScore[node.id] = std::numeric_limits<float>::infinity();
    }

    gScore[startID] = 0.0f;
    fScore[startID] = startNode->position.DistanceTo(endNode->position);
    
    openSet.push({fScore[startID], startID});

    while (!openSet.empty()) {
        int currentID = openSet.top().second;
        openSet.pop();

        if (currentID == endID) {
            result.found = true;
            result.totalDistance = gScore[endID];

            int curr = endID;
            while (curr != startID) {
                result.pathNodeIDs.push_back(curr);
                curr = cameFrom[curr];
            }
            result.pathNodeIDs.push_back(startID);
            
            std::reverse(result.pathNodeIDs.begin(), result.pathNodeIDs.end());
            return result;
        }

        Node* current = GetNodeByID(currentID);
        if (!current) continue;

        for (int neighborID : current->neighbors) {
            Node* neighbor = GetNodeByID(neighborID);
            if (!neighbor) continue;

            float tentative_gScore = gScore[currentID] + current->position.DistanceTo(neighbor->position);

            if (tentative_gScore < gScore[neighborID]) {
                cameFrom[neighborID] = currentID;
                gScore[neighborID] = tentative_gScore;
                fScore[neighborID] = gScore[neighborID] + neighbor->position.DistanceTo(endNode->position);
                
                openSet.push({fScore[neighborID], neighborID});
            }
        }
    }

    return result;
}