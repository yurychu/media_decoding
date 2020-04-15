
#include <transcode_audio/ConvertSamples.hpp>

#include <transcode_audio/PatchAvErr2Str.hpp>


int tr_au::convert_samples(const uint8_t **input_data,
                           uint8_t **converted_data, const int frame_size,
                           SwrContext *resample_context)
{
    int error;

    /* Convert the samples using the resampler. */
    if ((error = swr_convert(resample_context,
                             converted_data, frame_size,
                             input_data    , frame_size)) < 0) {
        fprintf(stderr, "Could not convert input samples (error '%s')\n",
                av_err2str(error));
        return error;
    }

    return 0;
}
