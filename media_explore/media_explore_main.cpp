
#include <MediaSource.hpp>


int main(int argc, char * argv[])
{
    media_expl::MediaSource media_source {"E:\\Videos\\Renders\\clip_3.mp4"};
    media_source.find_info();
    media_source.print_format_info_to_stdout();
    return 0;
}