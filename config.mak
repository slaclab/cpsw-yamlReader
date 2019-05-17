#####################
### Arch Versions ###
#####################
AVAILABLE_ARCHES:=$(ARCHES)
ARCHES=$(filter $(HARCH) buildroot-2016.11.1-x86_64,$(AVAILABLE_ARCHES))
