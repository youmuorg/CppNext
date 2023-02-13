#ifndef WIN32_IO_SERVICE_H_
#define WIN32_IO_SERVICE_H_

#include "win32/io_completion_service.h"

namespace next {
namespace win32 {

class IoService {
public:
  IoService();

public:
  void Run();
  void Quit();

private:
  IoCompletionService _ioCompletionService;
};

}
}

#endif
