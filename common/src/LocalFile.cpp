#include <common/LocalFile.hpp>

#include <iostream>

#include <common/Exceptionator.hpp>


common::Exceptionator& operator<<(common::Exceptionator& ex, common::FileMode mode)
{
    switch (mode){
        case common::FileMode::Read : {
            ex << "read";
        } break;
        case common::FileMode::Write : {
            ex << "write";
        } break;
        default: {
            ex << "default";
        }
    }
    return ex;
}


common::LocalFile::LocalFile(std::string file_name, FileMode mode)
    : m_mode{mode},
    m_file_name{std::move(file_name)},
    m_file{}
{
    std::ios_base::openmode open_mode = std::ios_base::binary;
    switch (m_mode){
        case FileMode::Read : {
            open_mode |= std::ios_base::in;
        } break;
        case FileMode::Write : {
            open_mode |= std::ios_base::out;
            open_mode |= std::ios_base::trunc;
        } break;
        default: {
            open_mode |= std::ios_base::in;
            open_mode |= std::ios_base::out;
        }
    }
    m_file.open(m_file_name, open_mode);
    if (!m_file.is_open()){
        common::Exceptionator ex {};
        ex << "Fail open file: " << m_file_name << ", in mode: " << m_mode;
        ex.make_runtime_err();
    }
}


common::LocalFile::~LocalFile()
{

}


const std::string &common::LocalFile::name() const
{
    return m_file_name;
}
