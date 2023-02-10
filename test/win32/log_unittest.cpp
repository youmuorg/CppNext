#include "win32/log_utils.h"

#include <gtest/gtest.h>

using namespace next;

TEST(LogUtilsTest, Log) {
  win32::_Log(win32::LogLevel::info, L"Test Log", L"a1");

  EXPECT_EQ(1, 1);
}