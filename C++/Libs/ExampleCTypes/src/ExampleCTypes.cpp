#include <ExampleCTypes.hpp>
#include "../../../BuildVersion/BuildVersion.hpp"
#include <Common.hpp>
#include <vkpBuildVersioner.hpp>

CECS_MODULE("ExampleCTypes")
using namespace vkp;
static vkpBuildVersioner BV1(1, VERSION_NUMBER);

extern "C" {

// --- User defined C-API functions ---
int ExampleCTypes_StructInOut(void* initDataPtr) { // Allocated in python
  _ERRI(initDataPtr == nullptr,"initDataPtr pointer was nullptr")

  ExampleCTypes_InitData* initData = (ExampleCTypes_InitData*)initDataPtr;
  _ERRI(nullptr == initData->string_, "string_ is nullptr")
  _ERRI(nullptr == initData->vectorFloat_, "vectorFloat_ is nullptr")

  dbg_(63,"ExampleCTypes_StructInOut(): === START ===")
  dbg_(63,"string_: "<<string(initData->string_))
  dbg_(63,"integer_: "<<initData->integer_)
  dbg_(63,"float_: "<<initData->float_)
  dbg_(63,"boolean_: "<<initData->boolean_)
  dbg_(63,"vectorFloat_: ")
  for (int i=0; i < initData->vectorFloatSize_; i++) {
    dbg_(63," - ["<<initData->vectorFloat_[i]<<"]")
  }

  // Update some of the values.
  initData->integer_ = -1;
  initData->float_ = -1.0;

  dbg_(63,"ExampleCTypes_StructInOut(): === END ===")
  return 0;
}

int ExampleCTypes_ScalarsIn(int integer_, float float_, char byte_) {
  dbg_(63,"integer_: "<<integer_)
  dbg_(63,"float_: "<<float_)
  dbg_(63,"byte_: "<<byte_)
  return 0;
}

int ExampleCTypes_VectorsInOut(int* integer_, float* float_, char* bytes_) { // Allocated in python, known size = 2 for all
  _ERRI(nullptr==integer_,"integer_ is nullptr")
  _ERRI(nullptr==float_,"float_ is nullptr")
  _ERRI(nullptr==bytes_,"bytes_ is nullptr")
  for (int i=0; i < 2; i++) {
    dbg_(63,"integer_: "<<integer_[i]<<", float_: "<<float_[i]<<", bytes: "<<bytes_[i])
    integer_[i] = -1;
    float_[i] = -1.0;
    bytes_[i] = 'z';
  }
  return 0;
}

int ExampleCTypes_VectorsOut(int** integer_, float** float_, char** bytes_) { // Allocated in C/C++, known size = 2 for all
  static vector<int> vInt;
  static vector<float> vFloat;
  static vector<char> vByte;
  vInt.push_back(10); vInt.push_back(20);
  vFloat.push_back(30); vFloat.push_back(40);
  vByte.push_back('a'); vByte.push_back('b');
  *integer_ = vInt.data();
  *float_ = vFloat.data();
  *bytes_ = vByte.data();

  return 0;
}




// --- Standard C-API functions ---
int ExampleCTypes_version(void** versionPtr){  // Allocated in C, char**
  _ERRI(nullptr == versionPtr,"NULL pointer provided!")
  *versionPtr = const_cast<char*>(BV1.version.c_str());
  return 0;
}

int ExampleCTypes_error(void** errorPtr){ // Allocated in C, char**
  if (errorPtr == NULL) return -1;
  *errorPtr = const_cast<char*>(__ECSOBJ__.str());
  if (_NERR_ != 0) return -1;
  return 0;
}

void ExampleCTypes_clearErrors() {
  _ECSCLS_
}

void* ExampleCTypes_cecs() {
  return __ECSOBJ__.cecs();
}

int ExampleCTypes_setcecs(void* errorPtr) {
  __ECSOBJ__.ConnectTo(errorPtr);
  return 0;
}

}; // extern C
