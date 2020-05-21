
#pragma once

#include <string>


namespace chu
{

    enum class TestingState
    {
        INIT,
        SUCCESS,
        FAIL
    };


    class ContinuityResult
    {
    private:
        chu::TestingState _state;
        std::string _msg;
        size_t _updatesCounter;

    public:
        ContinuityResult();
        ~ContinuityResult() = default;

        void setFail(const std::string& msg);
        void setSuccess(const std::string& msg);

        std::string str() const;

        void update();

        bool isUpdated() const;
        bool isSuccess() const;

    };

}
