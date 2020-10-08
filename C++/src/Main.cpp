// MIT License

// Copyright (c) 2017 - 2019 Vasileios Kon. Pothos (terablade2001)
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

#include <Example.hpp>

#include "../../BuildVersion/BuildVersion.hpp"
#include <vkpBuildVersioner.hpp>

using namespace std;
using namespace vkp;
using namespace vkpConfigReader;

// Versioning and CECS
static vkpBuildVersioner BV1(1, VERSION_NUMBER);
CECS_MAIN_MODULE("Main","CECS::Project")


// Loading [processType] from configuration file.
static string processType;
int acquireTypeOfProcess(string&& file);


int main(int argc, char** argv) {
  // Set ECS display sections, and clear default obj's errors (optional)
  _ECSFORMAT(1,0,0,1,1,1,1,1) __ECSOBJ__.clear();
  // Enable all 32 Signals in case of CECSDEBUG flag.
  for (int i=0; i < 32; i++) _SETSIGNAL(i)

  // Show program version.
  cout << endl << "=======================================================================";
  cout << endl << "= VP-CPP-TEMPLATE (https://github.com/terablade2001/vp-cpp-template)  =";
  cout << endl << "= Program version: " << BV1.version << "                                            =";
  cout << endl << "=======================================================================";
  cout << endl;

  try {
    // This setup takes a configuration file and depending it's 'processType'
    // flag it execute a specific test/development function.
    _ERRT(2!=argc,"Use only one configuration file as parameter. Got [%i] parameters, need only 1.",argc-1)
    _ERRT(0!=acquireTypeOfProcess(string(argv[1])),"Failed to identify the requested process type.")
    cout << "ProcessType: " << processType << endl;

    if (0==processType.compare("Example")) {
      _ERRT(0!=Example(argc, argv),"Failed to run \"Example()\" function!")
    } else {
      _ERRSTR(1,{
        ss << "Unknown process type: [" << processType << "]" << endl;
        ss << "Valid Case-Sensitive process types are: "<<endl;
        ss << " - [Example]" << endl;
      })
      _ERRT(1,"Abort due to unknown process type.")
    }

    cout << "Program completed." << endl;
  } catch(std::exception &e) {
    string eColorStart; string eColorFix;

    // Enable the following line for colored error output
    // eColorStart = string("\033[1;36m"); eColorFix = string("\033[m");
    std::cerr<< std::endl<<"(*) Exception occurred: "<< std::endl << eColorStart <<e.what()<< eColorFix << std::endl;
  }
  return 0;
}




int acquireTypeOfProcess(string&& file) {
  cfg_type cfg_data;
  _ERRI(0!=cfg_LoadFile(file.c_str(), cfg_data),"Failed to load config file: [%s]",file.c_str())
  std::vector<std::string> CheckParamList = { "ProcessType" };
  std::string NotExistingParams;
  int r = cfg_CheckParams(cfg_data, CheckParamList, NotExistingParams);
  _ERRSTR(r!=0,{ ss << "The following parameters were not found: \n" << "[" << NotExistingParams << "]"; })
  _ERRI(r!=0,"Missing parameter in configuration file [%s]",file.c_str())
  _ERRI(0!=cfg_GetParam(cfg_data, "ProcessType", processType),"Failed to process parameters [ProcessType] in file [%s]",file.c_str())
  return 0;
}
