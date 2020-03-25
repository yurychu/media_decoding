#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libswresample/swresample.h>
EXTERN_C_END


namespace tr_au
{


    /**
     * Convert the input audio samples into the output sample format.
     * The conversion happens on a per-frame basis, the size of which is
     * specified by frame_size.
     * @param      input_data       Samples to be decoded. The dimensions are
     *                              channel (for multi-channel audio), sample.
     * @param[out] converted_data   Converted samples. The dimensions are channel
     *                              (for multi-channel audio), sample.
     * @param      frame_size       Number of samples to be converted
     * @param      resample_context Resample context for the conversion
     * @return Error code (0 if successful)
     */
    int convert_samples(const uint8_t **input_data,
                        uint8_t **converted_data, const int frame_size,
                        SwrContext *resample_context);



}