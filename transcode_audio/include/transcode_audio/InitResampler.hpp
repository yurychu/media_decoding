#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
EXTERN_C_END


namespace tr_au
{

    /**
     * Initialize the audio resampler based on the input and output codec settings.
     * If the input and output sample formats differ, a conversion is required
     * libswresample takes care of this, but requires initialization.
     * @param      input_codec_context  Codec context of the input file
     * @param      output_codec_context Codec context of the output file
     * @param[out] resample_context     Resample context for the required conversion
     * @return Error code (0 if successful)
     */
    int init_resampler(AVCodecContext *input_codec_context,
                       AVCodecContext *output_codec_context,
                       SwrContext **resample_context);

}
