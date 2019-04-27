// Copyright 2019 Zhixuan Xiao <xzxxzx401@gmail.com>

#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
  // google::InitGoogleLogging(argv[0]);
  testing::InitGoogleTest(&argc, argv);
  // testing::AddGlobalTestEnvironment(
  //     new databus2::Databus2TestEnviroment(argc, argv));

  return RUN_ALL_TESTS();
}


