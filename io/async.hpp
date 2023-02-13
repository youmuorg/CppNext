#ifndef IO_ASYNC_HPP_
#define IO_ASYNC_HPP_

namespace next {
namespace io {

// IO 状态
enum class Status {
  unknown = 0,
  create,
  open,
  write,
  read,
  close,
  broken
};

// IO 模式
enum class Mode {
  unknown = 0,
  create,
  open,
};

}
}

#endif
