#include "RAIIFile.h"

RAIIFile::RAIIFile( const std::string &name, const std::_Ios_Openmode& mode )
{
    file.open( name.c_str(), mode );

    if ( ! file.is_open() )
        throw std::runtime_error( std::string( "Unable to open output file " + name ).c_str() );
}

