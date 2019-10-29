# Release notes

Release notes for the yamlReader Driver.

## Releases:
* __R1.1.2__: 2019-10-28 Kukhee Kim
  * build with cpsw/framework R4.3.1 and cpsw/deviceLibrary R1.1.2
* __R1.1.1__: 2019-09-20 Kukhee Kim
  * build with cpsw/framework R4.2.0 and cpsw/DeviceLibrary R1.1.1

* __R1.1.0__: 2019-06-26 Kukhee Kim
  * build with cpsw/framework R4.1.2 and cpsw/deviceLibrary R1.1.0
  * Support reading to an arbitrary std::ostream
    (no unzip/untar support, though).
  * Support silencing or redirecting the messages that 
    are normally printed (necessary if you want to 
    read the yaml to stdout).
  * Port to the latest CPSW.
  * Use the standard CPSW makefiles.

* __R1.0.3__: 2019-02-06 J. Vasquez
  * Bug Fix: Update yaml-cpp to the correct verion 
    yaml-cpp-0.5.3_boost-1.64.0.

* __R1.0.2__: 2018-11-05 J. Vasquez
  * Update CPSW framework to R3.6.6 and boost to 1.64.0.
  * Update CPSW deviceLibrary to R1.0.1.

* __R1.0.1__: 2018-07-25 J. Vasquez
  * Fix bug when the file end is outside 32-bit word boundries.
  * Use the htobe32() function to transform the data to big-endian 
  *   indipendent of the formart used by the host cpu.  
  * Minor code cleanup and improvements.

* __R1.0.0__: 2018-04-20 J. Vasquez
  * First stable release.
