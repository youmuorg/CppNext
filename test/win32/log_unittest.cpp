#include "win32/log_utils.h"

#include <gtest/gtest.h>

using namespace next;

class LogUtilsTest : public testing::Test {
protected:
  // virtual void SetUp() override {
  //   log::default_logger.AddSink()
  // }

};

TEST_F(LogUtilsTest, Log) {
  log::Info() << std::format("Test {}", "a");
  win32::_LogInfo() << L"Debug test";
  EXPECT_EQ(1, 1);
}