#pragma once
#include <stdint.h>

extern "C" {

typedef struct ExampleCTypes_InitData {
  char* string_;
  int integer_;
  float float_;
  bool boolean_;
  float* vectorFloat_;
  int vectorFloatSize_;
} ExampleCTypes_InitData;

// --- User defined C-API functions ---
int ExampleCTypes_StructInOut(void* initDataPtr); // Allocated in python
int ExampleCTypes_ScalarsIn(int integer_, float float_, char byte_);
int ExampleCTypes_VectorsInOut(int* integer_, float* float_, char* bytes_); // Allocated in python, known size = 2 for all
int ExampleCTypes_VectorsOut(int** integer_, float** float_, char** bytes_); // Allocated in C/C++, known size = 2 for all

// --- Standard C-API functions ---
int ExampleCTypes_version(void** versionPtr); // Allocated in C, char**
int ExampleCTypes_error(void** errorPtr); // Allocated in C, char**
void ExampleCTypes_clearErrors();
void* ExampleCTypes_cecs();
int ExampleCTypes_setcecs(void* errorPtr);

}; // extern C
