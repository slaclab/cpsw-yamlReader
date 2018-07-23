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
    outputFile( dirName + "/" + fileName )
{
    try
    {
        Hub root               = buildHier( ipAddr.c_str() );
        ScalVal_RO tarballAddr = IScalVal_RO::create( root->findByName( "mmio/CPSW_TARBALL_ADDR_C" ) );
        prom                   = IEEProm::create( root->findByName( "mmio/prom" ) );

        tarballAddr->getVal(&startAddress);

        printf( "Tarball start address found: 0x%08X\n", startAddress );
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

    uint32_t raw_data[mem_block_size];
    bool     first_loop = true;
    uint32_t addr       = startAddress;

    printf( "Starting reading of the tarball file from the PROM...\n" );
    try
    {
        // Setup for 32-bit address mode
        prom->setAddr32BitMode( true );

        while( 1 )
        {
            prom->readProm( addr, raw_data );

            // On first loop, verify if it is a valid GZ file
            if ( first_loop )
            {
                uint16_t header = ( (raw_data[0] >> 16) & 0xffff );

                if ( header != 0x1f8b )
                    throw std::runtime_error( "Invalid GZIP header. Aborting." );

                first_loop = false;
            }

            for ( int i = 0; i < mem_block_size; ++i )
            {
                if ( raw_data[i] == 0xffffffff )
                {
                    endAddress = addr;
                    file.put( 0 );

                    printf( "A valid tarball was found:\n" );
                    printf( "   Start address     : 0x%08X\n",   startAddress );
                    printf( "   End address       : 0x%08X\n",   endAddress   );
                    printf( "   Tarball file size : %d bytes\n", endAddress - startAddress  );
                    printf( "The tarball was written to %s\n",   outputFile.c_str() );
                    return;
                }

                file.put( (raw_data[i] >> 24) & 0xFF );
                file.put( (raw_data[i] >> 16) & 0xFF );
                file.put( (raw_data[i] >>  8) & 0xFF );
                file.put( (raw_data[i]) & 0xFF       );
            }
            addr += mem_block_byte_size;
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

    printf( "The tarball was ungziped and untared on %s\n",  dirName.c_str() );

    if ( stripRootDir )
        printf( "The root directory in the tarball was stripped\n" );

}

YamlReader IYamlReader::create( const std::string& ipAddr )
{
    return YamlReader( boost::make_shared<IYamlReaderImpl>( ipAddr ) );
}