#include <Common.hpp>
#include <mutex>

using namespace std;
using namespace vkp;
using namespace vkpConfigReader;

CECS_MODULE("CLIReader")

class TestCLIReaderCLIReader : public vkpConfigReader::_baseDataLoader {
  public:
  int testId;
  bool enabled;
  std::string confFile;
  int frames;
  float timemsec;

  TestCLIReaderCLIReader() {
    testId=0;
    enabled=false;
  }

  void str() {
    for (size_t i=0; i < _argv.size(); i++) {
      dbg_(63,"_argv["<<i<<"]: ["<<_argv[i]<<"]")
    }
    dbg_(63,"testId: "<<testId)
    dbg_(63,"enabled: "<<enabled)
    dbg_(63,"confFile: "<<confFile)
    dbg_(63,"frames: "<<frames)
    dbg_(63,"timemsec: "<<timemsec)
  }

  std::vector<std::string>& getCheckParamList() {
    static std::vector<std::string> CheckParamList = {
      "frames","timemsec"
    };
    return CheckParamList;
  }

  int loadDataSection(cfg_type& cfgData) {
    vkpConfigReaderLOADPARAM(testId)
    vkpConfigReaderLOADPARAM(enabled)
    vkpConfigReaderLOADPARAM(confFile)
    vkpConfigReaderLOADPARAM(frames)
    vkpConfigReaderLOADPARAM(timemsec)
    return 0;
  }
};

TestCLIReaderCLIReader confCLI;


int Test_CLIReader(int argc, char** argv) {
  _ERRI(0!=confCLI.readCommandLine(argc, argv),"Failed to read command line!")
  confCLI.str();
  return 0;
}
