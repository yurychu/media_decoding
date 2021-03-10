

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
        std::cerr << ss.str();
        throw std::runtime_error {ss.str()};
    }
}


media_expl::MediaSource::~MediaSource()
{
    avformat_close_input(&m_fmt_ctx);
}
