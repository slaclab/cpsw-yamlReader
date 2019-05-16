#ifndef YAMLREADER_H
#define YAMLREADER_H

#include <stdexcept>
#include <cstdlib>
#include <iterator>
#include <boost/make_shared.hpp>
#include <PromApiUser.h>
#include <AxiMicronN25Q.h>
#include <cpsw_api_builder.h>
#include <cpsw_api_user.h>
#include <RAIIFile.h>
#include <yamlReader_api.h>

static const size_t mem_block_size      = 64;                             // Number of memory block
static const size_t mem_byte_size       = 4;                              // Size in bytes of each memory location
static const size_t mem_block_byte_size = mem_block_size * mem_byte_size; // Size in bytes of the memory

class IYamlReaderImpl : public IYamlReader
{
public:
    IYamlReaderImpl( const std::string& ipAddr );
    virtual ~IYamlReaderImpl() {};

    virtual const uint32_t getStartAddress() const { return startAddress;                };
    virtual const uint32_t getEndAddress()   const { return endAddress;                  };
    virtual const uint32_t getTarballSize()  const { return (endAddress - startAddress); };

    virtual void           setOutputDir( const std::string& dir );
    virtual void           setFileName(  const std::string& name );

    virtual void           readTarball(bool quiet = 0);
	virtual void           readTarball(std::ostream *, bool quiet = 0);
    virtual void           untar( const bool stripRootDir = false ) const;

	// stream where to dump data -- is *not* closed by this library
	virtual void           setOutputStream(std::ostream *);

private:
    std::string dirName;
    std::string fileName;
    std::string outputFile;
    EEProm      prom;
    uint32_t    startAddress;
    uint32_t    endAddress;

	std::ostream *ostream;

    void copyWord( const uint32_t& u32, std::ostream* file, bool trim_tail );
};

#endif
