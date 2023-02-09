#ifndef WIN32_FILE_OBJECT_H_
#define WIN32_FILE_OBJECT_H_

#include "win32/KernelObject.h"

namespace next {
namespace win32 {

class FileObject: public KernelObject {
public:
  explicit FileObject() {}
  explicit FileObject(HANDLE handle): KernelObject(handle) {}
};

}
}

#endif
