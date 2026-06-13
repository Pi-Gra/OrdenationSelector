#include "memoria.h"
#include <windows.h>
#include <psapi.h>

size_t memoria_atual(void){
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))){
        return pmc.PeakWorkingSetSize;
    }
    return 0;
}