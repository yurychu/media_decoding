#pragma once

#include <string>

extern "C" {
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

    };

}