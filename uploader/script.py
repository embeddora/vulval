#!/usr/bin/env python2 
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
# Abstract:      a script to upload a product of successful run of 'voluval.sh'
#                over FTP server (with predefined credentials)
#
# Usage:         run 'script.py'
#   
# Version:       0.0.1
#
# Todo:		 decide which kind will be product will be in future (text, binary,
#		 etc) and correct file opening flag 'rb'. By now a binary kind is
#		 used as universal.
#

import ftplib

import os

import sys

import traceback

FTP_SERVER = 'ftp.XXXXXX'

FTP_USER = 'XXXXXX'

FTP_PASSWD = 'XXXXXX'

FTP_DIRECTORY = 'development.XXXXXX.com'

LCL_PROD1_FILE = '../_report.html'

LCL_PROD2_FILE = '../_report.ext.html'
  
print "Entering FTP server " + FTP_SERVER

ftp = ftplib.FTP()

ftp.connect(FTP_SERVER)

print ftp.getwelcome()

try:
    try:
        ftp.login(FTP_USER, FTP_PASSWD)

        ftp.cwd(FTP_DIRECTORY)

        print "Entered directory ", ftp.pwd()
  
	for fullname in [LCL_PROD1_FILE, LCL_PROD2_FILE]:

		print "Uploading file " + fullname

		name = os.path.split(fullname)[1]

		f = open(fullname, "rb")

		ftp.storbinary('STOR ' + name, f)

		f.close()

		print "OK"
          
        print "Files:"

        print ftp.retrlines('LIST')

    finally:

        print "Leaving with an FTP-access-failure"

        ftp.quit()

except:

    traceback.print_exc()
