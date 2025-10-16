#ifndef MOCKOC_HPP
#define MOCKOC_HPP

#include <chrono>
#include <sstream>
#include <string>
#include <vector>

struct FunctionCall
{
    std::string fn_name;
    std::vector<std::string> args;
    std::string return_value;
    uint64_t timestamp_start;
    uint64_t timestamp_end;

    FunctionCall(const std::string &name,
                 const std::vector<std::string> &arguments,
                 const std::string &ret_val, const uint64_t timestamp_start,
                 const uint64_t timestamp_end)
        : fn_name(name), args(arguments), return_value(ret_val),
          timestamp_start(timestamp_start), timestamp_end(timestamp_end)
    {
    }

    uint64_t runtime() const
    {
        return timestamp_end - timestamp_start;
    }
};

using FunctionCalls = std::vector<FunctionCall>;

class MockoC
{
private:
    FunctionCalls _function_calls;
    void _sort();

public:
    // Registration
    void register_function_call(const FunctionCall call);

    // Data managements
    void clear();

    // Data retrieval
    const FunctionCall &last_function_call() const;
    const FunctionCalls &function_calls() const;
    const FunctionCalls calls_for_function(const std::string fn_name) const;
    const bool was_called(const std::string fn_name) const;
    const FunctionCall &last_call_for_function(const std::string fn_name) const;
};

extern MockoC mockoc;

template <typename Fn, typename... Args>
auto mock_call(const std::string &name, Fn &&fn, Args &&...args)
{
    uint64_t start =
        std::chrono::steady_clock::now().time_since_epoch().count();

    // Run the function and save the return value
    auto temp = fn(std::forward<Args>(args)...);
    uint64_t end = std::chrono::steady_clock::now().time_since_epoch().count();
    std::ostringstream retval;
    retval << temp;

    // Create a vector with the given arguments
    std::vector<std::string> arg_list;
    (arg_list.push_back((std::ostringstream{} << args).str()), ...);

    // Create the `FunctionCall` object
    FunctionCall fc{name, arg_list, retval.str(), start, end};

    // Register the call
    mockoc.register_function_call(fc);

    // Return the value
    return temp;
}

#endif // MOCKOC_HPP