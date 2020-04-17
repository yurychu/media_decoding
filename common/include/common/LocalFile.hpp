#pragma once

#include <string>
#include <fstream>

#include <common/ByteBuff.hpp>


namespace common
{

    enum class FileMode
    {
        Read,
        Write
    };


    class LocalFile
    {
    private:
        FileMode m_mode;
        std::string m_file_name;
        std::fstream m_file;

    public:
        explicit LocalFile(std::string file_name, FileMode mode = FileMode::Read);
        ~LocalFile();

        const std::string& name() const;

        void read_bytes(common::ByteBuff & buff);

        size_t size();
    };


}
