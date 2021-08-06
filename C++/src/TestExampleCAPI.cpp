#include "include/TestExampleCAPI.hpp"

CECS_MODULE("TestExampleCAPI")

using namespace std;
using namespace vkp;
using namespace vkpConfigReader;

class TestExampleCAPIConfigData : public vkpConfigReader::_baseDataLoader {
  public:
  float InputValue;

  std::vector<std::string>& getCheckParamList() {
    static std::vector<std::string> CheckParamList = {
      "InputValue"
    };
    return CheckParamList;
  }

  int loadDataSection(cfg_type& cfgData) {
    vkpConfigReaderLOADPARAM(InputValue)
    return 0;
  }
};


static TestExampleCAPIConfigData confData;


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

  _ERRI(0!=confData.loadConfigFile(argv[1]),"Failed to load config file [%s]",argv[1])

  // Get .dll version
  char* dllVersion;
  _ERRI(0!=ExampleCAPI_version((void**)&dllVersion),"Failed to get .dll version!")
  std::cout << "= Library [ExampleCAPI.dll]: Version: " <<dllVersion<<std::endl;

  dbg_(63,"InputValue = " << confData.InputValue)

  // Execute .dll functions
  try {
    _ERRI(0!=ExampleCAPI_Initialize(), " ExampleCAPI:: Initialize failed")
    _ERRI(0!=ExampleCAPI_Process(), " ExampleCAPI:: Process failed")
    _ERRI(0!=ExampleCAPI_Shutdown(), " ExampleCAPI:: Shutdown failed")
  } catch(std::exception &e) { _ERRI(1,"Exception captured:\n%s",e.what()) }
  return 0;
}
