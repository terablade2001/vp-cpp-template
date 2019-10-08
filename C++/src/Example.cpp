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
#include <unistd.h>

//CECS / CCEXP / vkp_Config variables.
static CECS __ECSOBJ__("Example");
static CCEXP::CCEXP DBG;
static cfg_type cfg_data;

// Threading setup (PThreadPool)
#define MAX_THREADS (4)
#define MAX_TASKS (40)
static vkpProgressBar vkpPB("[","]","=",">",0,MAX_TASKS,20);
static int progressCnt = 0;
static pthread_mutex_t q_mtx = PTHREAD_MUTEX_INITIALIZER;
typedef struct SThread_data {
	int task_id;
} SThread_data;
static SThread_data Thread_Data[MAX_TASKS];
void* Thread_Execute(void* _data) {
	SThread_data* data = (SThread_data*)_data;
	int task_id = data->task_id;
	pthread_mutex_lock(&q_mtx);
		_ERRO(vkpPB.Update(progressCnt++),{ pthread_mutex_unlock(&q_mtx); return NULL; },"ProgressBar failed to update")
		usleep(50000);
		CCEXP::AddVal<int>(DBG,"task-id",task_id);
		 _CHECKRO_({ pthread_mutex_unlock(&q_mtx); return NULL; } )
	pthread_mutex_unlock(&q_mtx);
	return NULL;
}





int Example(int argc, char** argv) {
  _ERRI(2!=argc,"One configuration file is required as input argument! Got (%i)", argc)

  // Load config file
  string cfgFilePath(argv[1]);
  _ERRI(cfg_LoadFile(cfgFilePath.c_str(), cfg_data),
    "Failed to load config file [%s]", cfgFilePath.c_str());

  // Load and check Configuration file
  std::vector<std::string> CheckParamList = {"ExportTestFile"};
  std::string NotExistingParams;
  int r = cfg_CheckParams(cfg_data, CheckParamList, NotExistingParams);
  _ERRSTR(r,{
    ss << "The following required parameters were not found in configuration file: \n >> [";
    ss << NotExistingParams +"]";
  })
  _ERRI(r,"Failed to initialize from Configuration file...")

  // Load params from the config file
  string ExportTestFile;
  cfg_GetParam(cfg_data, "ExportTestFile", ExportTestFile);

  // Create the CCEXP object for recording
  CCEXP::Initialize(DBG,ExportTestFile.c_str());
  CCEXP::AddTable<char>(DBG,"Message","char");
  CCEXP::AddTable<int>(DBG,"task-id","int32");
  
  string msg("vp-cpp-template test file!");
  CCEXP::AddRow<char>(DBG,"Message",const_cast<char*>(msg.c_str()),msg.size());

  cout << "Progress: ";
  vkpPB.Start(); progressCnt = 0;
  // Run the threaded code.
  PThreadPool TPool;
  TPool.Initialize(Thread_Execute, MAX_THREADS, -1);
  for (int tid = 0; tid < MAX_TASKS; tid++)
    Thread_Data[tid].task_id = tid;
  for (int tid = MAX_TASKS-1; tid >= 0; tid--)
    TPool.AddTask(&Thread_Data[tid]);
  TPool.Wait();
  TPool.Shutdown();
  cout << endl;
  _CHECKRI_

  // Store results.
  CCEXP::StoreData(DBG); _CHECKRI_
  CCEXP::Reset(DBG); _CHECKRI_

  _ERRI(1,"[EXAMPLE forced Error] -> To see how CECS works! ;)")
  return 0;
}