
#include <MediaSource.hpp>


int main(int argc, char * argv[])
{
    media_expl::MediaSource media_source {"E:\\Work\\VideoFiles\\TP708308.mxf"};
    media_source.find_info();
    media_source.print_info_to_stdout();
    return 0;
}