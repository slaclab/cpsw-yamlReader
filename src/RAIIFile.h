#ifndef RAIIFILE_H
#define RAIIFILE_H

#include <fstream>
#include <stdexcept>

class RAIIFile
{
public:
    RAIIFile(const std::string &name, const std::_Ios_Openmode& mode);

    std::ofstream *f() { return &file; };

    std::ostream& put( char c ) { return file.put( c ); };

    virtual ~RAIIFile() { file.close(); };

private:
    std::ofstream file;
};

#endif
