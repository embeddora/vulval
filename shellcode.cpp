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
// Abstract:            an implementation of 'Shellcode' class
//
// Usage:               none
//
// Version:             0.0.8


// Definition of 'std::ifstream'
#include <fstream>

// Definition of 'std::search'
#include <algorithm>


// Definition of '_hazentry' type (which is a structure), and of 'Hazent' class
#include "hazent.hpp"

// Definition of 'Shellcode' type, which is a class
#include "shellcode.hpp"

// Include ARM's possible shellcodes 
#include "shellcode.arm"

// Include MIPS' possible shellcodes 
#include "shellcode.mips"


///	\brief		A constructor of 'Shellcode' class
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-05
///	\warning	Is not a subject for further optimization
///
///	@param[in]	none
///
///	@return		none
///
///	An auxiliary function, could be removed upon optimization
Shellcode::Shellcode() : Hazent("shellcodes")
{
	// Put known MIPS and ARM patterns into 'ha_shellcode'
	setVectorData();

} // Shellcode::Shellcode()

///	\brief		A destructor of 'Shellcode' class
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-05
///	\warning	Is not a subject for further optimization
///
///	@param[in]	none
///
///	@return		none
///
///	An auxiliary function, could be removed upon optimization
Shellcode::~Shellcode()
{
	// Dispose memory allocated by patterns, etc. Kept here for future implementations

} // Shellcode::~Shellcode()

#if defined(CUSTOM_SEARCH)

///	\brief		Check if 'ar2' (of length 'size2') is present in 'ar1' (of size1). Returns true if present, and false by default 
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-05
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
bool Shellcode::isContained(char ar1[], int size1, char ar2[], int size2)
{
	// Check if range found is exactly the second range 
	return std::search(ar1, ar1 + size1, ar2, ar2 + size2) != (ar1 + size1);

} // bool isContained ( . . .)

#endif /* defined(CUSTOM_SEARCH) */


///	\brief		Check if pattern with index 'iIdx' is present in 'pcMemblock' of 'iSize'. Returns true if present, and false by default 
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-05
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
bool Shellcode::isIthShellcodeContained(char pcMemblock[], int iSize, int iIdx)
{
#if defined(CUSTOM_SEARCH)
	// Check if 'ar2' (of length 'size2') is present in 'ar1' (of size1).
	if ( isContained( pcMemblock, iSize, (char*)ha_shellcode  [iIdx].vpPattern,  ha_shellcode  [iIdx].iLength )  )  

		// Return true if present
		return true;

	// If 'is not present' return false
	return false;
#else
	// Check if range found is exactly the second range 
	return	std::search(	pcMemblock,				
				pcMemblock + iSize,
				(char*)ha_shellcode  [iIdx].vpPattern,
				(char*)ha_shellcode  [iIdx].vpPattern + ha_shellcode  [iIdx].iLength)
				!=
			(pcMemblock + iSize);
#endif // defined(CUSTOM_SEARCH)

} // bool Shellcode::isIthShellcodeContained(char pcMemblock[], int iSize, int iIdx)


///	\brief		Check if a shellcode with index 'iIdx' is present in 'pcMemblock' of 'iSize'. Returns true if present, and false by default 
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
bool Shellcode::isIthContained(char pcMemblock[], int iSize, int iIdx)
{
	// Check if range found is exactly the second range 
	return	isIthShellcodeContained(pcMemblock, iSize, iIdx);

} // bool Hazent::isIthContained(char pcMemblock[], int iSize, int iIdx)


///	\brief		A function to enroll patterns into empty vector variable
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-07
///	\warning	No optimizable
///
///	@param[in]	none
///
///	@return		none
///
///	A basic function, should not be removed
void Shellcode::setVectorData()
{
	//Push back new object created with default constructor.
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[0].vpPattern = SC_904;
	ha_shellcode[0].iLength = 4*8+3;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[1].vpPattern = SC_901;
	ha_shellcode[1].iLength = 4*9+3+2*10;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[2].vpPattern = SC_853;
	ha_shellcode[2].iLength = 4*4+1+2*11;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[3].vpPattern = SC_854;
	ha_shellcode[3].iLength = 4*4+1+2*10;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[4].vpPattern = SC_668;
	ha_shellcode[4].iLength = 8+8*2+11;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[5].vpPattern = SC_670;
	ha_shellcode[5].iLength = 4*14+8*2+11;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[6].vpPattern = SC_671;
	ha_shellcode[6].iLength = 4*19+2;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[7].vpPattern = SC_665;
	ha_shellcode[7].iLength = 7+2;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[8].vpPattern = SC_698;
	ha_shellcode[8].iLength = 4*6+3;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[9].vpPattern = SC_696;
	ha_shellcode[9].iLength = 4*7+3;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[10].vpPattern = SC_666;
	ha_shellcode[10].iLength = 4*9+2;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[11].vpPattern = SC_820;
	ha_shellcode[11].iLength = 4*4+2*14;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[12].vpPattern = SC_819;
	ha_shellcode[12].iLength = 4*3+2*10;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[13].vpPattern = SC_860;
	ha_shellcode[13].iLength = 16*12+8;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[14].vpPattern = SC_79;
	ha_shellcode[14].iLength = 8*6;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[15].vpPattern = SC_782;
	ha_shellcode[15].iLength = 4*11+7;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[16].vpPattern = SC_793;
	ha_shellcode[16].iLength = 4*41;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[17].vpPattern = SC_794;
	ha_shellcode[17].iLength = 4*40;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[18].vpPattern = SC_792;
	ha_shellcode[18].iLength = 4*12;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[19].vpPattern = SC_795;
	ha_shellcode[19].iLength = 4*8;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[20].vpPattern = SC_80;
	ha_shellcode[20].iLength = 4*13+7;

	//Add a new element
	ha_shellcode.push_back ( _hazentry () );
	ha_shellcode[21].vpPattern = SC_81;
	ha_shellcode[21].iLength = 4*37+7;

} // void chargePatterns(std::vector<_pattern> vec_pattern)
