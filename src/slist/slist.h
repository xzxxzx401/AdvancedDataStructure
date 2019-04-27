// Copyright 2019 Zhixuan Xiao <xzxxzx401@gmail.com>

#ifndef SLIST_H_
#define SLIST_H_

#include <atomic>
#include <memory>

#include "atomic_shared_ptr.h"

namespace advanced_data_structure {

template<typename T>
class SList {
 protected:
  class SListNode {
    friend class SList;
   protected:
    T t_;
    std::shared_ptr<SListNode> next_;
   public:
    T &operator*() { return t_; }
    const T &operator*() const { return t_; }
    T *operator&() { return &t_; }
    const T *operator&() const { return &t_; }
  };
  std::atomic<std::shared_ptr<SListNode>> head_;

 public:
  void PushFront(T t) {
    std::shared_ptr<SListNode> tmp = std::make_shared<SListNode>();
    tmp->t_ = t;
    tmp->next_ = head_.atomic_load();
    while (!this->head_.atomic_compare_exchange_weak(&tmp->next_, tmp)) {}
  }

  std::shared_ptr<SListNode> PopFront() {
    auto tmp = this->head_.atomic_load();
    while (tmp && !this->head_.atomic_compare_exchange_weak(&tmp, tmp->next_)) {}
    return tmp;
  }

  auto Find(T t, std::shared_ptr<SListNode>* res) const {
    auto tmp = this->head_.atomic_load();
    while (tmp && tmp->t_ != t) {
      tmp = tmp->next_;
    }
    if (tmp) {
      if (res) {
        *res = tmp;
      }
      return true;
    }
    return false;
  }

};

}  // namespace advanced_data_structure

#endif  // SLIST_H_
