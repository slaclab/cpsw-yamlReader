#ifndef YAMLREADER_API_H
#define YAMLREADER_API_H

#include <string>
#include <inttypes.h>
#include <stdexcept>
#include <boost/shared_ptr.hpp>

class IYamlReader;

typedef boost::shared_ptr<IYamlReader> YamlReader;

class IYamlReader
{
public:
    virtual const uint32_t getStartAddress()                        const = 0;
    virtual const uint32_t getEndAddress()                          const = 0;
    virtual const uint32_t getTarballSize()                         const = 0;
    virtual const bool     wasValid()                               const = 0;
    virtual void           setOutputDir( const std::string& dir )         = 0;
    virtual void           setFileName(  const std::string& name )        = 0;
    virtual void           readTarball()                                  = 0;
    virtual void           untar( const bool stripRootDir = false ) const = 0;

    static YamlReader create( const std::string& ipAddr );

    virtual ~IYamlReader() {};
};

#endif