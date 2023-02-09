#ifndef WIN32_IO_COMPLETION_SERVICE_H_
#define WIN32_IO_COMPLETION_SERVICE_H_

#include "win32/IoCompletionPort.h"

namespace next {
namespace win32 {

// IO 完成服务
// 提供异步 IO Proactive 模型简单封装
class IoCompletionService {
public:
  // 开始完成状态等待循环
  void RunLoop();


private:
  IoCompletionPort port_;
};

}
}

#endif
