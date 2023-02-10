#include "win32/io_completion_service.h"

namespace next {
namespace win32 {

void IoCompletionService::RunLoop() {
  IoCompletionDelegate* delegate = nullptr;
  IoCompletionStatus* status = nullptr;
  
  while (port_.WaitStatus(delegate, status)) {
    if (delegate != nullptr && status != nullptr) {
      delegate->IoCompleted(status);
    }
  }
}

void IoCompletionService::Quit() {
  port_.Close();
}

}
}