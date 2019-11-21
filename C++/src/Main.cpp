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

#include <Main.hpp>
#include "../../BuildVersion/BuildVersion.hpp"
#include <vkpBuildVersioner.hpp>

// Versioning and CECS
static vkpBuildVersioner BV1(1, VERSION_NUMBER);
CECS_MAIN_MODULE("Main","CECS::Project")

int main(int argc, char** argv) {
	// Set ECS display sections, and clear default obj's errors (optional)
	_ECSFORMAT(1,0,0,1,1,1,1,1) __ECSOBJ__.clear();
	// Enable all 32 Signals in case of CECSDEBUG flag.
	for (int i=0; i < 32; i++) _SETSIGNAL(i)

	// Show program version.
	cout << endl << "------ Program Version: " << BV1.version << " -----------" << endl;

	try {
		
		// Run Example() function of the demo!
		_ERRT(Example(argc, argv),"Failed to run \"Example()\" function!")


	cout << "---------------- Program completed ---------------------" << endl;
	} catch(std::exception &e) {
		string eColorStart; string eColorFix;

		// Enable the following line for colored error output
		// eColorStart = string("\033[1;36m"); eColorFix = string("\033[m");
		std::cerr<< std::endl<<"(*) Exception occured: "<< std::endl << eColorStart <<e.what()<< eColorFix << std::endl;
	}
	return 0;
}