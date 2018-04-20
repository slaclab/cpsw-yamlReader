# yamlReader for the SLAC High Performance System

## How to use the library

### Create an instance of IYamlReader

You can use the **IYamlReader::create** factory function to create an instance of the IYamlReader class (actually a smart pointer to it).

The factory function takes a single argument: the IP address of the target FPGA.

During the construction of the object, the PROM's start address of the YAML tarball is read from register **CPSW_TARBALL_ADDR_C** at offset
**0x0404**.

The communication with the FPGA is done using UDP port 8192, and SRP version 2.

### Define and output location for the YAML file

You can use the methods **setOutputDir** and **setFileName** to set the destination folder and file name of the YAML tarball respectively.

By default, the destination folder is the current directory and the file name is **yaml.tar.gz**.

### Read the YAML tarball

The method **readTarball** reads the YAML tarball from the PROM into the destination file. Initially, the first 2 bytes read are check to
verify if the PROM area contains a valid GZ file header (*0x1F8B*). If not, the reading is aborted.

### Untar the resulting file.

The method **untar** provides a way to untar the resulting YAML tarball file. It takes a bool argument, if set to true the root directory
in the tarball is stripped during untar process.

## Example

An example utility program is provide as a reference: **src/test/readYaml.cpp**