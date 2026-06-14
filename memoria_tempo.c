#include "memoria_tempo.h"
#include <time.h>
#include <windows.h>
#include <psapi.h>

#define _POSIX_C_SOURCE 199309L

size_t memoria_atual(void){
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))){
        return pmc.PeakWorkingSetSize;
    }
    return 0;
}

double obter_tempo(void) {
    struct timespec ts;
    
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (double)ts.tv_sec + ((double)ts.tv_nsec / 1000000000.0);
}
