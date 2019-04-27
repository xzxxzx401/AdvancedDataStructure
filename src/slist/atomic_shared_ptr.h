// Copyright 2019 Zhixuan Xiao <xzxxzx401@gmail.com>

#ifndef ATOMIC_SHARED_PTR_H_
#define ATOMIC_SHARED_PTR_H_

#include <atomic>

template<typename T>
class std::atomic<std::shared_ptr<T>> {
 public:
  atomic() noexcept = default;
  ~atomic() noexcept = default;
  atomic(const atomic &) = delete;
  atomic &operator=(const atomic &) = delete;
  atomic &operator=(const atomic &) volatile = delete;

  bool atomic_is_lock_free() {
    return std::atomic_is_lock_free(&this->ptr_);
  }

  std::shared_ptr<T> atomic_load() const {
    return std::atomic_load(&this->ptr_);
  }

  void atomic_store(std::shared_ptr<T> r) {
    std::atomic_store(&this->ptr_, r);
  }

  bool atomic_compare_exchange_weak(std::shared_ptr<T> *expected,
                                    std::shared_ptr<T> desired) {
    return std::atomic_compare_exchange_weak(&this->ptr_, expected, desired);
  }

  bool atomic_compare_exchange_strong(std::shared_ptr<T> *expected,
                                      std::shared_ptr<T> desired) {
    return std::atomic_compare_exchange_strong(&this->ptr_, expected, desired);
  }

 protected:
  std::shared_ptr<T> ptr_{nullptr};

};

#endif // ATOMIC_SHARED_PTR_H_
