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
## Abstract:             a script to produce a potential vulnerabilities report
##                       collected in respect to files contained in folder defined
##                       by command line parameter passed to this script
##
## Note:                 without 'vulval.sh.inc' placed beneath this script
##                       won't work, as well as it won't work without routine named
##                       'vulval' kept beneath, either, for it performs core
##                       activity of such potential vulnerability check
##
## Usage:                './vulval ./locally_stored_unpacked_rootfs', where
##                       './locally_stored_unpacked_rootfs' is a directory in which
##                       potential vulnerabilities to be detected
##
## Version:              0.0.8
##
## @author               k.mauch@
##
## @file                 vulval.sh




# File to include (contains aux. functions)
INCLUDE_FILE="$0.inc"

# Feed the functions implemented beneath into this script
. $INCLUDE_FILE

# File to deploy (contains keywords to find in binaries functions). Not mandatory under current model
KEYWORDS_FILE="$0.keywords"

# File to perform core activity behind potential vulnerability check
ROUTINE_FILE="vulval"

# Check if library with aux. functions exists
[ -f "$INCLUDE_FILE" ] || err_no_such_file "$INCLUDE_FILE"

# Check if main processing file exists
[ -f "$ROUTINE_FILE" ] || err_no_such_file "$ROUTINE_FILE"

# Check if not less than two parameters given on a command line, exit is not
[ -z $1 ] && err_usage

# Check if correct direcotry name is given on a command line, ethis if not 
[ -d "$1" ] || err_no_such_dir $1



# Clean after (presumed) previous run
rm -f $LOG $LOG_EXT $0.log $0~ $COMPOSITES_FNAME $TRIVIAS_FNAME $VARNAMES_FNAME

# Set session-wide var to avoid non-English symbols in output of 'date', etc
export LC_TIME=en_US.UTF-8

# File name of hypertext log file
LOG="./_report.html"

# File name of hypertext extention of hypertext log 
LOG_EXT="./_report.ext.html"

# Program name (may be whatever you find relevant)
PRG_NAME="$0"

SHELLCODE_FILES=`ls *.{arm,mips}`

# Marker string 
MARKER="Lexical check of binaries stored in '$1' against keywords stored in '$KEYWORDS_FILE' and against shell code patterns stored in '$SHELLCODE_FILES'. <br><br> Autogenerated by '$PRG_NAME'"

# Ignore custom filenames which might contain keywords
EXCEPTIONS=($PRG_NAME $INCLUDE_FILE $KEYWORDS_FILE $LOG $LOG_EXT )

# Form a HTTP header in hypertext log file
do_caption

# Take output of <pwd> to form URL of it later
CURDIR=`eval pwd | awk '{ print $0 }' `

# Launch <Mozilla-F.F.> to observe the progress in hypertext form
#+++firefox -url file://$CURDIR/$LOG > /dev/null 2>&1  &

# Initialize step counter
i=0

# Recursively throughout all the files contained in all of target folders, suppressing error messages
for FNAME in `find "$@" -type f 2>/dev/null`

do
	# Don't process those excluded from search
	if [[ ! ${EXCEPTIONS[*]} =~ "$FNAME" ]]; then

		# Assign 'footprint' variable
		STEP="STEP-$i"	

		# Comment current 'do'
		do_step "$STEP:" " processing $FNAME"

		echo "<br>" >> $LOG_EXT

		# Get the timestamt of current file
		TMP_TIME_STAMP=`stat $FNAME --format=%y`
		TMP_STAMP="File $FNAME was last modified on $TMP_TIME_STAMP"
		AT=${TMP_STAMP//$'\n'/$'\n'<br>}

		echo "<br>$AT<br>" >> $LOG_EXT

		echo "<hr noshade>" >> $LOG_EXT

		#ATY=`valgrind --tool=massif  ./"$ROUTINE_FILE" $FNAME`
		#ATY=`valgrind --tool=callgrind  ./"$ROUTINE_FILE" $FNAME`
		ATY=`./"$ROUTINE_FILE" $FNAME`
		AT=${ATY//$'\n'/$'\n'<br>}

		echo "<br>$AT<br>" >> $LOG_EXT

		# Process each keyword stored in '$KEYWORDS_FILE' as potentially hazardous (once found generate arm-linux disasm. output)
		for KEYWORD in `cat $KEYWORDS_FILE`; do

			# Remove 'continue' below to produce extended report (quite exuberant and, frankly, pointless)
			continue

			# Skip "Not an ARM-ELF file errors"
			TMP_RES=`arm-linux-gnueabi-readelf -a  $FNAME 2>/dev/null | grep $KEYWORD`

			# (ARM) Process only those files where the call to keywords was really found by 'readelf'
			if [[ -n $TMP_RES ]]
			# Check the file if it were an ARM executable in ELF format
			then

				echo "<hr noshade>" >> $LOG_EXT

				# Here any output is affordable 
				ATY=`arm-linux-gnueabi-readelf -a $FNAME  | grep $KEYWORD | tr -d '[<>]'`
				AT=${ATY//$'\n'/$'\n'<br>}

				echo "(Platf: ARM) Keyword $KEYWORD: <br>$AT<br>" >> $LOG_EXT

				# Amn empty error output presumed
				ATY=`arm-linux-gnueabi-objdump -S $FNAME  | grep $KEYWORD | tr -d '[<>]'`
				AT=${ATY//$'\n'/$'\n'<br>}
		
				echo "<br>$AT<br>" >> $LOG_EXT

			fi # if [[ -n $TMP_RES ]]; then

			# Skip "Not an MIPS-ELF file errors"
			TMP_RES=`mips-linux-gnu-readelf -a  $FNAME 2>/dev/null | grep $KEYWORD`

			# (MIPS) Process only those files where the call to keywords was really found by 'readelf'
			if [[ -n $TMP_RES ]]
			# Check the file if it were an MIPS ELF-executable
			then

				echo "<hr noshade>" >> $LOG_EXT

				# Here any output is affordable 
				ATY=`mips-linux-gnu-readelf -a $FNAME  | grep $KEYWORD | tr -d '[<>]'`
				AT=${ATY//$'\n'/$'\n'<br>}

				echo "(Platf: MIPS) Keyword $KEYWORD: <br>$AT<br>" >> $LOG_EXT

				# Get rid of 'can't diassemble for architecture unknown' in error output
				ATY=`mips-linux-gnu-objdump -S $FNAME  2>/dev/null | grep $KEYWORD | tr -d '[<>]'`
				AT=${ATY//$'\n'/$'\n'<br>}
		
				echo "<br>$AT<br>" >> $LOG_EXT

			fi # if [[ -n $TMP_RES ]]; then

		done # for KEYWORD in  `cat ./keywords.in`; do

		echo "<hr noshade=\"\" size=\"20\" >" >> $LOG_EXT

	fi # if [[ ! ${EXCEPTIONS[*]} =~ "$FNAME" ]]; then

	# Increase step counter
	((i++))

done # FNAME cycle 

# Prevent user scrolling down for more data at the position where all of data is listed above
echo "<br>[end]<br>" >> $LOG_EXT

# Add some empty space into HTML-stuff to delimit last step form footer
do_delimiter

# Form a HTTP footer in hypertext log file
do_footer

# Skip to a new line in a console
echo ""

# Exit without error
exit 0
