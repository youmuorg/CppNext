#include "win32/io_completion_service.h"

#include <gtest/gtest.h>

#include <thread>

using namespace next;

class FileIoTest: public testing::Test {
protected:
  FileIoTest() :
    thread_(&win32::IoCompletionService::RunLoop, &service_) {}
  virtual ~FileIoTest() {}
  virtual void SetUp() override {}
  virtual void TearDown() override {
    service_.Quit();
  }

private:
  win32::IoCompletionService service_;
  std::jthread thread_;
};

TEST_F(FileIoTest, Test) {
  EXPECT_EQ(1, 1);
}

TEST_F(FileIoTest, Write) {

}