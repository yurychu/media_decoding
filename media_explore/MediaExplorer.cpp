
#include "MediaExplorer.hpp"


#include <iostream>

static void print_av_err_str(int errnum)
{
    char err_str[AV_ERROR_MAX_STRING_SIZE];
    av_make_error_string(err_str, AV_ERROR_MAX_STRING_SIZE, errnum);
    std::cerr << err_str << std::endl;
}

void StreamDecoder::print_frame_info(const AVFrame* a_v_frame)
{
    std::cout << "frame pts: " << a_v_frame->pts << std::endl;

    for (int i = 0; i < a_v_frame->nb_side_data; ++i) {
        std::cout << "have side data: " << av_frame_side_data_name(a_v_frame->side_data[i]->type) << std::endl;
        if (a_v_frame->side_data[i]->type == AV_FRAME_DATA_GOP_TIMECODE) {
            std::cout << "gop_timecode size: " << a_v_frame->side_data[i]->size << std::endl;
            std::cout << "gop_timecode data ptr: " << a_v_frame->side_data[i]->data << std::endl;
            std::cout << "gop_timecode data value: " << *(int64_t*)a_v_frame->side_data[i]->data << std::endl;
        }
        //char* str_res = nullptr;
        //av_dict_get_string(a_v_frame->side_data[i]->metadata, &str_res, '@', '!');
        //if (str_res) {
        //	std::cout << "metadata print: " << str_res << std::endl;
        //}
    }
}

StreamDecoder::StreamDecoder(const AVCodecParameters* codec_params)
        : m_decoder_ctx(nullptr)
{
    if ( ! codec_params) {
        throw std::runtime_error("Invalid parameter: codec_params");
    }

    AVCodec* decoder = avcodec_find_decoder(codec_params->codec_id);
    if ( ! decoder) {
        throw std::runtime_error("Fail find decoder for codec id: " + std::to_string(codec_params->codec_id));
    }
    m_decoder_ctx = avcodec_alloc_context3(decoder);
    if ( ! m_decoder_ctx) {
        throw std::runtime_error("Fail alloc context for: " + std::string(decoder->long_name));
    }
    int ret = avcodec_parameters_to_context(m_decoder_ctx, codec_params);
    if (ret < 0) {
        print_av_err_str(ret);
        throw std::runtime_error("Fail codec parameters to ctx");
    }

    ret = avcodec_open2(m_decoder_ctx, decoder, nullptr);
    if (ret < 0) {
        print_av_err_str(ret);
        throw std::runtime_error("Fail open context with codec: " + std::string(decoder->long_name));
    }
}

StreamDecoder::~StreamDecoder()
{
    avcodec_free_context(&m_decoder_ctx);

    for (auto& item : m_temp_frames) {
        av_frame_free(&item);
    }
    std::cout << "end" << std::endl;
}

void StreamDecoder::print_info() const
{
    std::cout << "--- Info for stream type: " << av_get_media_type_string(m_decoder_ctx->codec_type) << std::endl;
    std::cout << "--- Frames info: " << std::endl;
    for (const auto& elem : m_temp_frames) {
        StreamDecoder::print_frame_info(elem);
    }

}

bool StreamDecoder::is_video_stream() const
{
    return m_decoder_ctx->codec_type == AVMEDIA_TYPE_VIDEO;
}

void StreamDecoder::handle_packet(const AVPacket* packet)
{
    int ret = avcodec_send_packet(m_decoder_ctx, packet);
    if (ret < 0) {
        std::cerr << "Fail send packet!" << std::endl;
        print_av_err_str(ret);
        throw ret;
    }

    receive_frames();
}

void StreamDecoder::receive_frames()
{
    AVFrame* frame = av_frame_alloc();
    if ( ! frame) {
        std::cerr << "Fail allocate frame" << std::endl;
        throw 1;
    }

    int ret = 0;
    while (ret >= 0) {
        ret = avcodec_receive_frame(m_decoder_ctx, frame);
        if (ret == 0) {
            //std::cout << "Success receive frame" << std::endl;
            handle_frame(frame);
        }
        else if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            //std::cerr << "EAGAIN or EOF in receive frames" << std::endl;
            //print_av_err_str(ret);
            break;
        }
        else {
            std::cerr << "Error while receiving a frame from the decoder" << std::endl;
            print_av_err_str(ret);
            throw ret;
        }
    }

    av_frame_free(&frame);
}

void StreamDecoder::handle_frame(const AVFrame* frame)
{
    AVFrame* tmp_frame = av_frame_clone(frame);
    if (!tmp_frame) {
        std::cerr << "Fail clone frame" << std::endl;
        throw 1;
    }

    m_temp_frames.push_back(tmp_frame);
}


void PacketExplorer::print_packet_info(const AVPacket* packet)
{
    std::cout << "Explore packet info: " << std::endl;
//    std::cout << ".Print side data:" << std::endl;
//    std::cout << "side data elems: " << packet->side_data_elems << std::endl;
//    for (int i = 0; i < packet->side_data_elems; ++i) {
//        std::cout << av_packet_side_data_name(packet->side_data[i].type) << std::endl;
//    }
}

PacketExplorer::PacketExplorer(const AVFormatContext* fmt_ctx)
{
    for (int i = 0; i < fmt_ctx->nb_streams; ++i) {
        AVStream* stream = fmt_ctx->streams[i];
        m_stream_decoders[i] = new StreamDecoder { stream->codecpar };
    }
}

PacketExplorer::~PacketExplorer()
{
    for (const auto& item : m_stream_decoders) {
        delete item.second;
    }
}

void PacketExplorer::print_state() const
{
    std::cout << "--- Print decoders bunch:" << std::endl;
    for (const auto& item : m_stream_decoders) {
        item.second->print_info();
    }

}

void PacketExplorer::print_info_video_frames() const
{
    for (const auto& elem : m_stream_decoders) {
        if (elem.second->is_video_stream()) {
            elem.second->print_info();
        }
    }
}


void PacketExplorer::explore(const AVPacket* packet)
{
    PacketExplorer::print_packet_info(packet);

    auto decoder = m_stream_decoders[packet->stream_index];
    if (decoder) {
        decoder->handle_packet(packet);
    }
    else {
        std::cerr << "Not find decoder for packet with stream_index: " << packet->stream_index << std::endl;
    }
}


MediaObject::MediaObject(std::string file_name)
        : m_file_name(std::move(file_name)),
          m_fmt_ctx(nullptr)
{
    int ret = 0;
    ret = avformat_open_input(&m_fmt_ctx, m_file_name.c_str(), nullptr, nullptr);
    if (ret < 0) {
        std::cerr << "Fail open input: " << m_file_name << std::endl;
        print_av_err_str(ret);
        throw ret;
    }

    ret = avformat_find_stream_info(m_fmt_ctx, nullptr);
    if (ret < 0) {
        std::cerr << "Fail find media object info: " << m_file_name << std::endl;
        print_av_err_str(ret);
        throw ret;
    }
}

MediaObject::~MediaObject()
{
    std::cout << "dtor media obj" << std::endl;
}

void MediaObject::print_info()
{
    av_dump_format(m_fmt_ctx, 1, m_file_name.c_str(), 0);
}

void MediaObject::start_read_packets()
{
    bool running = true;

    AVPacket* packet = av_packet_alloc();
    if ( ! packet) {
        throw std::runtime_error("Fail packet alloc!");
    }

    PacketExplorer explorer { m_fmt_ctx };
    explorer.print_state();

    while (running) {
        int ret = av_read_frame(m_fmt_ctx, packet);
        if (ret < 0) {
            std::cout << "Break reading packets frames." << std::endl;
            print_av_err_str(ret);
            running = false;
        }

        explorer.explore(packet);

        av_packet_unref(packet);
    }

    //explorer.print_info_video_frames();
    explorer.print_state();

    av_packet_free(&packet);

    std::cout << "unreffed pkt" << std::endl;
}
