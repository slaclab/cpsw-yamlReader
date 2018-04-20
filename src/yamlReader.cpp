#include <yamlReader.h>

static Hub buildHier(const char *ip_addr)
{
    NetIODev      commDev     = INetIODev::create("udp",  ip_addr);
    MMIODev       mmio        = IMMIODev::create("mmio", 0x80000000, LE );
    AxiMicronN25Q prom        = IAxiMicronN25Q::create("prom");
    IntField      tarballAddr = IIntField::create("CPSW_TARBALL_ADDR_C");

    ProtoStackBuilder bldr = IProtoStackBuilder::create();
    bldr->setSRPVersion(IProtoStackBuilder::SRP_UDP_V2);
    bldr->setUdpPort(8192);

    commDev->addAtAddress( mmio, bldr );

    mmio->addAtAddress( tarballAddr, 0x00000404 );
    mmio->addAtAddress( prom, 0x02000000 );

    return commDev;
}

IYamlReaderImpl::IYamlReaderImpl( const std::string& ipAddr )
:
    dirName( "." ),
    fileName( "yaml.tar.gz" ),
    outputFile( dirName + "/" + fileName ),
    gotValidTarball( false )
{
    try
    {
        Hub root               = buildHier( ipAddr.c_str() );
        ScalVal_RO tarballAddr = IScalVal_RO::create( root->findByName( "mmio/CPSW_TARBALL_ADDR_C" ) );
        prom                   = IEEProm::create( root->findByName( "mmio/prom" ) );

        tarballAddr->getVal(&startAddress);
    }
    catch (CPSWError e)
    {
        fprintf( stderr, "CPSW Error during YamlReader object construction: %s\n",  e.getInfo().c_str() );
        throw;
    }
}

void IYamlReaderImpl::setOutputDir( const std::string& dir )
{
    dirName = dir;
    outputFile = dirName + "/" + fileName;
}

void IYamlReaderImpl::setFileName(  const std::string& name )
{
    fileName = name;
    outputFile = dirName + "/" + fileName;
}

void IYamlReaderImpl::readTarball()
{
    RAIIFile file( outputFile, std::ios_base::out | std::ios_base::binary );

    uint32_t data[mem_block_size];
    bool     first_loop = true;
    uint32_t addr       = startAddress;

    try
    {
        // Setup for 32-bit address mode
        prom->setAddr32BitMode( true );

        while( 1 )
        {
            prom->readProm( addr, data );

            // On first loop, verify if it is a valid GZ file
            if ( first_loop )
            {
                uint16_t header = ( (data[0] >> 16) & 0xffff );

                if ( header != 0x1f8b )
                    throw std::runtime_error( "Invalid GZIP header. Aborting." );

                first_loop = false;
            }

            for ( int i = 0; i < 64; ++i )
            {
                if ( data[i] == 0xffffffff )
                {
                    endAddress = addr;
                    file.put( 0 );
                    gotValidTarball = true;
                    return;
                }

                file.put( (data[i] >> 24) & 0xFF );
                file.put( (data[i] >> 16) & 0xFF );
                file.put( (data[i] >>  8) & 0xFF );
                file.put( (data[i]) & 0xFF       );
            }
            addr += byte_step_size;
        }
    }
    catch ( CPSWError e )
    {
        fprintf( stderr,"CPSW Error during PROM reading: %s\n", e.getInfo().c_str() );
        throw;
    }
}

void IYamlReaderImpl::untar( const bool stripRootDir ) const
{
    std::string cmd = "tar -zxf " + outputFile + " -C " + dirName;

    if ( stripRootDir )
        cmd += " --strip-components=1";

   system( cmd.c_str() );
}

YamlReader IYamlReader::create( const std::string& ipAddr )
{
    return YamlReader( boost::make_shared<IYamlReaderImpl>( ipAddr ) );
}