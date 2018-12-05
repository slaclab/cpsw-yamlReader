################
### Lib name ###
################
LIB_NAME = yamlReader

#####################
### Arch Versions ###
#####################
# Host version
HARCH      = rhel6
# Buildroot versions
BR_ARCHES += buildroot-2016.11.1

########################
### Package versions ###
########################
CPSW_VERSION           = R3.6.6
BOOST_VERSION          = 1.64.0
YAML_CPP_VERSION       = yaml-cpp-0.5.3
CPSW_DEVICELIB_VERSION = R1.0.0

########################
### Path definitions ###
########################
# Location of BuildRoot home:
BUILDROOT_HOME=/afs/slac/package/linuxRT/$(BR_VERSION)
# Location CrossCompiler HOME:
XCROSS_HOME=$(BUILDROOT_HOME)/host/linux-x86_64/x86_64/usr/bin/x86_64-buildroot-linux-gnu-

# Package top
PACKAGE_TOP      = /afs/slac/g/lcls/package
# Packages location
CPSW_DIR         = $(PACKAGE_TOP)/cpsw/framework/$(CPSW_VERSION)/$(TARCH)
BOOST_DIR        = $(PACKAGE_TOP)/boost/$(BOOST_VERSION)/$(TARCH)
YAML_CPP_DIR     = $(PACKAGE_TOP)/yaml-cpp/$(YAML_CPP_VERSION)/$(TARCH)
DEVICELIB_DIR    = $(PACKAGE_TOP)/cpsw/deviceLibrary/$(CPSW_DEVICELIB_VERSION)/$(TARCH)
