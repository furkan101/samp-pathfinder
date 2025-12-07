#include "amx.h"
#include "../plugincommon.h"

extern void *pAMXFunctions;

typedef int (AMXAPI *amx_Register_t)(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number);
typedef int (AMXAPI *amx_GetString_t)(char *dest,const cell *source,int use_wchar,size_t size);
typedef int (AMXAPI *amx_SetString_t)(cell *dest,const char *source,int pack,int use_wchar,size_t size); // YENI EKLENDI
typedef int (AMXAPI *amx_GetAddr_t)(AMX *amx,cell amx_addr,cell **phys_addr);
typedef int (AMXAPI *amx_StrLen_t)(const cell *cstring,int *length);
typedef int (AMXAPI *amx_FindPublic_t)(AMX *amx, const char *funcname, int *index);
typedef int (AMXAPI *amx_Push_t)(AMX *amx, cell value);
typedef int (AMXAPI *amx_Exec_t)(AMX *amx, cell *retval, int index);

int AMXAPI amx_Register(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number) {
	amx_Register_t fn = (amx_Register_t)((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Register];
	return fn(amx, nativelist, number);
}

int AMXAPI amx_GetString(char *dest,const cell *source,int use_wchar,size_t size) {
	amx_GetString_t fn = (amx_GetString_t)((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetString];
	return fn(dest, source, use_wchar, size);
}

int AMXAPI amx_SetString(cell *dest,const char *source,int pack,int use_wchar,size_t size) {
	amx_SetString_t fn = (amx_SetString_t)((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_SetString];
	return fn(dest, source, pack, use_wchar, size);
}

int AMXAPI amx_GetAddr(AMX *amx,cell amx_addr,cell **phys_addr) {
	amx_GetAddr_t fn = (amx_GetAddr_t)((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_GetAddr];
	return fn(amx, amx_addr, phys_addr);
}

int AMXAPI amx_StrLen(const cell *cstring,int *length) {
	amx_StrLen_t fn = (amx_StrLen_t)((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_StrLen];
	return fn(cstring, length);
}

int AMXAPI amx_FindPublic(AMX *amx, const char *funcname, int *index) {
	amx_FindPublic_t fn = (amx_FindPublic_t)((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_FindPublic];
	return fn(amx, funcname, index);
}

int AMXAPI amx_Push(AMX *amx, cell value) {
	amx_Push_t fn = (amx_Push_t)((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Push];
	return fn(amx, value);
}

int AMXAPI amx_Exec(AMX *amx, cell *retval, int index) {
	amx_Exec_t fn = (amx_Exec_t)((void**)pAMXFunctions)[PLUGIN_AMX_EXPORT_Exec];
	return fn(amx, retval, index);
}