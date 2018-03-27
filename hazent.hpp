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
// Abstract:            a definition of class 'Hazent'
//
// Usage:               none
//
// Version:             0.0.8

#ifndef HAZENT_HPP
#define HAZENT_HPP


// Type definition of 'std::vector'
#include <vector>

// Type definition of 'std::string'
#include <string>

// Definition of 'File' type, which is a class
#include "file.hpp"

// Extent global namespace of given module 
using namespace std;

/// A type definition of structure which describes single hazardous entry, be it shellcode or exploi
typedef struct _hazentry
{
	const void *	vpPattern;///< Shellcode in an 'endienness' of a target platform

	std::string	gExploit;///< Exploit as an ASCII-text, byteorder disregerded

	int		iLength;///< Effective length of data set, be it shellcode or exploi

	int		iID;///< Index of hazardous entry

	char		* cpShortName;///< Name of hazardous entry

} Hazentry, * pHazentry; // typedef struct _hazentry

/// A type definition of class to implement a logics behind various hazardous entries
class Hazent
{
public:
	Hazent(std::string fullname);///< Constructor, here empty vector of hazardous entries gets initialized

	~Hazent();///< Desctructor, no functionality by the moment

	bool isIthContained(char pcMemblock[], int iSize, int iIdx);///< A method to find hazardous data inside memory array

	std::vector<_hazentry>::const_iterator getFirst(), getLast();///< A method to get first/last element of patterns' vector

	bool bHazardDetected;///< A flag to memorize if a hazardous entry has been detected within a current data entry (e.g. file, buffer)

	std::string getCredentials();///< A method to return get stdout-frientdy definition of current hazardous entry

	void processAsClassified(File & CurrentFile);///<A method to attempt to find a haz. entry (exploit or shellcode) in current file

protected:
	std::string credentials;/// A stdout-friendly definition of current hazardous entry

	std::vector<_hazentry> ha_hazent;///< A vector to contain hazardous entries

	void setVectorData();///< A method to charge an empty vector with initialized data

	bool isContained(char ar1[], int size1, char ar2[], int size2);///< An aux. method to find hazardous entry inside memory array

}; // class Hazent

#endif // #define HAZENT_HPP
