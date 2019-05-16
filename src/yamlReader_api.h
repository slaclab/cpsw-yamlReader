#ifndef YAMLREADER_API_H
#define YAMLREADER_API_H

#include <string>
#include <inttypes.h>
#include <stdexcept>
#include <cpsw_shared_ptr.h>

class IYamlReader;

typedef cpsw::shared_ptr<IYamlReader> YamlReader;

#define YAML_READER_TO_STDOUT  0
#define YAML_READER_TO_STDERR  1
#define YAML_READER_QUIET      2

class IYamlReader
{
public:
    virtual const uint32_t getStartAddress()                                          const = 0;
    virtual const uint32_t getEndAddress()                                            const = 0;
    virtual const uint32_t getTarballSize()                                           const = 0;
    virtual void           setOutputDir( const std::string& dir )                           = 0;
    virtual void           setFileName(  const std::string& name )                          = 0;
    virtual void           readTarball( int verb = YAML_READER_TO_STDOUT )                  = 0;
	virtual void           readTarball( std::ostream *, int verb = YAML_READER_TO_STDOUT )  = 0;
    virtual void           untar( const bool stripRootDir = false )                   const = 0;
	virtual void           setOutputStream(std::ostream *)                                  = 0;

    static YamlReader create( const std::string& ipAddr );

    virtual ~IYamlReader() {};
};

#endif
