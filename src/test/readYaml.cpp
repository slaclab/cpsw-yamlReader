#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <arpa/inet.h>
#include <getopt.h>
#include <yaml-cpp/yaml.h>
#include <cpsw_api_user.h>
#include <yamlReader_api.h>

static void usage(const char* name)
{
    printf( "Usage: %s [-a ip_addr] [-d out_dir] [-f file_name] -u | -h\n", name );
    printf( "    -h           : show this message.\n" );
    printf( "    -a ip_addr   : IP address of the target FPGA.\n" );
    printf( "    -d out_dir   : Output directory to write the read tarball (Optional. Default to \".\").\n" );
    printf( "    -f file_name : Output file name (Optional. Default: \"yaml.tar.gz\").\n" );
    printf( "    -u           : Untar the tarball in the output directory.\n" );
    printf( "    -s           : Strip the root directory while untaring (Must be used with -u).\n" );
    printf( "    -v           : Read firmware informatio (Must be used with -u and -s).\n" );
    printf( "\n" );
}

class IYamlSetIP : public IYamlFixup
{
    public:
        IYamlSetIP( std::string addr ) : ipAddr( addr ) {}

        void operator()(YAML::Node &root, YAML::Node &top) { root["ipAddr"] = ipAddr.c_str(); };

        ~IYamlSetIP() {}

    private:
        std::string ipAddr;
};

int main (int argc, char **argv)
{
    unsigned char buf[sizeof(struct in6_addr)];
    std::string   ipAddr;
    std::string   outDir;
    std::string   fileName;
    int           c;
    bool          untar   = false;
    bool          strip   = false;
    bool          readVer = false;

    while((c =  getopt(argc, argv, "a:d:f:usv")) != -1)
    {
        switch (c)
        {
            case 'a':
                if (!inet_pton(AF_INET, optarg, buf))
                {
                    fprintf(stderr, "Invalid IP address...\n" );
                    usage( argv[0] );
                    exit(1);
                }
                ipAddr = std::string(optarg);
                break;
            case 'd':
                outDir= std::string(optarg);
                break;
            case 'f':
                fileName = std::string(optarg);
                break;
            case 'u':
                untar = true;
                break;
            case 's':
                strip = true;
                break;
            case 'v':
                readVer = true;
                break;
            default:
                usage( argv[0] );
                exit(1);
                break;
        }
    }

    if ( ipAddr.empty() )
    {
        fprintf(stderr,"Must specify an IP address.\n" );
        exit(1);
    }

    YamlReader tr = IYamlReader::create( ipAddr );

    if ( !fileName.empty() )
        tr->setFileName( fileName );

    if ( !outDir.empty() )
        tr->setOutputDir( outDir );

    // Read tarball from PROM
    tr->readTarball();

    if ( untar )
    {
        // Untar tarball
        tr->untar( strip );


        if ( strip && readVer )
        {
            printf(  "\n" );
            printf( "Reading firmware version information...\n" );
            try
            {
                std::string topYaml = outDir + "/000TopLevel.yaml";
                IYamlSetIP setIP(ipAddr);
                Path root = IPath::loadYamlFile( topYaml.c_str(), "NetIODev", NULL, &setIP );

                ScalVal_RO fpgaVers    = IScalVal_RO::create (root->findByName("/mmio/AmcCarrierCore/AxiVersion/FpgaVersion"));
                ScalVal_RO bldStamp    = IScalVal_RO::create (root->findByName("/mmio/AmcCarrierCore/AxiVersion/BuildStamp"));
                ScalVal_RO gitHash     = IScalVal_RO::create (root->findByName("/mmio/AmcCarrierCore/AxiVersion/GitHash"));
                ScalVal_RO upTimeCnt   = IScalVal_RO::create (root->findByName("/mmio/AmcCarrierCore/AxiVersion/UpTimeCnt"));
                ScalVal_RO deviceId    = IScalVal_RO::create (root->findByName("/mmio/AmcCarrierCore/AxiVersion/DeviceId"));
                ScalVal_RO fdSerail    = IScalVal_RO::create (root->findByName("/mmio/AmcCarrierCore/AxiVersion/FdSerial"));

                printf("\n");
                printf("FW Version information:\n");
                printf("=======================\n");

                uint8_t  str[256];
                bldStamp->getVal( str, sizeof( str )/sizeof( str[0] ) );
                printf( "Build String : %s\n", (char*)str );

                uint8_t  hash[20];
                gitHash->getVal( hash, sizeof( hash )/sizeof( hash[0] ) );
                printf( "Git Hash     : 0x" );
                for ( int i = 0; i < 20; i++ )
                    printf( "%02X", hash[i] );
                printf( "\n" );

                uint32_t u32;
                upTimeCnt->getVal(&u32);
                printf( "UpTimerCnt   : %08" PRIu32 " s\n", u32 );

                fpgaVers->getVal(&u32);
                printf( "FpgaVersion  : 0x%08" PRIx32 "\n", u32 );

                deviceId->getVal(&u32);
                printf( "DeviceId     : 0x%08" PRIx32 "\n", u32 );

                uint64_t u64;
                fdSerail->getVal(&u64);
                printf( "FdSerial     : 0x%016" PRIx64 "\n", u64 );

            }
            catch (CPSWError &e)
            {
                fprintf( stderr, "CPSW Error: %s\n", e.getInfo().c_str() );
            }
        }
    }


    return 0;
}
