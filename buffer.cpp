//
// Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//        * Redistributions of source code must retain the above copyright
//          notice, this list of conditions and the following disclaimer.
//        * Redistributions in binary form must reproduce the above copyright
//          notice, this list of conditions and the following disclaimer in the
//          documentation and/or other materials provided with the distribution.
//        * Neither the name of The Linux Foundation nor
//          the names of its contributors may be used to endorse or promote
//          products derived from this software without specific prior written
//          permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Abstract:            
//
// Usage:               none
//
// Version:             0.0.8


// Definition of 'vector', 'log'
#include <algorithm>

// Definition of 'std::set'
#include <set>

// Own interface, and treshold constants
#include "buffer.hpp"

// Extent global namespace of given module 
using namespace std;

///	\brief		A dafault constructor of 'Buffer' class
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-13
///	\warning	Is not a subject for further optimization
///
///	@param[in]	none
///
///	@return		none
///
///	A constrcutor, to initialize entropy thresholds and minimal allowed length of a buffer process
Buffer::Buffer(double binary_, double  text_, double malformed_, int iShortfile)
{
	binary_tr = binary_;

	text_tr = text_;

	malformed_tr = malformed_;

	shortfile = iShortfile;

} // Buffer::Buffer()

///	\brief		A destructor of 'Buffer' class
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-13
///	\warning	Is not a subject for further optimization
///
///	@param[in]	none
///
///	@return		none
///
///	A descructor, not used to the moment
Buffer::~Buffer()
{
	//

} // Buffer::~Buffer()



///	\brief		A routine to compute an entropy of char array to tell whether it's a binary data or text
///	\author		kmauch@
///	\version	0.2
///	\date		2018-03-13
///	\warning	Optimizable (but better to leave it as is for a while)
///
///	@param[in]	st	An input data (considered to be char array, later on being transformed into a vector)
///
///	@return		Returns float value of entropy. The lower value is the higher is a probability that input arrays is binary data, not a text
///
///	A routine of Shannon's information entropy computation. Needed to distinguish text
///	files/arrays from binary ones. An output later to be compared with set corr. threholds
double Buffer::entropy(string& st)
{
// Input string as vector of characters
vector<char> stvec(st.begin(), st.end());

// Produce an alfabet out of input data (string, sequence of chars)
set<char> alphabet(stvec.begin(), stvec.end());

// Frequency of each character in a vactor (original string)
vector<double> freqs;

	// Go though each char in alfabet of which (an input) string consists
	for (set<char>::iterator c = alphabet.begin(); c != alphabet.end(); ++c)
	{
	// Counter of chars being encountered
	int ctr = 0;

		// Go though each char of (an input) string
		for (vector<char>::iterator s = stvec.begin(); s != stvec.end(); ++s)

			// Same char ecountered?
			if (*s == *c)

				// Then increase a counter
				++ctr;

		// For the char (being procesed currenty) memorize its frequency in an (input) string
		freqs.push_back((double)ctr / (double)stvec.size());
	}

	// Default entropy - zero; incorrect entropy values (including zero) should be filered out while using this value
	double ent = 0;

	// Take base-e natural logarithm of 2; signature is 'double log(double)' is appropriate for across C++90, C++98, C++99, C++11. (For C++14, C++17 should be same, too.)
	double ln2 = log(2);

	// Process frewuency of each character
	for (vector<double>::iterator f = freqs.begin(); f != freqs.end(); ++f)

		// Add an intermediate entropy value to cumulative entropy
		ent += *f * log(*f)/ln2;

	// Beware: on this default '0.0' becomes '-0.0' (pay attention while filtering out inadmissible entropy values) 
	ent = -ent;

	// Now the entropy (being returned here) is ready for classifying
	return ent;

} // double entropy(string& st)

///	\brief		Method to decide which kind of data is going to be processed
///	\author		kmauch@
///	\version	0.2
///	\date		2018-03-13
///	\warning	Optimizable (but better to leave it as is for a while)
///
///	@param[in]	enthr	Information enthropy value
///	@param[in]	fsize	Dta length (to skip processing short data)
///
///	@return		Returns ID of data kind
///
///	A routine to decide which kind of data is going to be processed
int Buffer::classify(double enthr, int fsize)
{
	// Check if data length admits Shennon's entropy to be applied
	if (malformed_tr > enthr || SHORT_FILE_LEN > shortfile)

		// Do a special 'do' to short files and/or files which enthropy is unexpectedly low
		return KURZ;
	else		
		// Check if an entropy is that low that we don't have a text data at all
		if (binary_tr > enthr )

			// It's a definitely binary file, let's proceed it as such (find shellcodes)
			return DATA;	
		else
			// Check if an entropy is that high that we're about to deal with purely text data
			if (text_tr < enthr )

				// It's a definitely text file, let's proceed it as shell scripts, CGI stuff, or configuration files
				return TEXT;

			else
				// We can't tell if it's a text or binary - deploy special handling 
				return UNKN;

} // int Buffer::classify(double enthr, int fsize)
