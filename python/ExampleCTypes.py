#! /user/bin/env python
# MIT License

# Copyright (c) 2016 - 2022 Vasileios Kon. Pothos (terablade2001)
# https://github.com/terablade2001

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
import sys
from ctypes import *
from struct import *
import numpy as np
FF = (os.path.dirname(os.path.realpath(__file__))).replace("\\","/")+"/"
sys.path.append(FF)

class ExampleCTypes_InitData(Structure):
  _fields_ = [
    ("string_", c_char_p),
    ("integer_", c_int),
    ("float_", c_float),
    ("boolean_", c_bool),
    ("vectorFloat_", c_char_p),
    ("vectorFloatSize_", c_int),
  ]

class ExampleCTypes_Wrapper:
  def checkError(self, errVal, errString):
    if (errVal != 0):
      cv = c_char_p()
      res2 = self.ExampleCTypes.ExampleCTypes_error(byref(cv))
      if (res2 != 0):
          raise "Failed to get ExampleCTypes error message."
      print(cv.value.decode('utf-8'))
      raise errString

  def __init__(self):
    ### Initialize Struct's data
    self.InitData = ExampleCTypes_InitData()
    self.InitData.string_ = c_char_p("This is the input string!".encode('utf-8'))
    self.InitData.integer_ = c_int(10)
    self.InitData.float_ = c_float(10)
    self.InitData.boolean_ = c_bool(True)
    vectorFloat = list(map(float,[10.1, 11.2]))
    vectorFloatArray = bytearray()
    for v in vectorFloat:
      vectorFloatArray.extend(pack("f",v))
    self.InitData.vectorFloat_ = c_char_p(bytes(vectorFloatArray))
    self.InitData.vectorFloatSize_ = c_int(2)

    ### Load the DLL/SO
    self.ExampleCTypes = CDLL("./libExampleCTypes.so") # UNIX / Linux
    self.ExampleCTypes.ExampleCTypes_StructInOut.argtypes=[c_void_p]
    self.ExampleCTypes.ExampleCTypes_ScalarsIn.argtypes=[c_int, c_float, c_char]
    self.ExampleCTypes.ExampleCTypes_VectorsInOut.argtypes=[c_char_p, c_char_p, c_char_p]
    self.ExampleCTypes.ExampleCTypes_VectorsOut.argtypes=[c_void_p, c_void_p, c_void_p]
    self.ExampleCTypes.ExampleCTypes_version.argtypes=[c_void_p]
    self.ExampleCTypes.ExampleCTypes_error.argtypes=[c_void_p]

    ### Display DLL/SO Version ###
    cv = c_char_p()
    res = self.ExampleCTypes.ExampleCTypes_version(byref(cv))
    self.checkError(res,"Failed to get version.")
    print('libExampleCTypes.dll/so, Version: %s' % (cv.value.decode('utf-8')))

    ### ExampleCTypes_StructInOut ###
    res = self.ExampleCTypes.ExampleCTypes_StructInOut(byref(self.InitData))
    self.checkError(res,"Failed to run ExampleCTypes_StructInOut.")
    print(self.InitData.integer_)
    print(self.InitData.float_)
    # print(unpack("ff",self.InitData.vectorFloat_.value))

    ### ExampleCTypes_ScalarsIn ###
    res = self.ExampleCTypes.ExampleCTypes_ScalarsIn(c_int(10), c_float(10.1), c_char(40))
    self.checkError(res,"Failed to run ExampleCTypes_ScalarsIn.")

    ### ExampleCTypes_VectorsInOut ###
    vectorInt = list(map(int,[10, 11]))
    vectorIntArray = bytearray()
    for v in vectorInt:
      vectorIntArray.extend(pack("i",v))
    intInput = create_string_buffer(bytes(vectorIntArray),8)
    vectorFloat = list(map(float,[5.5, 6.6]))
    vectorFloatArray = bytearray()
    for v in vectorFloat:
      vectorFloatArray.extend(pack("f",v))
    floatInput = create_string_buffer(bytes(vectorFloatArray),8)
    charInput = create_string_buffer(b"yz",2)
    res = self.ExampleCTypes.ExampleCTypes_VectorsInOut(intInput, floatInput, charInput)
    self.checkError(res,"Failed to run ExampleCTypes_VectorsInOut.")
    print(unpack("ii",intInput.value))
    print(unpack("ff",floatInput.raw))
    print(charInput.value)

    ### ExampleCTypes_VectorsOut ###
    intOutput = POINTER(c_int)()
    floatOutput = POINTER(c_float)()
    charOutput = POINTER(c_char)()
    res = self.ExampleCTypes.ExampleCTypes_VectorsOut(byref(intOutput), byref(floatOutput), byref(charOutput))
    self.checkError(res,"Failed to run ExampleCTypes_VectorsOut.")
    print(intOutput[0],intOutput[1])
    print(floatOutput[0],floatOutput[1])
    print(charOutput[0],charOutput[1])




ExampleCTypes = ExampleCTypes_Wrapper()
