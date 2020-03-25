#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>
EXTERN_C_END


namespace tr_au
{

    /**
     * Initialize one input frame for writing to the output file.
     * The frame will be exactly frame_size samples large.
     * @param[out] frame                Frame to be initialized
     * @param      output_codec_context Codec context of the output file
     * @param      frame_size           Size of the frame
     * @return Error code (0 if successful)
     */
    int init_output_frame(AVFrame **frame,
                          AVCodecContext *output_codec_context,
                          int frame_size);

}
