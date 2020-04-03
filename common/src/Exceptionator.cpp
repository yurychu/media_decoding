#include <common/Exceptionator.hpp>


namespace
{
    std::string get_end_delim(bool end)
    {
        return end ? "" : " ";
    }

}

void common::Exceptionator::make_runtime_err()
{
    throw std::runtime_error{m_msg};
}

common::Exceptionator &common::Exceptionator::operator<<(const std::string &word)
{
    m_msg += word;
    return *this;
}

common::Exceptionator &common::Exceptionator::operator<<(int value)
{
    m_msg += std::to_string(value);
    return *this;
}

common::Exceptionator &common::Exceptionator::operator<<(double value)
{
    m_msg += std::to_string(value);
    return *this;
}
