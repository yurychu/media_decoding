

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

namespace
{
    void inline step_iterate_over_all_dict_entries(
            const AVDictionary *m,
            AVDictionaryEntry* &prev)
    {
        prev = av_dict_get(m, "", prev, AV_DICT_IGNORE_SUFFIX);
    }
}

void media_expl::MediaSource::print_format_info_to_stdout()
{
    std::cout << "Custom info." << std::endl;

    AVDictionaryEntry * tag = nullptr;
    step_iterate_over_all_dict_entries(m_fmt_ctx->metadata, tag);
    while (tag) {
        std::cout << "Key: " << tag->key << std::endl;
        std::cout << "Value: " << tag->value << std::endl;

        step_iterate_over_all_dict_entries(m_fmt_ctx->metadata, tag);
    }

    const int64_t duration = m_fmt_ctx->duration;
    int64_t secs = duration / AV_TIME_BASE;
    int64_t units = duration % AV_TIME_BASE;
    int64_t mins = secs / 60;
    secs %= 60;
    int64_t hours = mins / 60;
    mins %= 60;
    std::cout << "Raw duration: " << duration << ". "
        << "Duration repr: "
        << "hours: " << hours << ", "
        << "mins: " << mins << ", "
        << "secs: " << secs << ", "
        << "units: " << units << " of " << AV_TIME_BASE << std::endl;

    std::cout << "End custom info." << std::endl;

    // built-in functions
    av_dump_format(m_fmt_ctx, 1, m_url.c_str(), 0);
}
