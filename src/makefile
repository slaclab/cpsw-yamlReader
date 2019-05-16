# //@C Copyright Notice
# //@C ================
# //@C This file is part of CPSW. It is subject to the license terms in the LICENSE.txt
# //@C file found in the top-level directory of this distribution and at
# //@C https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html.
# //@C
# //@C No part of CPSW, including this file, may be copied, modified, propagated, or
# //@C distributed except according to the terms contained in the LICENSE.txt file.

# Makefile template for CPSW software:

# Locate CPSW:
ifndef TOPDIR
TOPDIR=.
endif

# Note: must include from $(SRCDIR) (which is redefined
#       when recursing into subdirs).
SRCDIR=.

# 'release.mak' must define CPSW_DIR
include $(TOPDIR)/release.mak
# while release.mak is in git, release.local.mak should
# not be and can be overridden for development and other
# purposes...
-include $(TOPDIR)/release.local.mak

include $(CPSW_DIR)/defs.mak

# If you want to add your own ARCHSPECIFIC_VARS or
# ARCHSPECIFIC_LIBVARS then you *must* do so before
# including 'defs.mak'

# ARCHSPECIFIC_VARS    += MYVAR
# ARCHSPECIFIC_LIBVARS += mypackage

# Headers to be installed (must exist prior to building or
# you must add a rule to pre-build them)
HEADERS += yamlReader_api.h

# Modification of headers listed in DEP_HEADERS triggers
# re-computation of all dependencies.
#
# 'Ordinary' modification of headers (i.e., modifications which
# do not change the dependencies themselves) are tracked
# by the automatic dependency analysis.
# However, if any of the DEP_HEADERS changes then *all* dependencies
# are recomputed.
# Normally, only dependencies for individual .c and .cc files are
# recomputed as those change. 
DEP_HEADERS += $(HEADERS)
DEP_HEADERS += RAIIFile.h
DEP_HEADERS += yamlReader.h

# List static libraries to build (only built if
# the user sets WITH_SHARED_LIBRARIES_<arch>=YES):
STATIC_LIBRARIES_YES += yamlReader

# List shared libraries to build (only built if
# the user sets WITH_SHARED_LIBRARIES_<arch>=YES):
SHARED_LIBRARIES_YES += yamlReader

# List programs to build:
PROGRAMS         += readYaml

# List sources for each target:
yamlReader_SRCS  += yamlReader.cc
yamlReader_SRCS  += RAIIFile.cc

VPATH+=$(SRCDIR)/test

readYaml_SRCS    += readYaml.cc

# Identify directories where to look for headers:
INCLUDE_DIRS      += $(DEVICELIB_DIR)/include

# Identify libraries required by each program + testprogram.
# List them *without* 'lib' prefix or any suffix.
# Don't forget to add $(CPSW_LIBS) in order to link CPSW
# and any dependent libraries.

# You can enforce linking a static version of a particular
# library by appending '.a' (still no 'lib' prefix)
readYaml_LIBS     += $(addsuffix .a,yamlReader deviceLib) $(CPSW_STATIC_LIBS)

# Tell them where to look for 'someLib' -- this example
# shows how to look in a target-architecture specific
# subdirectory (of a package built with the same makefiles)
#
deviceLiblib_DIR = $(DEVICELIB_DIR)/lib
deviceLib_alib_DIR = $(DEVICELIB_DIR)/lib

# Include rules
include $(CPSW_DIR)/rules.mak
