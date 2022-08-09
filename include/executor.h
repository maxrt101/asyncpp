#ifndef _ASYNCPP_EXECUTOR_H_
#define _ASYNCPP_EXECUTOR_H_ 1

#include <condition_variable>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include <queue>

#include <asyncpp/lock.h>
#include <asyncpp/task.h>
#include <asyncpp/pool.h>

namespace asyncpp {

template <typename T = std::function<bool(void)>>
class IntervalExecutor {
 private:
  ThreadPool<Task<T>> m_pool;

 public:
  inline IntervalExecutor(int threads = 1) : m_pool(threads) {}
  inline ~IntervalExecutor() = default;

  template <typename Rep, typename Period>
  inline void addTask(std::chrono::duration<Rep, Period> d, T task) {
    m_pool.addTask(Task([d](auto task) {
      bool running = true;
      while (running) {
        std::this_thread::sleep_for(d);
        running = task();
      }
    }, task));
  }

  template <typename Rep, typename Period>
  inline void addTasks(std::chrono::duration<Rep, Period> d, const std::vector<T>& tasks) {
    for (auto& task : tasks) {
      addTask(d, task);
    }
  }

  inline void waitForStarted() {
    m_pool.waitForStarted();
  }
  
  inline void waitForAll() {
    m_pool.waitForAll();
  }
};


template <typename T = std::function<void(void)>>
class DelayedExecutor {
 private:
  ThreadPool<Task<T>> m_pool;

 public:
  inline DelayedExecutor(int threads = 1) : m_pool(threads) {}
  inline ~DelayedExecutor() = default;

  template <typename Rep, typename Period>
  inline void addTask(std::chrono::duration<Rep, Period> d, T task) {
    m_pool.addTask(Task([d](auto task) {
      std::this_thread::sleep_for(d);
      task();
    }, task));
  }

  template <typename Rep, typename Period>
  inline void addTasks(std::chrono::duration<Rep, Period> d, const std::vector<T>& tasks) {
    for (auto& task : tasks) {
      addTask(d, task);
    }
  }

  inline void waitForStarted() {
    m_pool.waitForStarted();
  }
  
  inline void waitForAll() {
    m_pool.waitForAll();
  }
};


template <typename T = std::function<void(void)>>
class SingeThreadedExecutor  {
 private:
  ThreadPool<T> m_pool;

 public:
  inline SingeThreadedExecutor() : m_pool(1) {}
  inline ~SingeThreadedExecutor() = default;

  inline void addTask(T task) {
    m_pool.addTask(task);
  }

  inline void addTasks(const std::vector<T>& tasks) {
    for (auto& task : tasks) {
      m_pool.addTask(task);
    }
  }

  inline void waitForStarted() {
    m_pool.waitForStarted();
  }
  
  inline void waitForAll() {
    m_pool.waitForAll();
  }
};


template <typename T = std::function<void(void)>>
class MultiThreadedExecutor {
 private:
  ThreadPool<T> m_pool;

 public:
  inline MultiThreadedExecutor(int threads = 0) : m_pool(threads) {}
  inline ~MultiThreadedExecutor() = default;

  inline void addTask(T task) {
    m_pool.addTask(task);
  }

  inline void addTasks(const std::vector<T>& tasks) {
    for (auto& task : tasks) {
      m_pool.addTask(task);
    }
  }

  inline void waitForStarted() {
    m_pool.waitForStarted();
  }
  
  inline void waitForAll() {
    m_pool.waitForAll();
  }
};


} /* namespace asyncpp */

#endif /* _ASYNCPP_EXECUTOR_H_ */