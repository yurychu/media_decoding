#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavutil/frame.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
EXTERN_C_END


namespace tr_au
{

    class AudioFrameEncoder
    {
    private:
        /* Global timestamp for the audio frames. */
        int64_t m_pts;

    public:
        AudioFrameEncoder();
        ~AudioFrameEncoder() = default;

        /**
         * Encode one frame worth of audio to the output file.
         * @param      frame                 Samples to be encoded
         * @param      output_format_context Format context of the output file
         * @param      output_codec_context  Codec context of the output file
         * @param[out] data_present          Indicates whether data has been
         *                                   encoded
         * @return Error code (0 if successful)
         */
        int encode_audio_frame(AVFrame *frame,
                               AVFormatContext *output_format_context,
                               AVCodecContext *output_codec_context,
                               int *data_present);

    };

}
