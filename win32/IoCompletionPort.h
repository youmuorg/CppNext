#ifndef WIN32_IO_COMPLETION_PORT_H_
#define WIN32_IO_COMPLETION_PORT_H_

#include "win32/KernelObject.h"
#include "win32/FileObject.h"

#include <cstdint>

namespace next {
namespace win32 {

// IO 完成状态
// 包含异步 IO 数据，也就是重叠 IO 信息。
struct IoCompletionStatus : public OVERLAPPED {
  LPDWORD bytes;          // 异步传输的字节数
  IoCompletionDelegate* delegate;
};

// IO 完成委托
// 用于执行异步完成回调。
class IoCompletionDelegate {
public:
  virtual void IoCompleted(IoCompletionStatus* status) = 0;
};

// IO 完成端口
// Windows 提供的异步 IO 机制。
class IoCompletionPort:
  public KernelObject {
public:
  explicit IoCompletionPort();

public:
  // 关联一个文件句柄到 IO 完成端口
  void AssociateFile(FileObject file, ULONG_PTR key);

  // 获取一个完成状态
  bool GetStatus(
      LPOVERLAPPED* overlapped,
      PULONG_PTR key,
      LPDWORD bytesTransferred,
      DWORD* error,
      DWORD timeout);

  // 等待一个完成状态
  // 该方法将导致执行线程和完成端口相关联，一个线程只能关联一个完成端口。
  // @return 等待成功返回 true，收到退出状态返回 false。
  bool WaitStatus(IoCompletionDelegate*& delegate, IoCompletionStatus*& status);
};

}
}

#endif
