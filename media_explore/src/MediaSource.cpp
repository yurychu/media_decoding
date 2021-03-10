

#include <MediaSource.hpp>

#include <sstream>
#include <iostream>
#include <stdexcept>

#include <printable_errors.hpp>


media_expl::MediaSource::MediaSource(std::string url)
        : m_url{std::move(url)},
          m_fmt_ctx{nullptr}
{
    int ret = 0;
    ret = avformat_open_input(&m_fmt_ctx, m_url.c_str(), nullptr, nullptr);
    if (ret < 0) {
        std::stringstream ss;
        ss << "Fail avformat_open_input: " << m_url << std::endl;
        ss << media_expl::to_string_av_err(ret);
        std::cerr << ss.str() << std::endl;
        throw std::runtime_error {ss.str()};
    }
}


media_expl::MediaSource::~MediaSource()
{
    avformat_close_input(&m_fmt_ctx);
}

/*
 * Add info about:
 * start_time,
 * duration,
 * bit_rate,
 * duration_estimation_method
 * for some input formats
 */
void media_expl::MediaSource::find_info()
{
    int ret = avformat_find_stream_info(m_fmt_ctx, nullptr);
    if (ret < 0) {
        std::stringstream ss;
        ss << "Fail find_info: " << m_url << std::endl;
        ss << media_expl::to_string_av_err(ret);
        std::cerr << ss.str() << std::endl;
        throw std::runtime_error {ss.str()};
    }
}

void media_expl::MediaSource::print_info_to_stdout()
{
    av_dump_format(m_fmt_ctx, 1, m_url.c_str(), 0);
}
