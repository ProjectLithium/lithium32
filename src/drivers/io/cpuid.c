#include "cpuid.h"
#include <stdint.h>
#include <stddef.h>
#include <std/string.h>
#include <cpuid.h>

char* cpuid_get_cpu_name() {
    uint32_t regs[12] = {0};
    char *name = (char *)regs;
    char *cpu_name = "                                                \0"; // 48 chars + null terminator
    
    if (!cpu_name) {
        return NULL; // Memory allocation failed
    }

    // Get the CPU brand string using CPUID
    if (__get_cpuid(0x80000002, &regs[0], &regs[1], &regs[2], &regs[3]) &&
        __get_cpuid(0x80000003, &regs[4], &regs[5], &regs[6], &regs[7]) &&
        __get_cpuid(0x80000004, &regs[8], &regs[9], &regs[10], &regs[11])) {
        
        // Copy the name and ensure null termination
        strncpy(cpu_name, name, 48);
        cpu_name[48] = '\0';
        
        // Trim trailing whitespace
        for (int i = strlen(cpu_name) - 1; i >= 0; i--) {
            if (cpu_name[i] == ' ') {
                cpu_name[i] = '\0';
            } else {
                break;
            }
        }
    } else {
        strcpy(cpu_name, "Unknown CPU");
    }

    return cpu_name;
}