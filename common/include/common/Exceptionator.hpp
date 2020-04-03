#pragma once

#include <string>

namespace common
{

    class Exceptionator
    {
    private:
        std::string m_msg;

    public:
        Exceptionator() = default;
        ~Exceptionator() = default;

        Exceptionator& operator<<(const std::string& word);
        Exceptionator& operator<<(int value;
        Exceptionator& operator<<(double value;

        void make_runtime_err();

    };

}
