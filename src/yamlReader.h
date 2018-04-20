#ifndef YAMLREADER_H
#define YAMLREADER_H

#include <stdexcept>
#include <cstdlib>
#include <boost/make_shared.hpp>
#include <PromApiUser.h>
#include <AxiMicronN25Q.h>
#include <cpsw_api_builder.h>
#include <cpsw_api_user.h>
#include <RAIIFile.h>
#include <yamlReader_api.h>

static const size_t mem_block_size  = 64;
static const size_t byte_step_size  = mem_block_size*4;

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

    virtual void           readTarball();
    virtual void           untar( const bool stripRootDir = false ) const;

private:
    std::string dirName;
    std::string fileName;
    std::string outputFile;
    EEProm      prom;
    uint32_t    startAddress;
    uint32_t    endAddress;
};

#endif
