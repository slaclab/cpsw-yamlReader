-include config.mak

SRCDIR = src

TOPTARGETS = all clean install uninstall

.PHONY: $(TOPTARGETS)

$(TOPTARGETS):
	@printf '\n========== Building for $(HARCH) ==========\n\n'
	H_VERSION=$(HARCH) $(MAKE) -C $(SRCDIR) $(MAKECMDGOALS)
	@for br_arch in $(BR_ARCHES); do \
		printf "\n========== Building for $$br_arch ==========\n\n"; \
		BR_VERSION=$$br_arch $(MAKE) -C $(SRCDIR) $(MAKECMDGOALS); \
	done
