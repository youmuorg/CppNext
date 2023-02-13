#include "win32/file_io_service.h"

#include <gtest/gtest.h>

#include <thread>

using namespace next;

class FileIoTest: public testing::Test {
protected:
  FileIoTest() :
    _thread(&win32::IoService::Run, &_ioService),
    _fileIoService(_ioService) {}
  virtual ~FileIoTest() {}
  virtual void SetUp() override {}
  virtual void TearDown() override {
    _ioService.Quit();
  }

protected:
  win32::IoService _ioService;
  win32::FileIoService _fileIoService;
  std::jthread _thread;
};

TEST_F(FileIoTest, Test) {
  EXPECT_EQ(1, 1);
}

TEST_F(FileIoTest, Write) {
  auto file = File(_fileIoService);
  auto future = file.Write("Hello");
  future.wait();
}