#include "win32/io_completion_port.h"
#include "win32/check_utils.h"

#include <windows.h>
#include <assert.h>

namespace next {
namespace win32 {

IoCompletionPort::IoCompletionPort() {
  handle_ = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
  _ApiCheck(IsValid(), "CreateIoCompletionPort");
}

void IoCompletionPort::AssociateFile(FileObject file, ULONG_PTR key) {
  _Check(IsValid());

  HANDLE port = ::CreateIoCompletionPort(
      file.handle(),
      handle_,
      key,
      0);
  _ApiCheck(port == handle_, "CreateIoCompletionPort");
}

bool IoCompletionPort::WaitStatus(IoCompletionDelegate*& delegate, IoCompletionStatus*& status) {
  _Check(IsValid());

  DWORD* bytesNumber = nullptr;
  OVERLAPPED* overlapped;
  ULONG_PTR key;
  BOOL bret = ::GetQueuedCompletionStatus(
      handle_,
      bytesNumber,
      &key,
      &overlapped,
      INFINITE);
  if (!bret) {
    // 完成端口被关闭
    status = nullptr;
    return false;
  }

  delegate = reinterpret_cast<IoCompletionDelegate*>(key);
  status = static_cast<IoCompletionStatus*>(overlapped);
  return true;
}

}
}
