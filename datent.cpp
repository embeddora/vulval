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
// Abstract:            an implementation of 'Datent' class
//
// Usage:               none
//
// Version:             0.0.8

// Definition of 'Datent' type, which is a C++ class
#include "datent.hpp"

// Extent global namespace of given module for std::cout, at least 
using namespace std;


///	\brief		A default constructor of 'Datent' class
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-13
///	\warning	Is not a subject for further optimization
///
///	@param[in]	none
///
///	@return		none
///
///	A default constructor of 'data entry' entity; not used since all effective works is done in constructors of successors
Datent::Datent()
{
	//N/a

} // Datent::Datent()

///	\brief		A destructor of 'Datent' class
///	\author		kmauch@
///	\version	0.1
///	\date		2018-03-13
///	\warning	Is not a subject for further optimization
///
///	@param[in]	none
///
///	@return		none
///
///	A desctuctor; not used by the moment
Datent::~Datent()
{
	//N/a

} // Datent::~Datent()
