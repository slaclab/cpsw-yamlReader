# Release notes

Release notes for the yamlReader Driver.

## Releases:
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
