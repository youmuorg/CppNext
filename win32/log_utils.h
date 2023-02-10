#ifndef WIN32_LOG_UTILS_H_
#define WIN32_LOG_UTILS_H_

#include "win32/debug_utils.h"

#include <tuple>
#include <source_location>

namespace next {
namespace win32 {

enum class LogLevel {
  verbose,
  info,
  debug,
  warn,
  error,
  fatel
};

template<typename ...Args>
inline void _Log(LogLevel level, const wchar_t* message, std::tuple<Args...> args, const std::source_location location = std::source_location::current()) {
  _LogToDebugger(message);
}

}
}

#endif
