// Copyright 2019 Zhixuan Xiao <xzxxzx401@gmail.com>

#include "slist/slist.h"

#include <vector>
#include <random>
#include <thread>

#include <gtest/gtest.h>
#include <array>

namespace advanced_data_structure {

TEST(SListTest, NormalTest) {
  SList<int> l;
  const int total = 10000;
  for (int i = 0; i < total; i++) {
    l.PushFront(i);
  }
  auto seed = std::random_device()();
  std::mt19937 random_engine(seed);
  std::uniform_int_distribution<std::mt19937::result_type> distribution1(0, total - 1);
  for (int i = 0; i < total / 10; i++) {
    ASSERT_EQ(l.Find(distribution1(random_engine), nullptr), true);
  }
  std::uniform_int_distribution<std::mt19937::result_type> distribution2(total, total * 2);
  for (int i = 0; i < total / 10; i++) {
    ASSERT_EQ(l.Find(distribution2(random_engine), nullptr), false);
  }
  for (int i = total - 1; i >= 0; i--) {
    ASSERT_EQ(l.PopFront()->operator*(), i);
  }
  for (int i = 0; i < total / 10; i++) {
    ASSERT_EQ(l.Find(distribution1(random_engine), nullptr), false);
  }
}

TEST(SListTest, NullTest) {
  SList<std::string> l;
  ASSERT_EQ(nullptr, l.PopFront());
  l.PushFront("xiaozhixuan");
  ASSERT_EQ(l.PopFront()->operator*(), "xiaozhixuan");
  ASSERT_EQ(l.PopFront(), nullptr);
}

TEST(SListTest, MultiThreadTest) {
  struct BigObj {
    std::vector<char> v;
    int id;
    explicit BigObj(int i) : v(10240, 'c'), id(i) {}
  };
  SList<BigObj*> l;
  std::vector<std::thread> write_threads;
  std::vector<std::thread> read_threads;
  const int thread_num = 10;
  std::array<std::atomic_int64_t, thread_num> read_num;
  std::for_each(read_num.begin(), read_num.end(), [&](auto& t){t = 0;});
  std::atomic_int64_t total_read{0};
  int64_t total_write = 0;

  auto writer_work = [&] (int type_id, int amount) {
    while(amount--) {
      l.PushFront(new BigObj(type_id));
    }
  };

  auto reader_work = [&](){
    while(total_read.load() < total_write) {
      auto f = l.PopFront();
      if (f) {
        ASSERT_EQ(f->operator*()->v.size(), 10240);
        ASSERT_GE(f->operator*()->id, 0);
        ASSERT_LT(f->operator*()->id, thread_num);
        read_num[f->operator*()->id]++;
        total_read++;
        delete(f->operator*());
        f->operator*() = nullptr;
      }
    }
  };

  auto get_count_by_thread_id = [&](const int i) {return (thread_num - i) * 1000;};

  for (int i = 0; i < thread_num; i++) {
    total_write += get_count_by_thread_id(i);
  }
  for (int i = 0; i < thread_num; i++) {
    write_threads.emplace_back(writer_work, i, get_count_by_thread_id(i));
    read_threads.emplace_back(reader_work);
  }
  std::for_each(write_threads.begin(), write_threads.end(), [&](auto& t){t.join();});
  write_threads.clear();
  std::for_each(read_threads.begin(), read_threads.end(), [&](auto& t){t.join();});
  read_threads.clear();

  for (int i = 0; i < thread_num; i++) {
    ASSERT_EQ(read_num[i], get_count_by_thread_id(i)) << "i is " << i;
  }
  ASSERT_EQ(l.PopFront(), nullptr);
}

}  // namespace advanced_data_structure
