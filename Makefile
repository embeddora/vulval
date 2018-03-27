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
# Abstract:            a makefile to build C++ routine named 'vulval'
#
# Usage:               none
#
# Version:             0.0.8



# A project name used for distibutives (source code and docs) naming only
PROJ="Vulval"

# It's a program (or routine) we're building by present make process
TARGET=./vulval

# Only compiler to be used by present make process
CPP=$(PREFIX)g++

# Defining an exact C++ standard strictly we avoid warnings on type mismatch and C++ statements misinterpretation
CPPFLAGS=-std=gnu++11
#
# -DEXCESSIVE_OUTPUT (to report that an exact pattern/shellcode wasn't found; notmally only those found to be reported)
#
# -DCUSTOM_SEARCH (to call 'std::search' indirectly which is supposed to provide cusomized search procedure)
#

# Feed C++ boost libraries from this place (they're assumed to be already installed)
BOOSTLIBDIR=/usr/lib/x86_64-linux-gnu

# Tell compiler where to search for libraries on linkage stage 
LDFLAGS=-L$(BOOSTLIBDIR)  

# Configuration parameters for Doxygen
DOCSCFG=./documents.cfg

# These two are produced by Doxygen, and should be removed each time we're reworking a C++ code
DOCSDIR=./html ./latex 

# Objects of our target routine
OBJS=	hazent.o \
	shellcode.o exploit.o  \
	datent.o \
	buffer.o file.o  \
	vulval.o 

# Boost libraries required for our routine to get linked
EXTRA_OBJS=-lboost_system -lboost_filesystem

# Default target of present make process
all: $(TARGET)

# A rule to make objects out of C++ files
%.cpp.o: %.cpp
	$(CPP) $(CPPFLAGS)  -c -o $@ $<

# A rule to produce target routine out of its dependencies
$(TARGET): $(OBJS)
	$(CPP) $(LDFLAGS) $(OBJS) $(EXTRA_OBJS) -o $@ 

# A stuff to be removed each time we're doing 'make clean'. CRBG abbreviation stands for 'garbage'
GRBG=	./*.o ./*~

# A stuff to be removed each time we're doing 'make clean'. CRBGxt abbreviation stands for 'extra garbage'
GRBGxt= $(TARGET) *.tar.gz *.html

# Enumeration of phony targets list members
.PHONY: clean docs tar 

# A rule to produce documentation by Doxygen 
docs: $(DOCSCFG)
	doxygen $<
	cd ./latex; \
	find . -type f -name '*' -print0 | xargs -0 sed -i 's/Generated by Doxygen 1.8.11/ We Evaluate an Embedded Firmware Whatever It Is ! /g'; \
	find . -type f -name '*' -print0 | xargs -0 sed -i 's/Generated by Doxygen/ 2018   CONFIDENTIAL   Produced by Embeddora Ltd/g'; \
	make 

# A rule to produce two '*.tar.gz' archives (also known as 'distributives') one with source code another with documentation
tar:
	$(MAKE) clean ; \
	$(MAKE) docs; \
	tar cfvz $(PROJ).source.tar.gz ./*.cpp ./*.hpp ./*.arm ./*.mips ./*.any ./vulval.sh*  \
		./mainpage.dox ./documents.cfg ./Makefile ;\
	tar cfvz $(PROJ).docs.tar.gz $(DOCSDIR)

# A rule to remove source back-up files, linked target raoutine, html-report, and *.tar.gz distributives
clean:
	rm $(GRBG) $(GRBGxt)

# A rule to remove documentation in addition to aforementioned source backups, target, report, and distros
distclean:
	rm $(GRBG) $(GRBGxt) ; rm -r -v $(DOCSDIR) 