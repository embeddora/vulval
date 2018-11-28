#!/bin/bash
#
# Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#        * Redistributions of source code must retain the above copyright
#          notice, this list of conditions and the following disclaimer.
#        * Redistributions in binary form must reproduce the above copyright
#          notice, this list of conditions and the following disclaimer in the
#          documentation and/or other materials provided with the distribution.
#        * Neither the name of The Linux Foundation nor
#          the names of its contributors may be used to endorse or promote
#          products derived from this software without specific prior written
#          permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Abstract:
#                a scipt to find latest file and latest file and latest directory 
#                in a subtree of a given directory. It ignores such entities as
#                links since files and dirs since it's pretty enough to process
#                the these files and dirs these links point onto
#		 
#
# Usage:         './find_latest.sh .', or './find_latest.sh /tmp/ZyXEL_P2812/rootfs',
#                or etc
#
# Version:       0.0.1
#   

# Red color ID
RED='\033[0;31m'

# No-color ID
NORMAL='\033[0m'

# Set default empty value
LATEST_FILE=""

# Set Epoch-begin value
TIME_STAMP=0

# Throughout all files within currect folder, recursively 
for fil in `find "$1" -type f`

do
	# Don't confuse with current script
	if [ $fil != $0 ]; then

		# Get the timestamt of current file
		TMP_TIME_STAMP=$(stat "$fil" --format=%Y)

		# Check if the file is newest ever
		if [ $TIME_STAMP -lt $TMP_TIME_STAMP ]; then

			# Assign nost recent file modification time
			LATEST_FILE="$fil"

			# Assign nost recent file modification time
			TIME_STAMP=$TMP_TIME_STAMP
		fi
	fi

done # files cycle 

# -e for '\n', otherwise is not needed 
echo -e "\nLatest modiffied file is: ${RED}$LATEST_FILE${NORMAL}\nin particular in was midified on:" `stat $LATEST_FILE --format=%y` "\n"

# Set default empty value
LATEST_DIR=""

# Set Epoch-begin value
TIME_STAMP=0

# Throughout all subdirectories within currect directory, recursively 
for dir in `find "$1" -type d`

do
	# Don't confuse with highst directory (which is none of interest))
	if [ $dir != $1 ]; then

		# Get the timestamt of current directory
		TMP_TIME_STAMP=$(stat "$dir" --format=%Y)

		# Check if the subdirectory is newest ever
		if [ $TIME_STAMP -lt $TMP_TIME_STAMP ]; then

			# Assign most recent dir. modification name 
			LATEST_DIR="$dir"

			# Assign nost recent dir. modification time
			TIME_STAMP=$TMP_TIME_STAMP

		fi
	fi

done # directories cycle 

# -e for '\n', otherwise is not needed 
echo -e "Latest modiffied dir is: ${RED}$LATEST_DIR${NORMAL}\nin particular it was modified on:" `stat $LATEST_DIR --format=%y`

# Exit-with-success point 
exit 0

