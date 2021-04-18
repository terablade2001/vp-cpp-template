#pragma once
#include <stdint.h>

extern "C" {

// --- Standard C-API functions ---
int vpCppTemplate_extlibs_version(void** versionPtr); // Allocated in C, char**
int vpCppTemplate_extlibs_error(void** errorPtr); // Allocated in C, char**
void vpCppTemplate_extlibs_clearErrors();
void* vpCppTemplate_extlibs_cecs();
int vpCppTemplate_extlibs_setcecs(void* errorPtr);

}; // extern C
