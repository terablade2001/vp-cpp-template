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

#include "ModuleTests/include/Example.hpp"
#include "ModuleTests/include/TestExampleCAPI.hpp"
#include "ModuleTests/include/TestVkpCSVHandler.hpp"

using namespace std;
using namespace vkp;
using namespace vkpConfigReader;

// Versioning and CECS
static vkpBuildVersioner BV1(1, VERSION_NUMBER);
CECS_MAIN_MODULE("Main","CECS::Project")

class MainCLIReader : public vkpConfigReader::_baseDataLoader {
  public:
  bool cli;
  int testId;
  int v;
  bool version;
  std::string ProcessType;
  MainCLIReader() { cli=false; testId=std::numeric_limits<int>::min(); ProcessType=string("-ProcessType NOT SET-"); v = 99999; version=false;}
  std::vector<std::string>& getCheckParamList() {
    static std::vector<std::string> CheckParamList = { };
    return CheckParamList;
  }
  int loadDataSection(cfg_type& cfgData) {
    vkpConfigReaderLOADPARAM(cli)
    vkpConfigReaderLOADPARAM(testId)
    vkpConfigReaderLOADPARAM(ProcessType)
    vkpConfigReaderLOADPARAM(v)
    vkpConfigReaderLOADPARAM(version)
    return 0;
  }
};
static MainCLIReader mainCLIReader;
static int info_kVerboseLevel_ = 99999;

int ModuleTesting(int argc, char** argv);

int Test_CLIReader(int argc, char** argv);

int main(int argc, char** argv) {
  // Set ECS display sections, and clear default obj's errors (optional)
  _ECSFORMAT(1,0,0,1,1,1,1,1) __ECSOBJ__.clear();
  // Enable all 32 Signals in case of CECSDEBUG flag.
  for (int i=0; i < 32; i++) _SETSIGNAL(i)

  try {
    _ERRT(0!=mainCLIReader.readCommandLine(argc,argv),"Failed to parse CLI input.")

    if (mainCLIReader.version) { std::cout << BV1.version << std::endl; return 0; }

    info_kVerboseLevel_ = mainCLIReader.v;
    info_(1,"\n=======================================================================")
    info_(1,"= VP-CPP-TEMPLATE (https://github.com/terablade2001/vp-cpp-template)  =")
    info_(1,"= Program version: " << BV1.version << "                                            =")
    info_(1,"=======================================================================")

    const bool kinputIsCLI = mainCLIReader.cli; // Check's '--cli' flag in the CLI's input.

    if (kinputIsCLI)
    { // if '--cli' flag is detected, then no configuration file will be processed.
      // Add custom code here, if you are using CLI.
      const int kCLITestId = mainCLIReader.testId;
      _ERRT(kCLITestId == std::numeric_limits<int>::min(),"CLI input: No '-testId' directive detected. Use i.e. '-testId 0' to run the example!")
      if (kCLITestId == 0) {
        _ERRT(0!=Test_CLIReader(argc, argv),"Failed to run \"Test_CLIReader\" function!")
      } else {
        _ERRT(1,"Unknown CLI input value: -testId = %i",kCLITestId)
      }
    }

    else

    { // If '--cli' command is missing, then we expect a configuration file!
      // This setup takes a configuration file and depending it's 'processType'
      // flag it execute a specific test/development function.
      const auto& processType = mainCLIReader.ProcessType;
      _ERRT(argc < 2,"Arguments Error:\n * The '--cli' flag was not detected -> Enabled Configuration Files mode.\n * Got [%i] CLI input arguments.\n * \t-> Use at least 1 input parameter (config. file's name).",argc-1)
      _ERRT(0!=mainCLIReader.loadConfigFile(mainCLIReader._argv[1]),"Failed to load config file [%s]",mainCLIReader._argv[1].c_str())
      _ERRT(0==processType.compare("-ProcessType NOT SET-"),"Failed to identify the requested process type ('--cli' not set: Using Configuration Files mode)")

      info_(1,"ProcessType: " << processType);
      info_(1,"=======================================================================");

      if (0==processType.compare("ModuleTesting")) {
        _ERRT(0!=ModuleTesting(argc, argv),"Function \"ModuleTesting()\" failed!")
      } else if (0==processType.compare("Example")) {
        _ERRT(0!=Example(argc, argv),"Failed to run \"Example()\" function!")
      } else if (0==processType.compare("TestExampleCAPI")) {
        _ERRT(0!=TestExampleCAPI(argc, argv),"Failed to run \"TestExampleCAPI\" function!")
      } else if (0==processType.compare("TestVkpCSVHandler")) {
        _ERRT(0!=TestVkpCSVHandler(argc, argv),"Failed to run \"TestVkpCSVHandler\" function!")
      } else {
        _ERRSTR(1,{
          ss << "Unknown process type: [" << processType << "]" << endl;
          ss << "Valid Case-Sensitive process types are: "<<endl;
          ss << " - [ModuleTesting]" << endl;
          ss << " - [Example]" << endl;
          ss << " - [TestExampleCAPI]" << endl;
          ss << " - [TestVkpCSVHandler]" << endl;
        })
        _ERRT(1,"Abort due to unknown process type.")
      }
    }

    info_(1,"=*-*= Program completed =*-*=")

  } catch(std::exception &e) {
    string eColorStart; string eColorFix;
    // Enable the following line for colored error output
    // eColorStart = string("\033[1;36m"); eColorFix = string("\033[m");
    std::cout<< std::endl<<"(*) Exception occurred: "<< std::endl << eColorStart <<e.what()<< eColorFix << std::endl;
    return -1;
  }

  return 0;
}
