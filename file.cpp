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


// Definition of 'std::ifstream'
#include <fstream>

// Definition of 'boost::filesystem::is_directory'
#include <boost/filesystem.hpp>

// Own interface
#include "file.hpp"


///	\brief		A 'by-default' constructor of a 'File' class
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	Is not a subject for further optimization
///
///	@param[in]	none
///
///	@return		none
///
///	A default contructor of 'File' class needed for we instatiate the class prior to knwowing if the filename (given via command line) is valid. Also sets default values to class members to avoid code quality warning CWE#398.
File::File()
{
	// Assign default value
	size = 0;

	// Assign default value
	memblock = NULL;

	// Assign default value
	entr = -0.0;

} // File::File()

///	\brief		A constructor of 'File' class with real name of a target file
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	Is not a subject for further optimization
///
///	@param[in]	real name fo a file to be processed
///
///	@return		none
///
///	A constructor of 'File' class with real name of a target file; needed for we reinitialize class instance when the target file name is recognized to be valid. Also sets default values to class members to avoid code quality warning CWE#398.
File::File(const std::string& Filename) : filename(Filename)
{
	// Assign default value
	size = 0;

	// Assign default value
	memblock = NULL;

	// Assign default value
	entr = -0.0;

} // File::File()

///	\brief		A destructor of 'File' class
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	Is not a subject for further optimization
///
///	@param[in]	none
///
///	@return		none
///
///	An . . .
File::~File()
{
	// N/a

} // File::~File()

///	\brief		Check if file named 'location' on its path 
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-15
///	\warning	Is not a subject for further optimization
///
///	@param[in]	location	An absolute/relative (the shell is to decide which one) path to a file to be checked
///
///	@return		Returns result of a check
///
///	An auxiliary function, could be removed after debug is done
bool File::isFilePresent(std::string location)
{
	// Check if 'location' exists without opening
	if (std::ifstream(location))
	{
		// Now, when the filesystem entry (file or dir) has proven to be valid, undertake specail action(s), once needed
		;

		// Filesystem entry name exists - check if the one ain't a direcotry name
		if ( ! boost::filesystem::is_directory(location) )
	
			// 'True' is filename exists, and is not a name of a directory
			return true;	

	}

	// False in all other cases
	return false;

} // bool isFilePresent(std::string location)
