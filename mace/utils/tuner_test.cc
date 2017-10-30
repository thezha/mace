//
// Copyright (c) 2017 XiaoMi All rights reserved.
//
#include <thread>

#include "gtest/gtest.h"

#include "mace/utils/tuner.h"

namespace mace {

class TunerTest: public ::testing::Test {
 protected:
  virtual void SetUp() {
    remove( "/data/local/tmp/mace.config" );
    setenv("MACE_RUN_PARAMTER_PATH", "/data/local/tmp/mace.config", 1);
  }
};

TEST_F(TunerTest, SimpleRun) {
  int expect = 1;
  auto TunerFunc = [&](const std::vector<int>& params)->int {
    if (params.front() == 1) {
      return expect;
    } else {
      return expect + 1;
    }
  };

  std::vector<int> default_params(1, 1);
  int res = Tuner<int>::Get()->template TuneOrRun<int>("SimpleRun", default_params, nullptr, TunerFunc);

  EXPECT_EQ(expect, res);

  default_params[0] = 2;
  res = Tuner<int>::Get()->template TuneOrRun<int>("SimpleRun", default_params, nullptr, TunerFunc);
  EXPECT_EQ(expect+1, res);
}

TEST_F(TunerTest, SimpleTune) {
  int expect = 3;
  auto TunerFunc = [&](const std::vector<int>& params)->int {
    if (params.front() == expect) {
      return expect;
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      return params.front();
    }
  };

  std::vector<int> default_params(1, 1);
  auto params_generator = []()->std::vector<std::vector<int>> {
    return {{1}, {2}, {3}, {4}};
  };
  // tune
  int res = Tuner<int>::Get()->template TuneOrRun<int>("SimpleRun", default_params, *params_generator, TunerFunc);
  EXPECT_EQ(expect, res);

  // run
  res = Tuner<int>::Get()->template TuneOrRun<int>("SimpleRun", default_params, nullptr, TunerFunc);
  EXPECT_EQ(expect, res);
}

} //  namespace mace
