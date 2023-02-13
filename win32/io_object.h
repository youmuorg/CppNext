#ifndef WIN32_IO_OBJECT_H_
#define WIN32_IO_OBJECT_H_

#include "win32/kernel_object.h"

namespace next {
namespace win32 {

class IoObject: public KernelObject {
public:
  explicit IoObject() {}
  explicit IoObject(HANDLE handle): KernelObject(handle) {}

};

}
}

#endif
