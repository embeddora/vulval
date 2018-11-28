/*
 Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
        * Neither the name of The Linux Foundation nor
          the names of its contributors may be used to endorse or promote
          products derived from this software without specific prior written
          permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 Abstract:            a routine to dissassemble (temporarily hardcoded) ARM-binary

 Usage:               see code

 Version:             0.0.1

*/

/* PRIx64 format of haxadecimal */
#include <inttypes.h>

/* Interface to Cpstone library */
#include <capstone/capstone.h>
 
int main(void)
{
/* Data struct handler. Capstone's  */
csh handle;

/* Pointer to disassembler instruction. Capstone's */
cs_insn *insn;

/* The number of disassembled instructions */
size_t iCount;

/* Target file pointer TODO: remove hardwacoded */
FILE * fName;

/* Container for raw file */
char * pcData = NULL;

	/* Open locally stored file, ELF 32-bit LSB executable, ARM, version 1 */
	fName = fopen ("./pppd", "r");

	if (NULL != fName)
	{
		/* Shift file position to an end of file */
		fseek(fName, 0, SEEK_END); 

		/* Get current file position */
		int iSize = ftell(fName); 

		/* Shift back to beginning of file */
		fseek(fName, 0, SEEK_SET);

		/* File size computed ? */
		if (0 != iSize)
		{
		/* Prepare container for raw file */
		char * pcData = (char*) malloc (iSize) ;

			/* If place allocated */
			if (NULL != pcData) 
			{
				/* Could not initialize Capstone library? */
				if (cs_open(CS_ARCH_ARM, CS_MODE_ARM, &handle) != CS_ERR_OK)
				{
					/* Self-explanatory */
					printf("ERROR: Capstone library error \n");

					/* then exit an error */
					return 	-1;
				}

				/* Dassimble code at current position and take a number of disassembler instr's into 'iCount' */
				iCount = cs_disasm(handle, pcData, iSize, 0, iSize, &insn);

				/* Have we had a success on disassembling ? */
				if (0 < iCount)
				{
				size_t j;

					/* All disassembled to be printed out top STDOUD */
					for (j = 0; j < iCount; j++)

						/* Produce STDOUT output */
						printf("0x%"PRIx64":\t%s\t\t%s\n", insn[j].address, insn[j].mnemonic, insn[j].op_str);


					/* Release memory which was allocated by cs_disasm() */
					cs_free(insn, iCount);
				}
				else
					 /* Self-explanatory. Don't terminate - we have a chance with next code fragment */
					printf("ERROR: Failed to disassemble given code!\n");

				/* Release space occupied by current intr. set */
				cs_close(&handle);
			}
			else
			{
				/* Self-explanatory */
				printf("ERROR: NULL\n");

				/* Exit an error */
				return 	-1;

			} /* if (NULL != pcData)  */

		}
		else
		{
			/* Self-explanatory */
			printf("ERROR: bad size\n");

			/* Exit an error */
			return 	-1;

		} /* if (0 != iSize) */

		/* Opened file is not needed anymore */
		fclose(fName);
	}

	/* Success */
	return 0;

} /* int main(void)*/
