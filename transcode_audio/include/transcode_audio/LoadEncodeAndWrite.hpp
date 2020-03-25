#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavutil/audio_fifo.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
EXTERN_C_END


#include <transcode_audio/AudioFrameEncoder.hpp>


namespace tr_au
{

    /**
     * Load one audio frame from the FIFO buffer, encode and write it to the
     * output file.
     * @param fifo                  Buffer used for temporary storage
     * @param output_format_context Format context of the output file
     * @param output_codec_context  Codec context of the output file
     * @return Error code (0 if successful)
     */
    int load_encode_and_write(
            tr_au::AudioFrameEncoder& encoder,
            AVAudioFifo *fifo,
            AVFormatContext *output_format_context,
            AVCodecContext *output_codec_context
    );

}
