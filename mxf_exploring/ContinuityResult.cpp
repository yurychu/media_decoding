
#include <mxf_exploring/ContinuityResult.hpp>


chu::ContinuityResult::ContinuityResult()
    : _state(chu::TestingState::INIT),
      _msg("Unchecked TimeCodes"),
      _updatesCounter(0)
{

}

void chu::ContinuityResult::setFail(const std::string &msg)
{
    _state = chu::TestingState::FAIL;
    _msg = msg;
}

void chu::ContinuityResult::setSuccess(const std::string &msg)
{
    _state = chu::TestingState::SUCCESS;
    _msg = msg;
}

std::string chu::ContinuityResult::str() const
{
    if (_state == chu::TestingState::INIT){
        return "TimeCodes not tested!";
    }
    else if (_state == chu::TestingState::FAIL){
        return "Continuity fail, msg: " + _msg;
    }
    else {
        return "No fails, updates count: " + std::to_string(_updatesCounter);
    }
}

void chu::ContinuityResult::update()
{
    _updatesCounter++;
    if (_state == chu::TestingState::INIT){
        setSuccess("Continuity error not found");
    }
}

bool chu::ContinuityResult::isSuccess() const
{
    return _state == chu::TestingState::SUCCESS;
}

bool chu::ContinuityResult::isUpdated() const
{
    return _updatesCounter != 0;
}
