#include <common/ByteBuff.hpp>

#include <common/Exceptionator.hpp>


namespace {
    const size_t MAX_BUF_SZ = 1024;
}


common::ByteBuff::ByteBuff()
    : m_buf{nullptr},
    m_capacity{MAX_BUF_SZ},
    m_count{0}
{
    m_buf = new char [m_capacity];
}


common::ByteBuff::ByteBuff(size_t capacity)
    : m_buf{nullptr},
    m_capacity{capacity},
    m_count{0}
{
    m_buf = new char [m_capacity];
}


common::ByteBuff::~ByteBuff()
{
    delete [] m_buf;
}


size_t common::ByteBuff::capacity() const
{
    return m_capacity;
}

char* common::ByteBuff::begin()
{
    return m_buf;
}

void common::ByteBuff::set_count(size_t num_bytes)
{
    m_count = num_bytes;
}


uint8_t common::ByteBuff::get_byte(size_t pos) const
{
    if (pos >= get_count()){
        common::Exceptionator ex {};
        ex << "Pos in greater than count payload data.";
        ex.make_runtime_err();
    }
    auto res = m_buf + pos;
    return *res;
}


size_t common::ByteBuff::get_count() const
{
    return m_count;
}

bool common::ByteBuff::has(size_t pos) const
{
    return pos < get_count();
}
