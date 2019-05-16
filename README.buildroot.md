# yamlReader for the SLAC High Performance System

## Driver buildroot cross-compilation

This driver is crosscompiled against the buildroot versions listed in the variable **BR_ARCHES**,
which is defined in the file **config.mak**.

The driver is compiled also for the host architecture, which is defined in the **HARCH** in the
same file.
