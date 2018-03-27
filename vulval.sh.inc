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
## Abstract:             an set of auxiliary functions a) to produce reports (basic 
##                       and extended ones) in hypertext format; and b) to instruct
##                       a  user on how to launch head script
##
## Usage:                none
##
## Version:              0.0.8
##
## @author               k.mauch@
##
## @file                 vulval.sh.inc


## @function err_usage  Prompt user how to call us correctly 
function err_usage {

	# Self-explanatory
	echo "Error: incomplete parameter set, use '$0 ./_some_dir_name_' instead '$0'. Exiting."

	# Note: the 'do_footer()' is not needed since it's called before 'do_captron() '

	# Tell outer caller (if any) the script was terminated with an error
	exit -1

} # function usage


# Inform user necessary file is missing
function err_no_such_file {

	# Self-explanatory
	echo "Error: file $1 does not exist (thou should to), can't proceed. Exiting."

	# Note: the 'do_footer()' is not needed since it's called before 'do_captron() '

	# Tell outer caller (if any) the script was terminated with an error
	exit -1

} # function no_such_dir

# Inform user the correct directory name is must-have to runc current script
function err_no_such_dir {

	# Self-explanatory
	echo "Error: directory $1 does not exist. Exiting."

	# Note: the 'do_footer()' is not needed since it's called before 'do_captron() '

	# Tell outer caller (if any) the script was terminated with an error
	exit -1

} # function no_such_dir

# Function to put a caption into hypertext log and to prepared its hypertext extention
function do_caption {

	# Form HTML caption part of hypertext log 
	echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">"> $LOG
	echo "<html lang=\"en\">">> $LOG
	echo "<head>">> $LOG
		echo "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=ISO-8859-1\">">> $LOG
		# Reload every 5 seconds
		echo "<meta http-equiv=\"refresh\" content=\"5\"/>">> $LOG
		echo "  <title>LOG:: $MARKER </title>">> $LOG
		echo "  <link rel=\"stylesheet\" type=\"text/css\" href=\"gcov.css\">">> $LOG
	echo "</head>">> $LOG
	echo "<body bgcolor=\"#A0A0A0\">">> $LOG

		echo "    <tr><td class=\"title\"> $MARKER <br> <br>  </td></tr>">> $LOG
	echo "    <tr><td class=\"title\">Started at: ">> $LOG
	date >> $LOG
	echo "<br></td></tr>">> $LOG

	# Prepare "meta" in extention of hypertext log 
	echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">"> $LOG_EXT
	echo "<html lang=\"en\">">> $LOG_EXT
	echo "<head>">> $LOG_EXT
		# Reload every 10 seconds
		echo "<meta http-equiv=\"refresh\" content=\"10\"/>">> $LOG_EXT
	echo "</head>">> $LOG_EXT
	echo "</html>">> $LOG_EXT

	#TODO: deploy if required: FIRST_SECOND=`eval uptime | awk '{ print $1 }' `
	#TODO: deploy if required: LAST_SECOND=`eval uptime | awk '{ print $1 }' `

} # function do_caption

# Function to add time-stamped log entry to hypertext log
function commemorate
{
	echo "<br>">>$LOG
	date +%T:>>$LOG
	echo $1 $2 >> $LOG

} # function commemorate

# Function to add extended info into extention of hypertext log
function commemorate_x
{
	echo "<br>">>$LOG_EXT
	date +%T:>>$LOG_EXT
	echo $1 $2 >> $LOG_EXT

} # function commemorate_x

function do_step
{
	echo "<br>">>$LOG
	date +%T:>>$LOG

	echo " <a href=$LOG_EXT#$1>$1 $2</a> " >> $LOG

	echo " <p id=\"$1\">"  >> $LOG_EXT

	echo "<br>">>$LOG_EXT
	date +%T:>>$LOG_EXT
	echo $1 $2 >> $LOG_EXT

	echo -e ".\c" # "[$PRG_NAME]" $1 $2
	

} # function do_step


# Function to add HTML footer for successful run into hypertext log
function do_footer
{	
	echo "<br><br>" >> $LOG
	echo "    <tr><td class=\"title\">Finished at: ">> $LOG
	date >> $LOG

	echo "<br><br>" >> $LOG
        echo "<br><tr><td class=\"title\">Unpublished Copyright (c) 2017-2018 Embeddora Ltd, All Rights Reserved <br> <br>  </td></tr>">> $LOG
	echo "</body>">> $LOG
	echo "</html>" >> $LOG

} # function do_footer

# Function to add delimiter into hypertext log and into its hypertext extention and to close the tag in last one
function do_delimiter
{
	echo "<br><br>" >> $LOG
	echo "<br><br>" >> $LOG_EXT
	echo " </p>" >> $LOG_EXT

} # function do_delimiter

# Function to add HTML footer for FAILED run into hypertext log; (not used)
function do_footer_failed
{
	START_=$(date +%s)
	START_NS=$(date +%s.%N)
	echo "<br>">> $LOG
	date +%T:>>$LOG

	# Do part of HTML footer for FAILED run
	echo " FAILED, exiting with ($1)" >> $LOG

	do_footer 

	exit -1

} # function do_footer_failed
