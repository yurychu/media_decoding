#pragma once


#include <cstdint>

namespace common
{

    class ByteBuff
    {
    private:
        char * m_buf;
        size_t m_capacity;
        size_t m_count;

    public:
        ByteBuff();
        explicit ByteBuff(size_t capacity);
        ~ByteBuff();

        size_t capacity() const;
        char* begin();

        void set_count(size_t num_bytes);
        size_t get_count() const;

        bool has(size_t pos) const;
        uint8_t get_byte(size_t pos) const;


    };


}
