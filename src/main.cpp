#include <amx/amx.h>
#include <plugincommon.h>
#include "worker.h"

#if defined(_MSC_VER)
    #pragma comment(linker, "/EXPORT:Supports=_Supports@0")
    #pragma comment(linker, "/EXPORT:Load=_Load@4")
    #pragma comment(linker, "/EXPORT:Unload=_Unload@0")
    #pragma comment(linker, "/EXPORT:AmxLoad=_AmxLoad@4")
    #pragma comment(linker, "/EXPORT:AmxUnload=_AmxUnload@4")
    #pragma comment(linker, "/EXPORT:ProcessTick=_ProcessTick@0")
#endif

void *pAMXFunctions;

int ExecCallback(AMX* amx, const char* func, int playerid, int resultIdx) {
    int idx;
    if (amx_FindPublic(amx, func, &idx) == AMX_ERR_NONE) {
        amx_Push(amx, playerid);
        amx_Push(amx, resultIdx);
        cell retval;
        amx_Exec(amx, &retval, idx);
        return 1;
    }
    return 0;
}

extern AMX_NATIVE_INFO PluginNatives[];

extern "C" {
    
    unsigned int PLUGIN_CALL Supports() {
        return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
    }

    bool PLUGIN_CALL Load(void **ppData) {
        pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
        StartWorker();
        return true;
    }

    void PLUGIN_CALL Unload() {
        StopWorker();
    }

    int PLUGIN_CALL AmxLoad(AMX* amx) {
        return amx_Register(amx, PluginNatives, -1);
    }

    int PLUGIN_CALL AmxUnload(AMX* amx) {
        return AMX_ERR_NONE;
    }

    void PLUGIN_CALL ProcessTick() {
        ProcessCallbacks();
    }
}