#ifndef WIN32_FILE_IO_SERVICE_H_
#define WIN32_FILE_IO_SERVICE_H_

#include "win32/io_service.h"

#include <memory>
#include <functional>

namespace next {
namespace win32 {

class FileChannel {

};

using FileHandler = std::function<void(FileChannel&)>;

class File {
public:
  File();

private:
  std::unique_ptr<FileChannel> _channel;
};

class FileIoService {
public:
  FileIoService(IoService& ioService):
    _ioService(ioService) {}

public:
  File CreateFile(
      const std::wstring& filePath, 
      FileHandler handler = nullptr) {

  }

private:
  IoService& _ioService;
};

}
}

#endif
