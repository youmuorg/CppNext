#include "win32/IoCompletionService.h"

namespace next {
namespace win32 {

void IoCompletionService::RunLoop() {
  IoCompletionDelegate* delegate = nullptr;
  IoCompletionStatus* status = nullptr;
  
  while (port_.WaitStatus(delegate, status)) {
    if (delegate != nullptr && status != nullptr) {
      delegate->OnIoCompleted(status);
    }
  }
}

}
}