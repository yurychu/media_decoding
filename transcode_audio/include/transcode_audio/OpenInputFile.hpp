#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
EXTERN_C_END


namespace tr_au
{

    /**
     * Open an input file and the required decoder.
     * @param      filename             File to be opened
     * @param[out] input_format_context Format context of opened file
     * @param[out] input_codec_context  Codec context of opened file
     * @return Error code (0 if successful)
     */
    int open_input_file(
            const char *filename,
            AVFormatContext **input_format_context,
            AVCodecContext **input_codec_context
    );

}
