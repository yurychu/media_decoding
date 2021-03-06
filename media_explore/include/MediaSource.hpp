#pragma once

#include <string>

extern "C" {
    #include <libavutil/avutil.h>
    #include <libavformat/avformat.h>
}

namespace media_expl
{

    class MediaSource
    {
    private:
        std::string m_url;
        AVFormatContext *m_fmt_ctx;

    public:
        explicit MediaSource(std::string file_name);
        ~MediaSource();

        void find_format_info();
        void print_format_info_to_stdout();

    };

}
