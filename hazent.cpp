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
// Abstract:            an implementation of 'Hazent' class
//
// Usage:               none
//
// Version:             0.0.8

// Definition of 'cout', 'cin' 
#include <iostream>

// Definition of 'std::ifstream'
#include <fstream>

// Definition of 'std::search'
#include <algorithm>

// Definition of 'Shellcode' type, which is class
#include "shellcode.hpp"

// Definition of 'Hazent' type, which is a C++ class, and of type '_hazentry', which is a ANSI C structure
#include "hazent.hpp"

// Definition of 'File' type, which is a class
#include "file.hpp"

// Extent global namespace of given module 
using namespace std;


///	\brief		A constructor of 'Hazent' class
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	Is not a subject for further optimization
///
///	@param[in]	clarification of haz. entry type (to faciliatate output to STDOUT)
///
///	@return		none
///
///	An auxiliary function, could be removed upon optimization
Hazent::Hazent(const std::string& fullname): credentials (fullname)
{
	// Put known hazardous entries into 'ha_hazent'
	setVectorData();

	// A flag to memorize if an explot was detected within a current file
	bHazardDetected = false;

} // Hazent::Hazent()

///	\brief		A destructor of 'Hazent' class
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	Is not a subject for further optimization
///
///	@param[in]	none
///
///	@return		none
///
///	An auxiliary function, could be removed upon optimization
Hazent::~Hazent()
{
	// Dispose memory allocated by patterns, etc

} // Hazent::~Hazent()


///	\brief		Check if 'ar2' (of length 'size2') is present in 'ar1' (of size1). Returns true if present, and false by default 
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	Is not a subject for further optimization
///
///	@param[in]	ar1	First array to check
///	@param[in]	size1	Length of first array
///	@param[in]	ar2	Second array to check
///	@param[in]	size2	Length of second array
///
///	@return		Returns result of comparison
///
///	An auxiliary function, could be removed after debug is done
bool Hazent::isContained(char ar1[], int size1, char ar2[], int size2)
{
	// Check if range found is exactly the second range 
	return std::search(ar1, ar1 + size1, ar2, ar2 + size2) != (ar1 + size1);

} // bool isContained ( . . .)


///	\brief		Check if pattern with index 'iIdx' is present in 'pcMemblock' of 'iSize'. Returns true if present, and false by default 
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	A subject for further optimization
///
///	@param[in]	pcMemblock	First array to check
///	@param[in]	iSize		Length of first array
///	@param[in]	iIdx		index of pattern to find
///
///
///	@return		Returns result of comparison
///
///	A basic function, should not be removed
bool Hazent::isIthContained(char pcMemblock[], int iSize, int iIdx)
{
	// Overloaded by successors under current model. Kept here for future impl's

} // bool Hazent::isIthContained(char pcMemblock[], int iSize, int iIdx)


///	\brief		Take first element of vector of patterns 
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	Is not a subject for further optimization
///
///	@return		First element of vector of patterns 
///
///	A basic function, should not be removed
std::vector<_hazentry>::const_iterator Hazent::getFirst()
{
	return ha_hazent.begin();

} // bool Shellcode::getFirst()


///	\brief		Take last element of vector of patterns 
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	A subject for further optimization
///
///	@return		Last element of vector of patterns 
///
///	A basic function, should not be removed
std::vector<_hazentry>::const_iterator Hazent::getLast()
{
	return ha_hazent.end();

} // bool Shellcode::getLast()

///	\brief		A function to return haz. entry kind as a string 
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	No optimizable
///
///	@param[in]	none
///
///	@return		none
///
///	A function to return haz. entry kind as a string to facilitate an output to STDOUT
std::string Hazent::getCredentials()
{
	return credentials;

}// std::string Hazent::getCredentials()


///	\brief		A function to enroll patterns into empty vector variable
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	No optimizable
///
///	@param[in]	none
///
///	@return		none
///
///	A basic function, should not be removed
void Hazent::setVectorData()
{
	// Overloaded by successors under current model. Kept here for future implementations

} // void chargePatterns(std::vector<_pattern> vec_pattern)

///	\brief		Method to attempt to find a haz. entry (exploit or shellcode) in current file
///	\author		kmauch@
///	\version	0.2
///	\date		2018-03-13
///	\warning	Optimizable (but better to leave it as is for a while)
///
///	@param[in]	CurrentFile     Is an ... 
///	@param[in]	Filename	Is a name of file to be displayed on STDOUT
///
///	@return		none
///
///	A method to attempt to find a haz. entry (exploit or shellcode) in current file
void Hazent::processAsClassified(File & CurrentFile)
{	
// Iterator through patterns
std::vector<_hazentry>::const_iterator ii;

// Cycle counter 
int i = 0;

	// Go through all shellcode instances
	for(i=0, ii=getFirst(); ii!=getLast(); ++ii, i++)
	{
		// Try to find pattern in file 
		if ( isIthContained( CurrentFile.memblock, CurrentFile.size, i )    )
		{
			// Memorize that at lest one shellpattern was detected
			if ( ! bHazardDetected ) bHazardDetected = true;

			// Show result of pattern search on standard output
			cout <<  "An exploit " << std::to_string(i) << " was found in file '" << CurrentFile.filename << "'" << endl;
		}
#if defined(EXCESSIVE_OUTPUT)
		else
			cout <<  "An exploit " << std::to_string(i) << " was not found in file " << CurrentFile.filename << endl;
#endif // defined(EXCESSIVE_OUTPUT)
	}

	// Pattern search failed?
	if ( ! bHazardDetected )

		// Declare the search was failed on standard output 
		cout <<  "None of known "<<  getCredentials() <<" was found in file " << CurrentFile.filename << endl;

} // void File::processAsText(Exploit & Exploitable, std::string const & Filename)
