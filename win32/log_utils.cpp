#include "win32/log_utils.h"

#include <windows.h>

namespace next {
namespace win32 {

void DebuggerSink::Log(std::wstring_view msg) {
  ::OutputDebugStringW(std::wstring(msg).append(L"\r\n\0").data());
}

}
}