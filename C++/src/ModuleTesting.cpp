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
#include <mutex>

using namespace std;
using namespace vkp;
using namespace vkpConfigReader;

CECS_MODULE("ModuleTesting")


static vector<stringstream> vResultStringStream;
static vector<int> vReturnStatus;
static vector<float> vTestTimeInMSec;
static string testSuccessCompletionString;
static int info_kVerboseLevel_ = -1;



// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// Using PIPE to re-call the same program with different configuration.
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
int ModuleTesting_sysexec(const char* cmd, int testIdx) {
  stringstream& ss = vResultStringStream[testIdx]; ss.str("");
  int& returnStatus = vReturnStatus[testIdx];
	std::array<char, 1024> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

  returnStatus = -1;
  try {
  _ERRO(!pipe, {returnStatus = -9999; return -1; }, "Failed to open system pip() with command: [%s]", cmd)

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
			result = buffer.data();
      auto p = result.rfind("\n");
      if (p != string::npos) result = result.substr(0,p);
      ss << result << endl;
      if (returnStatus==0) {
        returnStatus = -9;
        ss << "\n** ModuleTesting-ERROR: Extra data found after a test completed **\n";
        return -2;
        break;
      }
      if (0==result.compare(testSuccessCompletionString)) returnStatus = 0;
	}
  } catch (std::exception& e) { returnStatus = -8; }
	return 0;
}








// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// Defining Custom Configuration Data for this operation (for .cfg file)
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
class ModuleTesting_ConfigData : public vkpConfigReader::_baseDataLoader {
  public:
  int DbgVerboseLevel;
  std::string executableFile;
  int inParallelTests;
  std::string unitTestCSVFile;
  bool displayPassedTestResults;
  bool displayFailedTestResults;
  std::string logPassedOutputFile;
  std::string logFailedOutputFile;
  std::string testSuccessCompletionString;
  std::vector<std::string>& getCheckParamList();
  int loadDataSection(vkpConfigReader::cfg_type& cfgData);
};
std::vector<std::string>& ModuleTesting_ConfigData::getCheckParamList() {
  static std::vector<std::string> CheckParamList = {
    "DbgVerboseLevel","executableFile","inParallelTests",
    "unitTestCSVFile",
    "displayPassedTestResults","displayFailedTestResults",
    "logPassedOutputFile","logFailedOutputFile",
    "testSuccessCompletionString"
  }; return CheckParamList;
}
int ModuleTesting_ConfigData::loadDataSection(vkpConfigReader::cfg_type& cfgData) {
  vkpConfigReaderLOADPARAM(DbgVerboseLevel)
  vkpConfigReaderLOADPARAM(executableFile)
  vkpConfigReaderLOADPARAM(inParallelTests)
  vkpConfigReaderLOADPARAM(unitTestCSVFile)
  vkpConfigReaderLOADPARAM(displayPassedTestResults)
  vkpConfigReaderLOADPARAM(displayFailedTestResults)
  vkpConfigReaderLOADPARAM(logPassedOutputFile)
  vkpConfigReaderLOADPARAM(logFailedOutputFile)
  vkpConfigReaderLOADPARAM(testSuccessCompletionString)
  return 0;
};











// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// Setup Thread required data and Trhead Process function - for TPool
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
typedef struct SThreadData_ModuleTesting {
  int testIdx;
  int testId;
  int testEnabled;
  int expectedReturnStatus;
  string command;
} SThreadData_ModuleTesting;

static std::mutex qmtx;
static int totalEnabledTests = 0;
static int completedEnabledTests = 0;
void* Thread_ModuleTesting(void* _data) {
  SThreadData_ModuleTesting* data = (SThreadData_ModuleTesting*)_data;
  int testIdx = data->testIdx;
  int testId = data->testId;
  int expectedReturnStatus = data->expectedReturnStatus;
  const string& command = data->command;
  _CERRO({return NULL;},"Test-#%i Failed before start!: Errors already captured", testIdx)
  vkpTimer T;
  T.start();
  ModuleTesting_sysexec(command.c_str(), testIdx);
  T.stop();
  { std::lock_guard<std::mutex> lock(qmtx);
    completedEnabledTests++;
    stringstream ss;
    bool isSuccess = false;
    const string expectedReturnStatusStr = (expectedReturnStatus==1) ? string("(+)") : string("(-)");
    if (((vReturnStatus[testIdx]==0) && (expectedReturnStatus!=0)) ||
        ((vReturnStatus[testIdx]!=0) && (expectedReturnStatus==0))) isSuccess = true;
    vReturnStatus[testIdx] = -(int)(!isSuccess);
    if (isSuccess) { ss << "[+]"<<expectedReturnStatusStr<<"[Passed] TestID: ["; }
    else { ss << "[-]"<<expectedReturnStatusStr<<"[Failed] TestID: ["; }
    ss << testId <<"] ("<<completedEnabledTests<<" / "<<totalEnabledTests<<") :: time: "<<T.getAverageTime()<<" msec";
    info_(2,ss.str()) // Print these results only if info_kVerboseLevel_ >= 2.
  }
  return NULL;
}











// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// A class to handle the Module Testing.
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
class CModuleTesting {
  public:
  int passedTests;
  int failedTests;
  ModuleTesting_ConfigData confData;
  CModuleTesting();
  ~CModuleTesting();
  int initialize(std::string confFile);
  int execute();
  std::string getResult();
  int shutdown();
  private:
  PThreadPool TPool;
  vector<SThreadData_ModuleTesting> vThreadData;
  vkpCSVHandler csv;
  vkpTimer totalTestTime;
  vector<vkpCSVHandlerData>* vTestIDPtr;
  vector<vkpCSVHandlerData>* vTestEnabledPtr;
  vector<vkpCSVHandlerData>* vTestReturnStatusPtr;
  vector<vkpCSVHandlerData>* vTestConfigFilePtr;
  vector<vkpCSVHandlerData>* vTestDescriptionPtr;
}; // class ModuleTesting


CModuleTesting::CModuleTesting(){
  totalTestTime.name = string("Total Testing Time");
  vTestDescriptionPtr = nullptr;
}

CModuleTesting::~CModuleTesting(){
  shutdown();
}


int CModuleTesting::initialize(std::string confFile) {
  _ERRI(0!=confData.loadConfigFile(confFile),"Failed to load configuration file!")

  const int kThreadsToUseForParallelTests = confData.inParallelTests;
  testSuccessCompletionString = confData.testSuccessCompletionString;

  _ERRI(0!=TPool.Initialize(Thread_ModuleTesting, kThreadsToUseForParallelTests, -1),"Failed to initialize thread pool")

  _ERRI(0!=csv.Initialize(" ","\""), "Initialize error.")
  vector<unsigned char> headerTypes{0, 0, 0, 2, 2};
  _ERRI(0!=csv.setHeaders(headerTypes),"Failed to set datatypes of headers")
  _ERRI(0!=csv.loadFile(confData.unitTestCSVFile, false),"Failed to load [%s] file.",confData.unitTestCSVFile.c_str())


  _ERRI(0!=csv.getDataColumnPtr((size_t)0,vTestIDPtr),"Failed to access first column")
  _ERRI(0!=csv.getDataColumnPtr((size_t)1,vTestEnabledPtr),"Failed to access second column")
  _ERRI(0!=csv.getDataColumnPtr((size_t)2,vTestReturnStatusPtr),"Failed to access third column")
  _ERRI(0!=csv.getDataColumnPtr((size_t)3,vTestConfigFilePtr),"Failed to access fourth column")
  _ERRI(0!=csv.getDataColumnPtr((size_t)4,vTestDescriptionPtr),"Failed to access fifth column")
  _ERRI(vTestIDPtr==nullptr,"vTestIDPtr==nullptr")
  _ERRI(vTestEnabledPtr==nullptr,"vTestEnabledPtr==nullptr")
  _ERRI(vTestReturnStatusPtr==nullptr,"vTestReturnStatusPtr==nullptr")
  _ERRI(vTestConfigFilePtr==nullptr,"vTestConfigFilePtr==nullptr")
  _ERRI(vTestDescriptionPtr==nullptr,"vTestDescriptionPtr==nullptr")

  // Generate test for the threads.
  const int ktotalTests = vTestIDPtr->size();
  vThreadData.resize(ktotalTests);
  vResultStringStream.resize(ktotalTests);
  vReturnStatus.resize(ktotalTests);
  vTestTimeInMSec.resize(ktotalTests,0);
  for (int testIdx = 0; testIdx < ktotalTests; testIdx++) {
    const int ktestId = (*vTestIDPtr)[testIdx].i;
    vThreadData[testIdx].testIdx=testIdx;
    vThreadData[testIdx].testId=ktestId;
    vThreadData[testIdx].testEnabled=(*vTestEnabledPtr)[testIdx].i;
    vThreadData[testIdx].expectedReturnStatus = (*vTestReturnStatusPtr)[testIdx].i;
    vThreadData[testIdx].command = confData.executableFile + string(" ") + (*vTestConfigFilePtr)[testIdx].s;
  }

  totalTestTime.reset();
  return 0;
}

int CModuleTesting::execute() {
  totalEnabledTests = 0;
  for (auto& v : vThreadData) {
    if (v.testEnabled <= 0) continue;
    totalEnabledTests++;
  }
  std::cout<<"Enabled Tests = "<<totalEnabledTests<<" / "<<vThreadData.size()<<std::endl;
  info_(2,"\n------- START TESTING -------")
  completedEnabledTests = 0;
  totalTestTime.start();
  for (auto& v : vThreadData) {
    if (v.testEnabled > 0) {
      TPool.AddTask(&v);
    }
  }
  TPool.Wait();
  totalTestTime.stop();
  info_(2,"----- TESTING COMPLETED ------\n")
  return 0;
}

std::string CModuleTesting::getResult() {
  _ERRO(vTestDescriptionPtr==nullptr,{ return string("ERROR"); }, "vTestDescriptionPtr==nullptr")
  stringstream ss;
  std::cout<<"\n>>>>>>> TEST RESULTS <<<<<<<"<<std::endl;
  const int ktotalTest = vResultStringStream.size();
  ss << "MODULE-TESTING: Total Tests = ["<<ktotalTest<<"]\n";

  int enabledTests = 0;
  for (const auto& v : vThreadData) { if (v.testEnabled > 0) enabledTests++; }
  ss << "MODULE-TESTING: - Enabled Tests = ["<<enabledTests<<"]\n";

  ofstream logOutPassed;
  ofstream logOutFailed;
  if (confData.logPassedOutputFile.length() > 2) {
    logOutPassed.open(confData.logPassedOutputFile);
  }
  if (confData.logFailedOutputFile.length() > 2) {
    logOutFailed.open(confData.logFailedOutputFile);
  }

  passedTests = 0;
  failedTests = 0;
  for (int i=0; i < ktotalTest; i++) {
    const auto& v = vThreadData[i];
    if (v.testEnabled <= 0) continue;
    const string expectedReturnStatus = ((*vTestReturnStatusPtr)[i].i==1) ? string("(+)") : string("(-)");
    if (vReturnStatus[i]==0) {
      ss <<"   [+]"<<expectedReturnStatus<<"[Passed]: TestID = ["<<v.testId<<"] > "<<(*vTestDescriptionPtr)[i].s<<"\n";
      if (confData.displayPassedTestResults==true) {
        ss << "   ----------------------------------------------------------------------------------------------------------------------------------\n";
        ss << vResultStringStream[i].str();
        ss << "   ----------------------------------------------------------------------------------------------------------------------------------\n";
      }
      if (confData.logPassedOutputFile.length() > 2) {
        logOutPassed << "\n\n\n==============================================================\n";
        logOutPassed << "[+]"<<expectedReturnStatus<<"[Passed]: TestID = ["<<v.testId<<"] > "<<(*vTestDescriptionPtr)[i].s<<"\n";
        logOutPassed << "   ----------------------------------------------------------------------------------------------------------------------------------\n";
        logOutPassed << vResultStringStream[i].str();
        logOutPassed << "   ----------------------------------------------------------------------------------------------------------------------------------\n";
      }
      passedTests++;
    } else {
      ss <<"   [-]"<<expectedReturnStatus<<"[Failed]: TestID = ["<<v.testId<<"] > "<<(*vTestDescriptionPtr)[i].s<<"\n";
      if (confData.displayFailedTestResults==true) {
        ss << "   ----------------------------------------------------------------------------------------------------------------------------------\n";
        ss << vResultStringStream[i].str();
        ss << "   ----------------------------------------------------------------------------------------------------------------------------------\n";
      }
      if (confData.logFailedOutputFile.length() > 2) {
        logOutFailed << "\n\n\n==============================================================\n";
        logOutFailed << "[-]"<<expectedReturnStatus<<"[Failed]: TestID = ["<<v.testId<<"] > "<<(*vTestDescriptionPtr)[i].s<<"\n";
        logOutFailed << "   ----------------------------------------------------------------------------------------------------------------------------------\n";
        logOutFailed << vResultStringStream[i].str();
        logOutFailed << "   ----------------------------------------------------------------------------------------------------------------------------------\n";
      }
      failedTests++;
    }
  }
  ss << "MODULE-TESTING: - Passed Tests = ["<<passedTests<<"] out of "<<enabledTests<<"\n";
  if (failedTests > 0) {
    ss << "MODULE-TESTING: - Failed Tests = ["<<failedTests<<"] out of "<<enabledTests<<"\n";
  }
  ss << "MODULE-TESTING: "<<totalTestTime.str()<<"\n";
  ss << ">>>>>>>==============<<<<<<<"<<std::endl;
  return ss.str();
}

int CModuleTesting::shutdown() {
  TPool.Shutdown();
  vTestDescriptionPtr=nullptr;
  return 0;
}











// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// The actual ModuleTesting entry process / function.
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
int ModuleTesting(int argc, char** argv) {
	static pthread_mutex_t q_mtx_CECS = PTHREAD_MUTEX_INITIALIZER;
	*(pthread_mutex_t**)CECS_MUTEXPTR = &q_mtx_CECS;
	CECS_SETFUNC_LOCK( [](){ pthread_mutex_lock(*(pthread_mutex_t**)CECS_MUTEXPTR);} );
	CECS_SETFUNC_UNLOCK( [](){ pthread_mutex_unlock(*(pthread_mutex_t**)CECS_MUTEXPTR);});
	_CHECKRI_

  CModuleTesting utesting;

  _ERRI(0!=utesting.initialize(string(argv[1])),"Failed to initialize ModuleTesting")

  info_kVerboseLevel_ = utesting.confData.DbgVerboseLevel;

  _ERRI(0!=utesting.execute(),"Failed to execute ModuleTesting")

  string testsResultString = utesting.getResult(); _CHECKRI_

  info_(1,testsResultString) // print result only if info_kVerboseLevel_ is >= 1

  _ERRI(0!=utesting.shutdown(),"Failed to shutdown ModuleTesting")

  _ERRI(utesting.failedTests != 0,"Tests Failed --> %i / %i",utesting.failedTests,(utesting.failedTests + utesting.passedTests))

  return 0;
}
