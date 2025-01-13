########################
### Package versions ###
########################
CPSW_VERSION           = R4.5.2
CPSW_DEVICELIB_VERSION = R1.2.2

# Location of packages. On S3DF, this should be defaulted to EPICS_PACKAGE_TOP. On AFS, we default to an absolute AFS path
# This may also be provided on the command line or in the environment
ifeq ($(PACKAGE_TOP),)
ifneq ($(EPICS_PACKAGE_TOP),)
PACKAGE_TOP	= $(EPICS_PACKAGE_TOP)
else
$(error PACKAGE_TOP or EPICS_PACKAGE_TOP must be provided in the environment or on the command line)
endif
endif

# Packages location
CPSW_DIR         = $(PACKAGE_TOP)/cpsw/framework/$(CPSW_VERSION)/src
DEVICELIB_DIR    = $(PACKAGE_TOP)/cpsw/deviceLibrary/$(CPSW_DEVICELIB_VERSION)/$(TARCH)
