#pragma once
#include <string>
#include <stdexcept>
#include <memory>

template <typename... Args>
std::string string_format(const std::string& format, Args... args)
{
    int size_s =
        std::snprintf(nullptr, 0, format.c_str(), args...) + 1;  // Extra space for '\0'
    if(size_s <= 0)
    {
        throw std::runtime_error("Error during formatting.");
    }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return {buf.get(), buf.get() + size - 1};  // We don't want the '\0' inside
}

template <typename T>
std::string to_string(const T& t)
{
    std::string str{std::to_string(t)};
    int offset{1};
    if(str.find_last_not_of('0') == str.find('.'))
    {
        offset = 0;
    }
    str.erase(str.find_last_not_of('0') + offset, std::string::npos);
    return str;
}