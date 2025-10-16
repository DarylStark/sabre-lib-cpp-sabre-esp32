#include "mockoc.hpp"
#include <algorithm>

void MockoC::_sort()
{
    std::sort(
        _function_calls.begin(), _function_calls.end(),
        [](const FunctionCall &x, const FunctionCall &y)
        { return x.timestamp_start < y.timestamp_start; });
}

void MockoC::register_function_call(const FunctionCall call)
{
    _function_calls.push_back(call);
    _sort();
}

void MockoC::clear()
{
    _function_calls.clear();
}

const FunctionCall &MockoC::last_function_call() const
{
    if (_function_calls.size() > 0)
        return _function_calls.back();
    throw std::string("ERROR"); // TODO: Better exception
}

const FunctionCalls &MockoC::function_calls() const
{
    return _function_calls;
}

const FunctionCalls MockoC::calls_for_function(const std::string fn_name) const
{
    FunctionCalls _temp;
    std::copy_if(_function_calls.begin(), _function_calls.end(),
                 std::back_inserter(_temp),
                 [&fn_name](FunctionCall c) { return c.fn_name == fn_name; });
    return _temp;
}

const bool MockoC::was_called(const std::string fn_name) const
{
    const auto _find = std::find_if(
        _function_calls.begin(), _function_calls.end(),
        [&fn_name](const FunctionCall &fc) { return fc.fn_name == fn_name; });
    return _find != _function_calls.end();
}

const FunctionCall &
MockoC::last_call_for_function(const std::string fn_name) const
{
    const auto _find = std::find_if(
        _function_calls.rbegin(), _function_calls.rend(),
        [&fn_name](const FunctionCall &fc) { return fc.fn_name == fn_name; });
    if (_find == _function_calls.rend())
        throw std::string("ERROR"); // TODO: Better exception
    return *_find;
}

MockoC mockoc;