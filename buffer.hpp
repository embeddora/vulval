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
// Abstract:            a type definition of '_pattern' structure and 'Buffer' class
//
// Usage:               none
//
// Version:             0.0.8

#ifndef BUFFER_HPP
#define BUFFER_HPP

// A definition of 'Datent' class
#include "datent.hpp"

/// Everything under this value will seem to be a binary data 
#define  BINARY_THRESHOLD	3.3

/// Everything above this value will look like a text
#define  TEXT_THRESHOLD  	3.5

/// To avoid enthropy value -0.0 to be regarded as an enthropy of binary data
#define  MALFORMED_THRESHOLD	0.001

/// To avoid processing tiny files (for on short input data, say under 16 bytes, Shennon's threshold-based data classification is weak)
#define  SHORT_FILE_LEN		0x10

/// Unknown data kind
#define UNKN 0

/// Purely binary data
#define DATA 1

/// Purely text data
#define TEXT 2

/// Unprocessable data - either short, either Shennon' entropy is incorrect
#define KURZ 3

/// A type definition of class to implement a buffer-processing logics
class Buffer : public Datent
{
public:
	Buffer(double binary_, double text_, double malformed_, int iShortfile);///< A default constructor, here we initilize threshold values, constants, etc

	~Buffer();///< A desctructor, no functionality by the moment

	double entropy(std::string& st);///< A method to compute Shennonenthropy (Shennon's mod) for this buffer

	int classify(double, int);///< A method to decide which kind of data is going to be processed

protected:

	double binary_tr, text_tr;///< Thresholds to determine binary (grows down) and text (grows upwards) entropy values

	double malformed_tr;///< A special threshold to get rid of misleading entropy values

	int shortfile;///< A length of sortest allowed file

}; // class Buffer

#endif // #define BUFFER_HPP
