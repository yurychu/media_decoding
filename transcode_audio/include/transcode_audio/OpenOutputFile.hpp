#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
EXTERN_C_END


namespace tr_au
{

    /**
     * Open an output file and the required encoder.
     * Also set some basic encoder parameters.
     * Some of these parameters are based on the input file's parameters.
     * @param      filename              File to be opened
     * @param      input_codec_context   Codec context of input file
     * @param[out] output_format_context Format context of output file
     * @param[out] output_codec_context  Codec context of output file
     * @return Error code (0 if successful)
     */
    int open_output_file(
            const char *filename,
            AVCodecContext *input_codec_context,
            AVFormatContext **output_format_context,
            AVCodecContext **output_codec_context
    );


}
