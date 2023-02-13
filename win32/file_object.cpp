#include "win32/file_object.h"
#include "win32/log_utils.h"

#include <windows.h>

namespace next {
namespace win32 {

void FileObject::Create(std::wstring_view filePath, io::Mode mode) {
  handle_ = ::CreateFileW(
      std::wstring(filePath).c_str(),
      GENERIC_READ | GENERIC_WRITE,
      0, // 不共享
      NULL,
      OPEN_ALWAYS,
      FILE_ATTRIBUTE_NORMAL,
      NULL);
  _ApiCheck(IsValid(), "CreateFile");
}

}
}