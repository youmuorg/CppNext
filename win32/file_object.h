#ifndef WIN32_FILE_OBJECT_H_
#define WIN32_FILE_OBJECT_H_

#include "io/async.hpp"
#include "win32/io_object.h"

#include <string>
#include <string_view>

namespace next {
namespace win32 {

class FileObject: public IoObject {
public:
  explicit FileObject() {}
  explicit FileObject(HANDLE handle): IoObject(handle) {}
  explicit FileObject(std::wstring_view filePath, io::Mode mode) {
    Create(filePath, mode);
  }

public:
  void Create(std::wstring_view filePath, io::Mode mode);
};

}
}

#endif
