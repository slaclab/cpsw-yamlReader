#####################
### Arch Versions ###
#####################
AVAILABLE_ARCHES:=$(ARCHES)
ARCHES=$(filter $(HARCH) buildroot-2019.08-x86_64,$(AVAILABLE_ARCHES))
