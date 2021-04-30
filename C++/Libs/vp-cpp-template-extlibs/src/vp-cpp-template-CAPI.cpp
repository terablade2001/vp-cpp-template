#include <vp-cpp-template.hpp>
#include <vp-cpp-teamplate-extlibs.hpp>
#include "../../../../BuildVersion/BuildVersion.hpp"

CECS_MODULE("vp-cpp-tempalte-extlibs")
using namespace vkp;
static vkpBuildVersioner BV1(1, VERSION_NUMBER);
extern "C" {

int vpCppTemplate_extlibs_version(void** versionPtr){  // Allocated in C, char**
  _ERRI(nullptr == versionPtr,"NULL pointer provided!")
  *versionPtr = const_cast<char*>(BV1.version.c_str());
  return 0;
}

int vpCppTemplate_extlibs_error(void** errorPtr){ // Allocated in C, char**
  if (errorPtr == NULL) return -1;
  *errorPtr = const_cast<char*>(__ECSOBJ__.str());
  if (_NERR_ != 0) return -1;
  return 0;
}

void vpCppTemplate_extlibs_clearErrors() {
  _ECSCLS_
}

void* vpCppTemplate_extlibs_cecs() {
  return __ECSOBJ__.cecs();
}

int vpCppTemplate_extlibs_setcecs(void* errorPtr) {
  __ECSOBJ__.ConnectTo(errorPtr);
  return 0;
}

}; // extern C
