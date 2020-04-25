#pragma once

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/avutil.h>
    #include <libavutil/pixdesc.h>
    #include <libavfilter/avfilter.h>
}

#include <string>
#include <map>
#include <vector>


class StreamDecoder
{
private:
    AVCodecContext* m_decoder_ctx;

    std::vector<int> m_temp_frames;

public:
    static void print_frame_info(const AVFrame* a_v_frame);

public:
    StreamDecoder(const AVCodecParameters* codec_params);
    ~StreamDecoder();

    void print_info() const;
    bool is_video_stream() const;
    void handle_packet(const AVPacket* packet);
    void receive_frames();
    void handle_frame(const AVFrame* frame);

};


class PacketExplorer
{
private:
    std::map<int, StreamDecoder*> m_stream_decoders;

public:
    static void print_packet_info(const AVPacket* packet);

public:
    PacketExplorer(const AVFormatContext* fmt_ctx);
    ~PacketExplorer();

    void print_state() const;
    void print_info_video_frames() const;

    void explore(const AVPacket* packet);

};


class MediaObject
{
private:
    std::string m_file_name;
    AVFormatContext* m_fmt_ctx;

public:
    MediaObject(std::string file_name);
    ~MediaObject();

    void print_info();

    void start_read_packets();

};
