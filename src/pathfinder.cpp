#include "pathfinder.h"
#include <algorithm>

std::vector<Node> g_Nodes;

void AddNode(int id, float x, float y, float z) {
    Node n;
    n.id = id;
    n.position = {x, y, z};
    g_Nodes.push_back(n);
}

void ConnectNodes(int id1, int id2) {
    auto it1 = std::find_if(g_Nodes.begin(), g_Nodes.end(), [id1](const Node& n){ return n.id == id1; });
    auto it2 = std::find_if(g_Nodes.begin(), g_Nodes.end(), [id2](const Node& n){ return n.id == id2; });

    if (it1 != g_Nodes.end() && it2 != g_Nodes.end()) {
        it1->neighbors.push_back(id2);
        it2->neighbors.push_back(id1);
    }
}