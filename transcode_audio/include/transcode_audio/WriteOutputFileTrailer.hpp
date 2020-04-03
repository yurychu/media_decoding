#pragma once

#include <common/macro_c_extern.hpp>

EXTERN_C_BEGIN
#include <libavformat/avformat.h>
EXTERN_C_END


namespace tr_au
{

    /**
     * Write the trailer of the output file container.
     * @param output_format_context Format context of the output file
     * @return Error code (0 if successful)
     */
    int write_output_file_trailer(AVFormatContext *output_format_context);

}
