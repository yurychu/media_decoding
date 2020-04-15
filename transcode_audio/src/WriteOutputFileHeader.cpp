
#include <transcode_audio/WriteOutputFileHeader.hpp>

#include <transcode_audio/PatchAvErr2Str.hpp>


int tr_au::write_output_file_header(AVFormatContext *output_format_context)
{
    int error;
    if ((error = avformat_write_header(output_format_context, NULL)) < 0) {
        fprintf(stderr, "Could not write output file header (error '%s')\n",
                av_err2str(error));
        return error;
    }
    return 0;
}
