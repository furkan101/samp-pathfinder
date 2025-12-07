#include "worker.h"
#include <thread>
#include <mutex>
#include <chrono>

std::queue<PathTask*> g_InputQueue;
std::queue<PathTask*> g_OutputQueue;
std::vector<PathTask*> g_ResultCache;

std::mutex g_InputMutex;
std::mutex g_OutputMutex;
std::thread g_Thread;
bool g_Running = false;

extern int ExecCallback(AMX* amx, const char* func, int playerid, int resultIdx);

void WorkerLoop() {
    while (g_Running) {
        PathTask* task = nullptr;

        {
            std::lock_guard<std::mutex> lock(g_InputMutex);
            if (!g_InputQueue.empty()) {
                task = g_InputQueue.front();
                g_InputQueue.pop();
            }
        }

        if (!task) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            continue;
        }

        task->result = FindPath(task->startNodeID, task->endNodeID);

        {
            std::lock_guard<std::mutex> lock(g_OutputMutex);
            g_OutputQueue.push(task);
        }
    }
}

void StartWorker() {
    g_Running = true;
    g_Thread = std::thread(WorkerLoop);
}

void StopWorker() {
    g_Running = false;
    if (g_Thread.joinable()) g_Thread.join();
}

void AddTask(PathTask* task) {
    std::lock_guard<std::mutex> lock(g_InputMutex);
    g_InputQueue.push(task);
}

void ProcessCallbacks() {
    std::lock_guard<std::mutex> lock(g_OutputMutex);
    while (!g_OutputQueue.empty()) {
        PathTask* task = g_OutputQueue.front();
        g_OutputQueue.pop();

        if (task->amxInstance) {
            g_ResultCache.push_back(task);
            int resultIndex = g_ResultCache.size() - 1;

            ExecCallback(task->amxInstance, task->callbackFunc.c_str(), task->playerID, resultIndex);
        } else {
            delete task;
        }
    }
}