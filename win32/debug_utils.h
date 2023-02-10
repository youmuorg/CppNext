#ifndef WIN32_DEBUG_UTILS_H_
#define WIN32_DEBUG_UTILS_H_

#include <windows.h>

namespace next {
namespace win32 {

inline void _LogToDebugger(const wchar_t* message) {
  ::OutputDebugStringW(message);
}

}
}

#endif
