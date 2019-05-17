# yamlReader for the SLAC High Performance System

## Driver buildroot cross-compilation

This driver is crosscompiled against the buildroot versions listed in the variable **ARCHES**,
which is defined in the file **config.mak**. Obviously these can only be a subset of the
architectures CPSW itself has been built for.

The driver is compiled also for the host architecture, which is defined in the **HARCH** in the
same file.
