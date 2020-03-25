#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavutil/audio_fifo.h>
#include <libavcodec/avcodec.h>
EXTERN_C_END



namespace tr_au
{
    /**
     * Initialize a FIFO buffer for the audio samples to be encoded.
     * @param[out] fifo                 Sample buffer
     * @param      output_codec_context Codec context of the output file
     * @return Error code (0 if successful)
     */
     int init_fifo(AVAudioFifo **fifo, AVCodecContext *output_codec_context);


}