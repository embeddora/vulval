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
# Abstract:      a scipt to produce "unsquashfs_all.sh" and "unyaffs2" needed for
#                deeper research of firmware images being exposed to potential code
#                vulnerability analysys done by 'vulval' 
#
# Usage:         run ./make_extractors.sh from within empty directory (internet
#                connection needed)
#   
# Version:       0.0.1
#


# Subsring to notify the aptitude's string "is already the newest version" is here
APTGET_CORR_RESP="newest"

# Check if package has been apt-get-installed, try to install it if not, and exit once could not install
apt_install()
{
	# Check if an install simulation gives something like "is already the newest version" in responce
	if [[ -z `apt-get install -s $1 | grep $APTGET_CORR_RESP` ]]
	then

		# Silently install the package without disturbing the user with Yes/No promptage
		echo -e "Y" | sudo apt-get install $1    >/dev/null 2>&1 

		# Check same again (see above for plain comment)
		if [[ -z `apt-get install -s $1 | grep $APTGET_CORR_RESP` ]]
		then

			# Self-explanatory
			echo "Can't install $1 with apt-get or can't recognize it as installed. (Are you using yum, dpkg, rpm?) Exiting anyway ... "

			# Exit with unique non-zero status 
			exit 1
		else
			# Self-explanatory
			echo "Have just installed $1 with apt-get and found it to be such"
		fi
	else
		# Self-explanatory
		echo "Found $1 to be installed with apt-get "
	fi

} # ed of 'apt_install()'

# Check if critically needed file exists and exit once does not
check_milestoene_file()
{
	# Check if critical file exists
	if [ ! -e $1 ]
	then
		# Function has been called with one parameeter?
		if [ -z "$2" ]; then

			# Self-explanatory 
			echo "bad, the $1 seems to be not here, exiting ..."
		else
			# Verbose current failure in a special way
			echo $2
		fi

		# Exit with unique non-zero status
		exit 2
	fi

} # end of check_milestone_file()



# Archive name with "Firmware Modkit" source
FW_MOD_KIT_ARCH="./source-archive.zip"

# First target
UNSQUASH="./firmware-mod-kit/unsquashfs_all.sh"

# Second target
UNYAFFS2="./firmware-mod-kit/src/yaffs2utils/unyaffs2"

# Check if files are alredy 
if [[ -e "$UNSQUASH"  &&   -e "$UNYAFFS2" ]];then

	# Self-explanatory
	echo "both files are here, no use to do them again "

	# Skip doing 'download&compile' (which follows) over and over
	exit 0
fi
 
# Check if 'zlib' headers are available
apt_install zlib1g-dev

# Check if 'lzma' headers are available
apt_install liblzma-dev

# If archive with "Firmware Modkit" is not here  
if [ ! -e $FW_MOD_KIT_ARCH ]
then
	# Obtain "Firmware Modkit" and store it locally 
	wget https://storage.googleapis.com/google-code-archive-source/v2/code.google.com/firmware-mod-kit/source-archive.zip
fi

# The archive with "Firmware Modkit" has not been downloaded - no use to proceed
check_milestone_file $FW_MOD_KIT_ARCH

# A void file to tell the unpack of "Firmware Modkit" archive was successful 
TARG_MAKEFILE="./firmware-mod-kit/src/others/Makefile"

# Don't unzip once seems to be already unsipped
[ ! -e $TARG_MAKEFILE ] &&	unzip source-archive.zip

# Exit once uppacking likely has been failed
check_milestone_file $TARG_MAKEFILE

# Rework a 'Makefile' to skip building obsoleted UNSQUASH-2 - make a "Firmware Modkit" compilable on standart set of Ubuntu-16 (+buildessentials, +zlib, +lzma)
sed -i '/make -C .\/squashfs-2.2-r2-7z/d' $TARG_MAKEFILE

# Enter working directory
cd ./firmware-mod-kit/src/

# Don't reconfigure once seems to be already configured, configure otherwise 
[ ! -e ./Makefile ] && ./configure

# Check if configured and exit once not
check_milestone_file ./Makefile

# Deploy just generated Makefile
make -C ./

cd ../..

# Check if file is available and notify an error if not
check_milestoene_file $UNSQUASH  "bad, no $UNSQUASH was generated, can't proceed"

# Check if file is available and notify an error if not
check_milestoene_file $UNYAFFS2  "bad, no $UNYAFFS2 was generated, can't proceed"

# Self-explanatory
echo "Utilities <$UNSQUASH> and <$UNYAFFS2> are available. Success."

# Another (a second one - to be more precise) point of exit-with-success
exit 0
