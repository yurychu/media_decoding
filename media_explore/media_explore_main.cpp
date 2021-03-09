
#include <MediaExplorer.hpp>


int main(int argc, char * argv[])
{
    MediaObject media_object {"E:\\Work\\VideoFiles\\TP708308.mxf"};
    media_object.start_read_packets();

    return 0;
}