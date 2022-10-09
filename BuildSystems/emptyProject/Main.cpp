// MIT License

// Copyright (c) 2016 - 2022 Vasileios Kon. Pothos (terablade2001)
// https://github.com/terablade2001/vp-cpp-template

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <Common.hpp>

using namespace std;
using namespace vkp;
using namespace vkpConfigReader;

static vkpBuildVersioner BV1(1, VERSION_NUMBER);
CECS_MAIN_MODULE("Main","CECS::Project")

int ModuleTesting(int argc, char** argv);

class CMainCLIReader : public vkpConfigReader::_baseDataLoader {
  public:
  bool cli;
  int t;
  int v;
  bool version;
  std::string ProcessType;
  CMainCLIReader() { cli=false; t=-1; ProcessType=string("-ProcessType NOT SET-"); v = 99999; version=false;}
  std::vector<std::string>& getCheckParamList() {
    static std::vector<std::string> CheckParamList = { };
    return CheckParamList;
  }
  int loadDataSection(cfg_type& cfgData) {
    vkpConfigReaderLOADPARAM(cli)
    vkpConfigReaderLOADPARAM(t)
    vkpConfigReaderLOADPARAM(ProcessType)
    vkpConfigReaderLOADPARAM(v)
    vkpConfigReaderLOADPARAM(version)
    return 0;
  }
};

static CMainCLIReader mainCLIReader;
static int info_kVerboseLevel_ = 99999;

int Test_newModule(int argc, char** argv);

int main(int argc, char** argv) {
  _ECSFORMAT(1,0,0,1,1,1,1,1) __ECSOBJ__.clear();
  for (int i=0; i < 32; i++) _SETSIGNAL(i)

  try {
    _ERRT(0!=mainCLIReader.readCommandLine(argc,argv),"Failed to parse CLI input.")

    if (mainCLIReader.version) { std::cout << BV1.version << std::endl; return 0; }

    info_kVerboseLevel_ = mainCLIReader.v;
    info_(1,"\n=======================================================================")
    info_(1,"= VP-CPP-TEMPLATE (https://github.com/terablade2001/vp-cpp-template)  =")
    info_(1,"= Program version: " << BV1.version << "                                            =")
    info_(1,"=======================================================================")

    const bool kinputIsCLI = mainCLIReader.cli;

    if (kinputIsCLI) {
      const int kCLITestId = mainCLIReader.t;
      if (kCLITestId == 0) {
        _ERRT(0!=Test_newModule(argc, argv),"Call to 'Test_newModule()' failed!")
      } else {
        _ERRT(1,"Unknown CLI input value: -t [=%i].",kCLITestId)
      }
    }

    else

    { const auto& processType = mainCLIReader.ProcessType;
      _ERRT(argc < 2,"Arguments Error:\n * The '--cli' flag was not detected -> Enabled Configuration Files mode.\n * Got [%i] CLI input arguments.\n * \t-> Use at least 1 input parameter (config. file's name).",argc-1)
      _ERRT(mainCLIReader._argv.size() <= 1,"No '--cli' flag with extra arguments provided [%zu] (no config. file)",mainCLIReader._argv.size()-1)
      _ERRT(0!=mainCLIReader.loadConfigFile(mainCLIReader._argv[1]),"Failed to load config file [%s]",mainCLIReader._argv[1].c_str())
      _ERRT(0==processType.compare("-ProcessType NOT SET-"),"Failed to identify the requested process type ('--cli' not set: Using Configuration Files mode)")

      info_(1,"ProcessType: " << processType);
      info_(1,"=======================================================================");

      if (0==processType.compare("ModuleTesting")) {
        _ERRT(0!=ModuleTesting(argc, argv),"Function \"ModuleTesting()\" failed!")
      } else {
        _ERRSTR(1,{
          ss << "Unknown process type: [" << processType << "]" << endl;
          ss << "Valid Case-Sensitive process types are: "<<endl;
          ss << " - [ModuleTesting]" << endl;
        })
        _ERRT(1,"Abort due to unknown process type.")
      }
    }

    info_(1,"=*-*= Program completed =*-*=")

  } catch(std::exception &e) {
    string eColorStart; string eColorFix;
    // eColorStart = string("\033[1;36m"); eColorFix = string("\033[m");
    std::cout<< std::endl<<"(*) Exception occurred: "<< std::endl << eColorStart <<e.what()<< eColorFix << std::endl;
    return -1;
  }

  return 0;
}
