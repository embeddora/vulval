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
// Abstract:            a definition of class 'Shellcode'
//
// Usage:               none
//
// Version:             0.0.8

#ifndef SHELLCODE_HPP
#define SHELLCODE_HPP

// A definition of 'Hazent' C++ class and '_hazentry' ANSI C structure
#include "hazent.hpp"

/// A type definition of class to implement a logics behind typical (and known) shellcode
class Shellcode : public Hazent
{
public:
	Shellcode();///< Constructor, here empty list (vector, in fact) patterns gets initialized

	~Shellcode();///< Desctructor, no functionality by the moment

	bool isIthContained(char pcMemblock[], int iSize, int iIdx);///< A method overloads parent's base method

protected:

	bool isIthShellcodeContained(char pcMemblock[], int iSize, int iIdx);///< A method to find pattern inside memory array

	std::vector<_hazentry> ha_shellcode;///<A vector of hazardous entries (shellcodes)

	void setVectorData();///< Charge a vector and initialize its components with SC_xxx bytes

#if defined(CUSTOM_SEARCH)

	bool isContained(char ar1[], int size1, char ar2[], int size2);///< Aux. method to find pattern inside memory array. (Experimental.)

#endif // defined(CUSTOM_SEARCH)


}; // class Shellcode


#endif // #define SHELLCODE_HPP
