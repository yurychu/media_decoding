#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavcodec/avcodec.h>
EXTERN_C_END


namespace tr_au
{

    /**
     * Initialize a temporary storage for the specified number of audio samples.
     * The conversion requires temporary storage due to the different format.
     * The number of audio samples to be allocated is specified in frame_size.
     * @param[out] converted_input_samples Array of converted samples. The
     *                                     dimensions are reference, channel
     *                                     (for multi-channel audio), sample.
     * @param      output_codec_context    Codec context of the output file
     * @param      frame_size              Number of samples to be converted in
     *                                     each round
     * @return Error code (0 if successful)
     */
    int init_converted_samples(uint8_t ***converted_input_samples,
                               AVCodecContext *output_codec_context,
                               int frame_size);


}