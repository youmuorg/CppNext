#include "win32/KernelObject.h"

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
