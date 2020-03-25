#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavutil/frame.h>
EXTERN_C_END


namespace tr_au
{


    /**
     * Initialize one audio frame for reading from the input file.
     * @param[out] frame Frame to be initialized
     * @return Error code (0 if successful)
     */
    int init_input_frame(AVFrame **frame);


}
