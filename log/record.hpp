#ifndef LOG_RECORD_HPP_
#define LOG_RECORD_HPP_

#include <cstdio>
#include <cwchar>
#include <string>
#include <type_traits>
#include <concepts>
#include <source_location>
#include <chrono>
#include <iostream>
#include <format>
#include <sstream>

namespace next {
namespace log {

// 日志等级
enum class Level {
  verbose = 0,
  info,
  debug,
  warn,
  error,
  fatel
};

// 记录器约束
template<typename _Logger>
concept LoggerType = requires {
  typename _Logger::_Char;
};

// 记录接收器约束
template<typename _Sink>
concept SinkType = requires {
  typename _Sink::_Char;
};

// 记录
template<LoggerType _Logger>
class Record {
public:
  using _Char = typename _Logger::_Char;
  using _String = std::basic_string<_Char>;
  using _SteadyTime = std::chrono::time_point<std::chrono::steady_clock>;
  using _SystemTime = std::chrono::time_point<std::chrono::system_clock>;

  Record(
      _Logger& logger, 
      Level level,
      const std::source_location location = std::source_location::current(),
      const _SteadyTime steadyTime = std::chrono::steady_clock::now(),
      const _SystemTime systemTime = std::chrono::system_clock::now()):
    _logger(logger), 
    _level(level),
    _steadyTime(steadyTime),
    _systemTime(systemTime),
    _location(location) {}

public:
  const _String& message() const { return _message; }
  const Level level() const { return _level; }
  const std::source_location& location() const { return _location; }
  const _SystemTime& systemTime() const { return _systemTime; }
  const _SteadyTime& steadyTime() const { return _steadyTime; }

protected:
  Level _level;
  std::source_location _location;
  _Logger& _logger;
  _String _message;
  _SystemTime _systemTime;
  _SteadyTime _steadyTime;
};

// 标准输出
class StdCoutSink {
public:
  using _Char = char;

public:
  void Log(std::string_view msg) {
    std::cout << msg << std::endl;
  }
};

class StdWcoutSink {
public:
  using _Char = wchar_t;

public:
  void Log(std::wstring_view msg) {
    std::wcout << msg << std::endl;
  }
};

inline StdCoutSink _stdCoutSink;
inline StdWcoutSink _stdWcoutSink;

// 记录器
template<SinkType _Sink, typename _Char = typename _Sink::_Char>
class Logger;

template<SinkType _Sink>
class Logger<_Sink, char> {
public:
  using _Char = char;

  Logger(_Sink& sink) : _sink(sink) {}

public:
  void Emit(Record<Logger>& record) {
    const auto endTime = std::chrono::steady_clock::now();
    std::string message = std::format(
        "[{} +{}][{}] {}", 
        std::format("{0:%F %T %z}", std::chrono::floor<std::chrono::milliseconds>(record.systemTime())),
        std::format("{}", std::chrono::floor<std::chrono::milliseconds>(record.steadyTime() -  _startTime)),
        GetLevel(record.level()), 
        record.message());
    _sink.Log(message);
    _startTime = endTime;
  }

protected:
  const char* GetLevel(const Level level) const {
    switch (level) {
    case Level::info:
      return "Info";
    case Level::debug:
      return "Debug";
    case Level::warn:
      return "Warn";
    case Level::error:
      return "Error";
    case Level::fatel:
      return "Fatel";
    default:
      return "Verbose";
    }
  }

protected:
  std::chrono::time_point<std::chrono::steady_clock> _startTime = 
      std::chrono::steady_clock::now();
  _Sink& _sink;
};

template<SinkType _Sink>
class Logger<_Sink, wchar_t> {
public:
  using _Char = wchar_t;

  Logger(_Sink& sink) : _sink(sink) {}

public:
  void Emit(Record<Logger>& record) {
    const auto endTime = std::chrono::steady_clock::now();
    std::wstring message = std::format(
        L"[{} +{}][{}] {}", 
        std::format(L"{0:%F %T %z}", std::chrono::floor<std::chrono::milliseconds>(record.systemTime())),
        std::format(L"{}", std::chrono::floor<std::chrono::milliseconds>(record.steadyTime() -  _startTime)),
        GetLevel(record.level()), 
        record.message());
    _sink.Log(message);
    _startTime = endTime;
  }

protected:
  const wchar_t* GetLevel(const Level level) const {
    switch (level) {
    case Level::info:
      return L"Info";
    case Level::debug:
      return L"Debug";
    case Level::warn:
      return L"Warn";
    case Level::error:
      return L"Error";
    case Level::fatel:
      return L"Fatel";
    default:
      return L"Verbose";
    }
  }

protected:
  std::chrono::time_point<std::chrono::steady_clock> _startTime = 
      std::chrono::steady_clock::now();
  _Sink& _sink;
};

using StdCoutLogger = Logger<StdCoutSink>;
inline StdCoutLogger _stdCoutLogger{_stdCoutSink};
using StdWcoutLogger = Logger<StdWcoutSink>;
inline StdWcoutLogger _stdWcoutLogger{_stdWcoutSink};

using DefaultLogger = StdCoutLogger;
inline DefaultLogger _defaultLogger{_stdCoutLogger};

// 销毁时自动提交
template<Level _level, LoggerType _Logger = DefaultLogger, _Logger& logger = _defaultLogger>
class ScopedRecord: 
  public Record<_Logger>,
  public std::basic_ostringstream<
      typename _Logger::_Char> {
public:
  using _Char = typename _Logger::_Char;
  using _Parent = Record<_Logger>;
  using _OStringStream = std::basic_ostringstream<
      typename _Logger::_Char>;

  ScopedRecord(
      _Logger& logger = logger,
      const std::source_location location = std::source_location::current()):
    _Parent(logger, _level, location) {

  }
  ~ScopedRecord() {
    Emit();
  }

public:
  void Emit() {
    _Parent::_message = _OStringStream::str();
    _Parent::_logger.Emit(*this);
  }
};


template<auto &tag_name>
using tag_t = std::decay_t<decltype(tag_name)>;

template<Level _level>
class Log {
public:
  template<LoggerType _Logger = Logger>
  Record<_Logger> operator()(
      _Logger& logger = logger, 
      const std::source_location location = std::source_location::current()) {
    return Record<_Logger>{logger, _level, location};
  }
};


using Info = ScopedRecord<Level::info, DefaultLogger>;

}
}

#endif
