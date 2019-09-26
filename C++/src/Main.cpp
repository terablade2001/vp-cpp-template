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

#include "../../BuildVersion/BuildVersion.hpp"
#include <vkpBuildVersioner.hpp>
#include <CCEXP.hpp>
#include <CECS.hpp>
#include <vkpConfigReader.hpp>
#include <vkpProgressBar.hpp>
#include <PThreadPool.hpp>
#include <iostream>

using namespace std;

static vkpBuildVersioner BV1(1, VERSION_NUMBER);

int main(int argc, char** argv) {
	cout << "--- Program version: " << BV1.version << endl;
	try {
	
	} catch(std::exception &e) {
		 std::cout<< std::endl<<"(*) Exception occured: "<< std::endl << "  --> " << e.what() << std::endl;
	}
	return 0;
}