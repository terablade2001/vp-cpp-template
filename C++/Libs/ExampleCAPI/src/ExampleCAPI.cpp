#include <ExampleCAPI.hpp> // CAPI functions for .dll use
#include <DummyClass.hpp> // .dll internal objects
#include "../../../BuildVersion/BuildVersion.hpp"
#include <Common.hpp>
#include <vkpBuildVersioner.hpp>

CECS_MODULE("ExampleCAPI")

using namespace std;
using namespace vkp;

static vkpBuildVersioner BV1(1, VERSION_NUMBER);

static DummyClass dummyClass;

extern "C" {

// --- User defined C-API functions ---
int ExampleCAPI_Initialize() {
  try {
    dbg_(63,"ExampleCAPI - Initialize")
  } catch (std::exception& e) { _ERRI(1,"Exception:\n[%s]") }
  return 0;
}
int ExampleCAPI_Process() {
  try {
    dbg_(63,"ExampleCAPI - Process")
    _ERRI(1,"Produced Error!")
  } catch (std::exception& e) { _ERRI(1,"Exception:\n[%s]") }
  return 0;
}
int ExampleCAPI_Shutdown() {
  try {
    dbg_(63,"ExampleCAPI - Shutdown")
  } catch (std::exception& e) { _ERRI(1,"Exception:\n[%s]") }
  return 0;
}


// --- Standard C-API functions ---
int ExampleCAPI_version(void** versionPtr){
  _ERRI(nullptr == versionPtr,"NULL pointer provided!")
  *versionPtr = const_cast<char*>(BV1.version.c_str());
  return 0;
}

int ExampleCAPI_error(void** errorPtr){
  if (errorPtr == NULL) return -1;
  *errorPtr = const_cast<char*>(__ECSOBJ__.str());
  if (_NERR_ != 0) return -1;
  return 0;
}

void ExampleCAPI_clearErrors() {
  _ECSCLS_
}

void* ExampleCAPI_cecs() {
  return __ECSOBJ__.cecs();
}

int ExampleCAPI_setcecs(void* errorPtr) {
  __ECSOBJ__.ConnectTo(errorPtr);
  return 0;
}

}; // extern "C"
