// MIT License

// Copyright (c) 2017 - 2020 Vasileios Kon. Pothos (terablade2001)
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

#include "include/Example.hpp"

using namespace std;
using namespace vkp;
using namespace vkpConfigReader;

//CECS / CCEXP / vkp_Config variables.
CECS_MODULE("Example")

static CCEXP::CCEXP DBG;

// Make a circular buffer with 2 cells
static vkpCircularBuffer<int> circBuff(std::string("CircBuff"), 2);
static int64_t circBuffvalue = -100; // Initialize value with -100

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
    // Each time add the value to the circular buffer and increase by 1 the index.
    _ERRO(circBuff.setMove(circBuffvalue++, 1),{ pthread_mutex_unlock(&q_mtx); return NULL; },"Failed to update the circular buffer")
    usleep(50000);
    CCEXP::AddVal<int>(DBG,"task-id",task_id);
     _CHECKRO_({ pthread_mutex_unlock(&q_mtx); return NULL; } )
  pthread_mutex_unlock(&q_mtx);
  return NULL;
}



static string ExportTestFile;

int Example_LoadConfigParameters(string&& file) {
  _ERRINF(1,"config file: [%s]", file.c_str())
  cfg_type cfg_data;
  _ERRI(0!=cfg_LoadFile(file.c_str(), cfg_data),"Failed to load config file")
  std::vector<std::string> CheckParamList = {
    "ExportTestFile"
  };
  std::string NotExistingParams;
  int r = cfg_CheckParams(cfg_data, CheckParamList, NotExistingParams);
  _ERRSTR(r!=0,{ ss << "The following parameters were not found: \n" << "[" << NotExistingParams << "]"; })
  _ERRI(r!=0,"Missing parameter in configuration file.")
  _ERRI(0!=cfg_GetParam(cfg_data, "ExportTestFile", ExportTestFile),"Failed to process parameters [ExportTestFile]")
  _ECSCLS_
  return 0;
}






int Example(int argc, char** argv) {
  dbg_(63,"Example() called")
  // Define a Timers map
  vkpTimersMap perfTimers("Example Timers");
  auto& T00 = perfTimers.addTimer("00 - Loading configuration");
  perfTimers.addTimer("01 - Loading and setup");
  perfTimers.addTimer("02 - Threading time");
  // Define a simple timer.
  vkpTimer storingTimer("storing and cleaning ccexp");

  T00.start();
    _ERRI(0!=Example_LoadConfigParameters(string(argv[1])),"Failed to load config file [%s]",argv[1]);
  T00.stop();

  // Condition debug statements.
  dbg_c(0,argc==2,"Entered Example (with argc == 2)...")
  dbg_c(1,argc==2,"Entered Example (with argc == 2) (dbg OR flag 0b10)...")
  dbg_c(0,argc==1,"Entered Example (with argc == 1)...")

  // Define our own thread sync system for CECS.
  static pthread_mutex_t q_mtx_CECS = PTHREAD_MUTEX_INITIALIZER;
  *(pthread_mutex_t**)CECS_MUTEXPTR = &q_mtx_CECS;
  CECS_SETFUNC_LOCK( [](){ pthread_mutex_lock(*(pthread_mutex_t**)CECS_MUTEXPTR);} );
  CECS_SETFUNC_UNLOCK( [](){ pthread_mutex_unlock(*(pthread_mutex_t**)CECS_MUTEXPTR);});
  _CHECKRI_

  { vkpTimer& T = perfTimers.getTimer("01 - Loading and setup"); T.start();

    // Create the CCEXP object for recording
    CCEXP::Initialize(DBG,ExportTestFile.c_str());
    CCEXP::AddTable<char>(DBG,"Message","char");
    CCEXP::AddTable<int>(DBG,"task-id","int32");

    string msg("vp-cpp-template test file!");
    CCEXP::AddRow<char>(DBG,"Message",const_cast<char*>(msg.c_str()),msg.size());

    _ERRI(circBuff.allSetTo(0),"Failed to initialize the circular Buffer");
    T.stop();
  }

  { vkpTimer& T = perfTimers.getTimer("02 - Threading time"); T.start();
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
    T.stop();
  }

  storingTimer.start();
  // Store results.
  CCEXP::StoreData(DBG); _CHECKRI_
  CCEXP::Reset(DBG); _CHECKRI_
  storingTimer.stop();

  // Display the results of the circlular buffer cells.
  dbg_(63,"CircBuffValues: [0]:"<<circBuff.get(0)<<", [1]:"<<circBuff.get(1))

  // Display timers info
  cout << perfTimers.str() << endl;
  cout << storingTimer.str() << endl;

  // In release mode, users can disable timers.
  perfTimers.enabled=false;
  storingTimer.enabled=false;
  cout << perfTimers.str() << endl;
  cout << storingTimer.str() << endl;

  // Play a bit with the vkp::opmlCPP class;
  vkp::opmlCPP opml("Debug","Debug.opml");
  opml.add("Branch A");
  opml.push("Branch B");
  for (int i = 0; i < 5; i++) {
    opml.push(opml.s<<"Branch C-"<<i);
      for (int j = i; j < i+3; j++) {
        opml.add(opml.s<<"Value j = "<<j);
      }
    opml.pop();
  }
  opml.pop();
  opml.add("Branch D");

  _ERRI(1,"[EXAMPLE forced Error] -> To see how CECS works! ;)")
  return 0;
}
