#include "../include/DummyClass.hpp"

CECS_MODULE("DummyClass")

DummyClass::DummyClass() {
  dbg_(63,"libExampleCAPI.dll:: DummyClass - constructor")
  _ERR(1,"Generated constructor error, in DummyClass!")
}
