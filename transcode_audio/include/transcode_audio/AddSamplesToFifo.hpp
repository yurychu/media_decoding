#pragma once


#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavutil/audio_fifo.h>
EXTERN_C_END


namespace tr_au
{

    /**
     * Add converted input audio samples to the FIFO buffer for later processing.
     * @param fifo                    Buffer to add the samples to
     * @param converted_input_samples Samples to be added. The dimensions are channel
     *                                (for multi-channel audio), sample.
     * @param frame_size              Number of samples to be converted
     * @return Error code (0 if successful)
     */
    int add_samples_to_fifo(
            AVAudioFifo *fifo,
            uint8_t **converted_input_samples,
            int frame_size
    );

}
