#ifndef WIN32_KERNEL_OBJECT_H_
#define WIN32_KERNEL_OBJECT_H_

#include <windows.h>

namespace next {
namespace win32 {

// Windows 内核对象
// 自带引用计数，需要在销毁时释放。
class KernelObject {
public:
  explicit KernelObject() : handle_(NULL) {}
  explicit KernelObject(HANDLE handle) : handle_(handle) {}
  explicit KernelObject(const KernelObject& other) = delete;
  ~KernelObject() { Close(); }

public:
  void Close();

  bool IsNull() const { return handle_ == NULL; }
  bool IsInvalid() const { return handle_ == INVALID_HANDLE_VALUE; }
  bool IsValid() const { return !(IsNull() || IsInvalid()); }

  HANDLE handle() const { return handle_; }

protected:
  HANDLE handle_;
};

}
}

#endif
