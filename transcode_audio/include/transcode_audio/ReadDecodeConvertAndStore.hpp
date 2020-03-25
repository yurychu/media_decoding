#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/audio_fifo.h>
#include <libswresample/swresample.h>
EXTERN_C_END


namespace tr_au
{

    /**
     * Read one audio frame from the input file, decode, convert and store
     * it in the FIFO buffer.
     * @param      fifo                 Buffer used for temporary storage
     * @param      input_format_context Format context of the input file
     * @param      input_codec_context  Codec context of the input file
     * @param      output_codec_context Codec context of the output file
     * @param      resampler_context    Resample context for the conversion
     * @param[out] finished             Indicates whether the end of file has
     *                                  been reached and all data has been
     *                                  decoded. If this flag is false,
     *                                  there is more data to be decoded,
     *                                  i.e., this function has to be called
     *                                  again.
     * @return Error code (0 if successful)
     */
    int read_decode_convert_and_store(AVAudioFifo *fifo,
                                      AVFormatContext *input_format_context,
                                      AVCodecContext *input_codec_context,
                                      AVCodecContext *output_codec_context,
                                      SwrContext *resampler_context,
                                      int *finished);

}
