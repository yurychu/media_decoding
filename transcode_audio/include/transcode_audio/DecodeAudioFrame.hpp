#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavutil/frame.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
EXTERN_C_END


namespace tr_au
{

    /**
     * Decode one audio frame from the input file.
     * @param      frame                Audio frame to be decoded
     * @param      input_format_context Format context of the input file
     * @param      input_codec_context  Codec context of the input file
     * @param[out] data_present         Indicates whether data has been decoded
     * @param[out] finished             Indicates whether the end of file has
     *                                  been reached and all data has been
     *                                  decoded. If this flag is false, there
     *                                  is more data to be decoded, i.e., this
     *                                  function has to be called again.
     * @return Error code (0 if successful)
     */
    int decode_audio_frame(AVFrame *frame,
                           AVFormatContext *input_format_context,
                           AVCodecContext *input_codec_context,
                           int *data_present, int *finished);


}