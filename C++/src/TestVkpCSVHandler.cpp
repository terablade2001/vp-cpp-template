#include "include/TestVkpCSVHandler.hpp"

CECS_MODULE("TestVkpCSVHandler")

using namespace std;
using namespace vkp;


int TestVkpCSVHandler(int argc, char** argv) {
  {
    vkpCSVHandler csv;
    _ERRI(0!=csv.Initialize(" ","\""), "Initialize error.")
    _ERRI(0!=csv.addNewHeader("Header 1",0),"Failed to add header")
    _ERRI(0!=csv.addNewHeader("Header 2",1),"Failed to add header")
    _ERRI(0!=csv.addNewHeader("Header 3",2),"Failed to add header")

    std::vector<long long> L{0,10,20,30};
    std::vector<double> D{0.01,0.2,3.0,40.1};
    std::vector<string> S{"one","two","three","for all!"};
    _ERRI(0!=csv.setIntColumn((size_t)0,L),"Failed to set column 0")
    _ERRI(0!=csv.setDoubleColumn((size_t)1,D),"Failed to set column 1")
    _ERRI(0!=csv.setStringColumn((size_t)2,S),"Failed to set column 2")

    _ERRI(0!=csv.saveFile("test.csv"),"Failed to store csv file")
  }

  {
    vkpCSVHandler csv;

    // Setting field limiter (Space) and Strings limiter (Quota)
    _ERRI(0!=csv.Initialize(" ","\""), "Initialize error.")

    // Setting the type of columns: 0-INT, 1-DOUBLE, 2-STRING, for 4 columns in csv.
    // If this step ignored, all types are set to STRING by default.
    vector<unsigned char> headerTypes{0, 1, 2};
    _ERRI(0!=csv.setHeaders(headerTypes),"Failed to set datatypes of headers")

    // Loading CSV file, knowing 1rst line is headers [false = don't ignore headers]
    _ERRI(0!=csv.loadFile("test.csv", false),"Failed to load [test.csv] file.")

    std::cout << csv.infoStr() << std::endl << std::endl;

    string headerName;
    for (size_t column = 0; column < csv.columns(); column++) {
      _ERRI(0!=csv.getHeaderNameByColumn(column, headerName),"Failed to get header name")
      dbg_(63,"Header ("<<column<<"): ["<<headerName<<"]")
      for (size_t r = 0; r < csv.rows(); r++) {
        unsigned char dataType;
        void* res = csv.getValPtr(headerName.c_str(), r, dataType); _CHECKRI_
        switch (dataType) {
          case (0): { dbg_(63," > INT   : "<<*(long long*)res) break;}
          case (1): { dbg_(63," > DOUBLE: "<<*(double*)res) break;}
          case (2): { dbg_(63," > STRING: "<<*(string*)res) break;}
          default: { _ERRI(1,"Unexpected case") }
        }
      }
    }

    vector<long long> VH0;
    _ERRI(0!=csv.getIntColumn((size_t)0,VH0),"Failed to get vector column")
    for (auto& i : VH0) { dbg_(63," : > "<< i)}
  }
  return 0;
}
