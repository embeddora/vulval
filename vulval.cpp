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
// Abstract:            a routine to check if a dedicated file (passed as second
//                      command line parameter, i.e. 'argv[1]') contains any of
//                      shell pattern known to this routine
//
// Usage:               ./find_shellcode ./FW_BINARY_NAME
//
// Version:             0.0.8

// Definition of 'cout', 'cin' 
#include <iostream>

// Definition of 'std::ifstream'
#include <fstream>

// Definition of 'Shellcode' type, which is a class
#include "shellcode.hpp"

// Definition of 'Exploit' type, which is a class
#include "exploit.hpp"

// Definition of 'Buffer' type, which is a class
#include "buffer.hpp"

// Definition of 'File' type, which is a class
#include "file.hpp"

// Extent global namespace of given module 
using namespace std;

///	\brief		A main function () 
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-05
///	\warning	No optimizable
///
///	@param[in]	argc	An amount of parameters on command line
///	@param[out]     argv	An array with command line parameters' values
///
///	@return		Return execution status (0 - success, !0 - some error)
///
///	A program entry point
int main (int argc, char** argv)
{
// Consttruct  'Shellcode' class instance
Shellcode Scode;

// Consttruct 'Exploit' class instance
Exploit Exploitable;

// Consttruct 'File' class instance with default constructor
File Openable;

	// Check command line parameters. Filenames as 'argv[1]' is a must 
	if  ( 2 > argc )
	{
		// Let user (if any) knwo what's was wrong 
		cout <<  "Insufficient argument set. Exiting..." << endl;

		// Exit with an error
		return -1;

	} // Command line parameter check
	else
		// Classify directory entry: only filesa are allowed; Ddirectory names - mot
		if ( ! Openable.isFilePresent( argv[1] ) )
		{
			// Let user (if any) knwo what's was wrong 
			cout <<  "The '" << argv[1] << "' does not seem to an openable file. Exiting..." << endl;

			// Exit with an error
			return -2;

		} // Directory entry classification
	else
	{

	// Re-construct 'File' class instance, this time with real name
	Openable = File(argv[1]);

	// Try to open a desired file as a binary one
	ifstream file (Openable.filename, ios::in|ios::binary|ios::ate);

	// Try to open file gives as command line parameter 'argv[1]'
	if (file.is_open())
	{
	// Buffer class inctance for currently procced file
	Buffer Buf(BINARY_THRESHOLD, TEXT_THRESHOLD, MALFORMED_THRESHOLD, SHORT_FILE_LEN);

		// Get file size into 'size' 
		Openable.size = file.tellg();

		// Allocate area long enough to include current file contents
		Openable.memblock = new char [Openable.size];

		// Shift file position to a begin of file
		file.seekg (0, ios::beg);

		// Take current file contents into just allocated area
		file.read (Openable.memblock, Openable.size);

		// Close current file
		file.close();

		// Construct a string long enough to incorporate current file's contents and place the contents in there
		std::string s(Openable.memblock);

		// Compute calculate an entropy of current file's contents
		Openable.entr = Buf.entropy( s );

		// Self-explanatory
		cout << "File '" << Openable.filename << "' enthropy is: " << Openable.entr << endl << "File '" << Openable.filename << "' length is: " << Openable.size << endl;		

		// Provide different handling for different file types
		switch( Buf.classify(Openable.entr, Openable.size) )
		{
			// Binary file
			case DATA:

				// Self-explanatory
				cout << "File '" << Openable.filename << "' recognized to be a binary file" << endl;

				// Try to find any shellcode in this file
				Scode.processAsClassified(Openable);

				// Terminate binary file block
				break;

			// Text file
			case TEXT:

				// Self-explanatory
				cout << "File '" << Openable.filename << "' recognized to be a text file" << endl;

				// Try to find any exploit in this file
				Exploitable.processAsClassified(Openable);

				// Terminate binary file block
				break;

			// Short or unprocessable file
			case KURZ:

				// Self-explanatory
				cout << "File '" << Openable.filename << "' recognized to be ether inacceptably short or unprocessable for some other reason. Skipping." << endl;

				// Terminate short/unprocessed file block
				break;

			// Unknown file type
			default:
			case UNKN:

				// Self-explanatory
				cout << "File '" << Openable.filename << "' recognized to be a file which resembles binary and text file at the same time. Special handling required." << endl;

				// Terminate unknown file block
				break;
		}

		// Free memory occupied by 'new char [size]'
		delete[] Openable.memblock;
	}
	else
	{
		// Inform user what's wrong
		cout << "Unable to open file '" << Openable.filename << "'" << endl;

		// Exit with an error 
		return -1;

	} // if (file.is_open())

	}

	// Exit with success
	return 0;

} // int main (. . .)
