#pragma once
#include <stdint.h>

extern "C" {

// --- User defined C-API functions ---
int ExampleCAPI_Initialize();
int ExampleCAPI_Process();
int ExampleCAPI_Shutdown();

// --- Standard C-API functions ---
int ExampleCAPI_version(void** versionPtr); // Allocated in C, char**
int ExampleCAPI_error(void** errorPtr); // Allocated in C, char**
void ExampleCAPI_clearErrors();
void* ExampleCAPI_cecs();
int ExampleCAPI_setcecs(void* errorPtr);

}; // extern C
