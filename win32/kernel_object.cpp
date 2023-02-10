#include "win32/kernel_object.h"

namespace next {
namespace win32 {

void KernelObject::Close() {
  if (IsValid()) {
    ::CloseHandle(handle_);
  }
  handle_ = NULL;
}

}
}
