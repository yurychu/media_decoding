
#include <iostream>

#include <MediaSource.hpp>

#include <SequenceOfValuesChecker.hpp>


int main(int argc, char * argv[])
{
//    media_expl::MediaSource media_source {"E:\\Videos\\Renders\\clip_3.mp4"};
//    media_source.find_format_info();
//    media_source.print_format_info_to_stdout();

    SequenceOfValuesChecker<AVPictureType> checker;
    checker.addRule(AV_PICTURE_TYPE_I, DurationRule{});
    const auto rep = checker.check(AV_PICTURE_TYPE_BI);
    if (!rep.empty()){
        std::cout << rep.str() << std::endl;
    }

    return 0;
}
