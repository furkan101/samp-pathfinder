#include "worker.h"
#include "pathfinder.h"
#include <plugincommon.h>

std::string GetPawnString(AMX* amx, cell param) {
    cell* addr = NULL;
    int len = 0;
    amx_GetAddr(amx, param, &addr);
    amx_StrLen(addr, &len);
    if (len == 0) return "";
    char* text = new char[len + 1];
    amx_GetString(text, addr, 0, len + 1);
    std::string res(text);
    delete[] text;
    return res;
}

PathTask* GetResult(int id) {
    if (id < 0 || id >= g_ResultCache.size()) return nullptr;
    return g_ResultCache[id];
}

cell AMX_NATIVE_CALL PF_AddNode(AMX* amx, cell* params) {
    AddNode(params[1], amx_ctof(params[2]), amx_ctof(params[3]), amx_ctof(params[4]));
    return 1;
}

cell AMX_NATIVE_CALL PF_ConnectNodes(AMX* amx, cell* params) {
    ConnectNodes(params[1], params[2]);
    return 1;
}

cell AMX_NATIVE_CALL PF_FindPath(AMX* amx, cell* params) {
    PathTask* task = new PathTask();
    
    task->startNodeID = params[1];
    task->endNodeID = params[2];
    task->callbackFunc = GetPawnString(amx, params[3]);
    task->playerID = params[4];
    task->amxInstance = amx;
    
    AddTask(task);
    return 1;
}

cell AMX_NATIVE_CALL PF_PathFound(AMX* amx, cell* params) {
    PathTask* t = GetResult(params[1]);
    return (t && t->result.found) ? 1 : 0;
}

cell AMX_NATIVE_CALL PF_PathNext(AMX* amx, cell* params) {
    PathTask* t = GetResult(params[1]);
    if (!t || !t->result.found) return 0;
    
    t->readIndex++;
    if (t->readIndex < t->result.pathNodeIDs.size()) return 1;
    return 0;
}

cell AMX_NATIVE_CALL PF_GetPathNode(AMX* amx, cell* params) {
    PathTask* t = GetResult(params[1]);
    if (!t) return -1;
    
    if (t->readIndex >= 0 && t->readIndex < t->result.pathNodeIDs.size()) {
        return t->result.pathNodeIDs[t->readIndex];
    }
    return -1;
}

cell AMX_NATIVE_CALL PF_FreeResult(AMX* amx, cell* params) {
    int id = params[1];
    if (id >= 0 && id < g_ResultCache.size()) {
        if (g_ResultCache[id]) {
            delete g_ResultCache[id];
            g_ResultCache[id] = nullptr;
        }
    }
    return 1;
}

cell AMX_NATIVE_CALL PF_LoadGraph(AMX* amx, cell* params) {
    std::string filename = GetPawnString(amx, params[1]);
    bool success = LoadGTANodes(filename);
    return success ? 1 : 0;
}

cell AMX_NATIVE_CALL PF_GetNodePos(AMX* amx, cell* params) {
    int nodeID = params[1];
    float x, y, z;

    if (GetNodePos(nodeID, x, y, z)) {
        
        cell* addrX = NULL;
        cell* addrY = NULL;
        cell* addrZ = NULL;

        amx_GetAddr(amx, params[2], &addrX);
        amx_GetAddr(amx, params[3], &addrY);
        amx_GetAddr(amx, params[4], &addrZ);

        *addrX = amx_ftoc(x);
        *addrY = amx_ftoc(y);
        *addrZ = amx_ftoc(z);
        
        return 1;
    }
    return 0;
}

AMX_NATIVE_INFO PluginNatives[] = {
    {"PF_AddNode", PF_AddNode},
    {"PF_ConnectNodes", PF_ConnectNodes},
    {"PF_FindPath", PF_FindPath},
    {"PF_PathFound", PF_PathFound},
    {"PF_PathNext", PF_PathNext},
    {"PF_GetPathNode", PF_GetPathNode},
    {"PF_FreeResult", PF_FreeResult},
    {"PF_LoadGraph", PF_LoadGraph},
    {"PF_GetNodePos", PF_GetNodePos},
    {0, 0}
};