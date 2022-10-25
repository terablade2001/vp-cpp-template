#include <Common.hpp>
#include <mutex>

using namespace std;
using namespace vkp;
using namespace vkpConfigReader;

CECS_MODULE("Test_OpenCV")

static int info_kVerboseLevel_ = 9999;
class TestOpenCVCLIReader : public vkpConfigReader::_baseDataLoader {
  public:
  int v;
  TestOpenCVCLIReader() { v = 9999;}
  std::vector<std::string>& getCheckParamList() {
    static std::vector<std::string> CheckParamList = { };
    return CheckParamList;
  }

  int loadDataSection(cfg_type& cfgData) {
    vkpConfigReaderLOADPARAM(v)
    info_kVerboseLevel_ = v;
    return 0;
  }
};
static TestOpenCVCLIReader confCLI;

int Test_OpenCV(int argc, char** argv) {
  _ERRI(0!=confCLI.readCommandLine(argc, argv),"Failed to read command line!")
  #ifdef VP_CPP_TEMPLATE__USING_OPENCV
  info_(1,"* Using OpenCV ["<<CV_MAJOR_VERSION<<"."<<CV_MINOR_VERSION<<"]")
  try {
    cv::Mat img = cv::Mat::zeros(cv::Size(32,32),CV_8UC1);
    for (int y=0; y < 32; y++) {
      auto p = img.ptr<uint8_t>(y);
      for (int x = 0; x < 32; x++) { p[x] = x*8; }
    }
    cv::imwrite("testOpenCV_result.bmp",img);
  } catch (std::exception& e) { _ERRI(1,"Exception:\n[%s]",e.what()) }
  #else
    info_(1,"* OpenCV is disabled for this build.")
  #endif
  return 0;
}
