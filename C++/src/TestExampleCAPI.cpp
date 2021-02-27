#include <TestExampleCAPI.hpp>

CECS_MODULE("TestExampleCAPI")

using namespace std;
using namespace vkp;
using namespace vkpConfigReader;

static float InputValue;

int TestExampleCAPI_LoadConfigParameters(string&& file) {
  _ERRINF(1,"config file: [%s]", file.c_str())
  cfg_type cfg_data;
  _ERRI(0!=cfg_LoadFile(file.c_str(), cfg_data),"Failed to load config file")
  std::vector<std::string> CheckParamList = {
    "InputValue"
  };
  std::string NotExistingParams;
  int r = cfg_CheckParams(cfg_data, CheckParamList, NotExistingParams);
  _ERRSTR(r!=0,{ ss << "The following parameters were not found: \n" << "[" << NotExistingParams << "]"; })
  _ERRI(r!=0,"Missing parameter in configuration file.")
  _ERRI(0!=cfg_GetParam(cfg_data, "InputValue", InputValue),"Failed to process parameters [InputValue]")
  _ECSCLS_
  return 0;
}

int TestExampleCAPI(int argc, char** argv) {

  // ---- Check And Setup Shared Error Mechanism with the .dll -----------------
  // Check if .dll has errors, during it's construction!
  char* dllErrorStr;
  if (0!=ExampleCAPI_error((void**)&dllErrorStr)) {
    dbg_(63,"dll has errors. Return error string:\n"<<dllErrorStr)
    ExampleCAPI_clearErrors();
    dbg_(63,"dll errors cleared. Continue...\n")
  }
  // Set .dll's CECS to use the current CECS thus errors in .dll to be
  // recording at the executable's CECS. (Comment to see the difference)
  ExampleCAPI_setcecs(__ECSOBJ__.cecs());
  // ---------------------------------------------------------------------------

  _ERRI(0!=TestExampleCAPI_LoadConfigParameters(string(argv[1])),"Failed to load config file [%s]",argv[1]);

  // Get .dll version
  char* dllVersion;
  _ERRI(0!=ExampleCAPI_version((void**)&dllVersion),"Failed to get .dll version!")
  std::cout << "= Library [ExampleCAPI.dll]: Version: " <<dllVersion<<std::endl;

  dbg_(63,"InputValue = "<<InputValue)

  // Execute .dll functions
  try {
    _ERRI(0!=ExampleCAPI_Initialize(), " ExampleCAPI:: Initialize failed")
    _ERRI(0!=ExampleCAPI_Process(), " ExampleCAPI:: Process failed")
    _ERRI(0!=ExampleCAPI_Shutdown(), " ExampleCAPI:: Shutdown failed")
  } catch(std::exception &e) { _ERRI(1,"Exception captured:\n%s",e.what()) }
  return 0;
}
