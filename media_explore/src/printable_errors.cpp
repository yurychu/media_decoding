//
// Created by yurychu on 10.03.2021.
//

#include <printable_errors.hpp>

extern "C" {
    #include <libavutil/avutil.h>
}


std::string media_expl::to_string_av_err(int errnum)
{
    char err_str[AV_ERROR_MAX_STRING_SIZE];
    int ret = av_strerror(errnum, err_str, AV_ERROR_MAX_STRING_SIZE);
    if (ret != 0){
        return std::string{"Error to_string_av_err, av_strerror return fail!"};
    }
    return std::string{err_str};
}
