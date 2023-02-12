#include "win32/io_completion_service.h"
#include "win32/log_utils.h"

namespace next {
namespace win32 {

void IoCompletionService::RunLoop() {
  IoCompletionDelegate* delegate = nullptr;
  IoCompletionStatus* status = nullptr;
  
  _LogInfo() << L"IoCompletionService Start";
  while (port_.WaitStatus(delegate, status)) {
    if (delegate != nullptr && status != nullptr) {
      delegate->IoCompleted(status);
    }
  }

  _LogInfo() << L"IoCompletionService End";
}

void IoCompletionService::Quit() {
  port_.Close();
}

}
}