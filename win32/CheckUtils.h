#ifndef WIN32_CHECK_UTILS_H_
#define WIN32_CHECK_UTILS_H_

#include <stdexcept>
#include <string>
#include <source_location>

namespace next {
namespace win32 {

class ApiError: public std::runtime_error {
public:
  using _Base = std::runtime_error;
  explicit ApiError(const std::string& msg) : _Base(msg.c_str()) {}
  explicit ApiError(const char* msg) : _Base(msg) {}
};

inline bool _ApiCheck(
    bool expr, 
    const char* apiName, 
    const std::source_location location = std::source_location::current()) {
  return expr;
}

inline bool _Check(
    bool expr,
    const std::source_location location = std::source_location::current()) {
  return expr;
}

}
}

#endif
