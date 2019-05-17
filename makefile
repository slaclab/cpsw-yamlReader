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

SUBDIRS+=src

# Include rules
include $(CPSW_DIR)/rules.mak
