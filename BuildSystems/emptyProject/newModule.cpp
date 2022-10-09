#include <Common.hpp>

using namespace std;
using namespace vkp;
using namespace vkpConfigReader;

CECS_MODULE("newModule")

static int info_kVerboseLevel_ = 99999;
class newModule_ConfData : public vkpConfigReader::_baseDataLoader {
  public:
  int v;
  newModule_ConfData() { v = 99999; }
  std::vector<std::string>& getCheckParamList() {
    static std::vector<std::string> CheckParamList = { };
    return CheckParamList;
  }
  int loadDataSection(cfg_type& cfgData) {
    vkpConfigReaderLOADPARAM(v)
    info_kVerboseLevel_=v;
    return 0;
  }
};

static newModule_ConfData confData;



int Test_newModule(int argc, char** argv) {
  _ERRI(0!=confData.readCommandLine(argc, argv),"Failed to read command line!")
  info_(3,"---------------")
  info_(2,"info_kVerboseLevel_ = "<<info_kVerboseLevel_)
  info_(1,"newModule:: ok!")
  return 0;
}
