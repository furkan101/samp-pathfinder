#pragma once
#include <string>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <amx/amx.h>
#include "pathfinder.h"

struct PathTask {
    int startNodeID;
    int endNodeID;

    std::string callbackFunc;
    int playerID;
    AMX* amxInstance;
    PathResult result;
    int readIndex = -1;
};

extern std::vector<PathTask*> g_ResultCache;

void StartWorker();
void StopWorker();
void AddTask(PathTask* task);
void ProcessCallbacks();