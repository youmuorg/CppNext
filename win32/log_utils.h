#ifndef WIN32_LOG_UTILS_H_
#define WIN32_LOG_UTILS_H_

#include "log/record.hpp"
#include "win32/debug_utils.h"

#include <tuple>
#include <string>
#include <source_location>

namespace next {
namespace win32 {

class DebuggerSink {
public:
  using _Char = wchar_t;

public:
  void Log(std::wstring_view msg) {
    ::OutputDebugStringW(std::wstring(msg).append(L"\r\n\0").data());
  }
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

}
}

#endif
