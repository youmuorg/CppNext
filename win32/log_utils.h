#ifndef WIN32_LOG_UTILS_H_
#define WIN32_LOG_UTILS_H_

#include "log/record.hpp"

#include <tuple>
#include <string>
#include <source_location>

namespace next {
namespace win32 {

class DebuggerSink {
public:
  using _Char = wchar_t;

public:
  void Log(std::wstring_view msg);
};

inline DebuggerSink _debuggerSink{};
using DebuggerLogger = log::Logger<DebuggerSink>;
inline DebuggerLogger _debuggerLogger{_debuggerSink};

// template<log::Level _level>
// using _Log = log::ScopedRecord<_level, DebuggerLogger, _debuggerLogger>;

template<log::Level _level>
using _Log = log::ScopedRecord<_level, log::StdWcoutLogger, log::_stdWcoutLogger>;

using _LogVerbose = _Log<log::Level::verbose>;
using _LogInfo = _Log<log::Level::info>;
using _LogDebug = _Log<log::Level::debug>;
using _LogWarn = _Log<log::Level::warn>;
using _LogError = _Log<log::Level::error>;
using _LogFatel = _Log<log::Level::fatel>;

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
  if (!expr) {
    
  }
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
