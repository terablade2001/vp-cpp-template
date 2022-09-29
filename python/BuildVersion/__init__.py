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
import sys
import struct
import math
import os

# def _BUILDVersionF():
  # _BUILDVersion = -1
  # _BUILDFormatStr = ""

# _BUILDVersionF()

def BuildVersionFormat(format, BV):
  BUILDFormatStr = []
  if (format == 0):
    BUILDFormatStr = "[%3.3i]"%(BV)
  elif (format == 3):
    tr4 = math.floor(BV / (1000000000));
    tr3 = math.floor((BV-tr4*1000000000) / (1000000));
    tr2 = math.floor((BV-tr4*1000000000-tr3*1000000) / (1000));
    tr1 = math.floor(BV-tr4*1000000000-tr3*1000000-tr2*1000);
    BUILDFormatStr = "[%i.%3.3i.%3.3i.%3.3i]"%(tr4,tr3,tr2,tr1)
  elif (format == 2):
    tr3 = math.floor((BV) / (1000000));
    tr2 = math.floor((BV-tr3*1000000) / (1000));
    tr1 = math.floor((BV-tr3*1000000-tr2*1000));
    BUILDFormatStr = "[%i.%3.3i.%3.3i]"%(tr3,tr2,tr1)
  else:
    tr2 = math.floor((BV) / (1000));
    tr1 = math.floor((BV-tr2*1000));
    BUILDFormatStr = "[%i.%3.3i]"%(tr2,tr1)
  return BUILDFormatStr
    

# Use this to update versions in Debug mode
def BuildVersion(file):
  _BUILDDebug = True
  FF = (os.path.dirname(os.path.realpath(__file__))).replace("\\","/")+"/"
  
  ProjectStateFile = FF + "project.state"
  if not os.path.exists(ProjectStateFile):
    with open(ProjectStateFile,"w") as wfp:
      print("1",file=wfp,end='')
  Lines = [line.rstrip('\n') for line in open(ProjectStateFile)]
  for l in Lines:
    if int(l) == 1: 
      _BUILDDebug = True
    else:
      _BUILDDebug = False
    break
  dbg = _BUILDDebug

  # In Release Mode do nothing more
  if dbg == False:
    return
  
  # In Debug Mode update with new version
  Lines = [line.rstrip('\n') for line in open(file)]
  version_number=[]
  for l in Lines:
    ps = l.find(" (")
    pe = l.find(".0)")
    BV = int(l[ps+2:pe])
    break
  
  BV = BV + 1
  with open(file,"w") as wfp:
    print("#define VERSION_NUMBER (%i.0)"%(BV),file=wfp)
  with open(FF+"current.version","w") as wfp:
    print("(%i.0)"%(BV),file=wfp)


# Use this to read current version.
def version(format):
  FF = (os.path.dirname(os.path.realpath(__file__))).replace("\\","/")+"/"
  file = FF+"current.version"
  if not os.path.exists(file):
    print("File is missing: [%s]. Use BuildVersion() first! ... Aborting."%(file))
    sys.exit(0)
  Lines = [line.rstrip('\n') for line in open(file)]
  version_number=[]
  for l in Lines:
    ps = l.find(" (")
    pe = l.find(".0)")
    BV = int(l[ps+2:pe])
    break
  
  return BuildVersionFormat(format, BV)