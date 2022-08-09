#ifndef _ASYNCPP_ASYNC_H_
#define _ASYNCPP_ASYNC_H_ 1

#include <thread>
#include <type_traits>

#include <asyncpp/pool.h>
#include <asyncpp/future.h>
#include <asyncpp/type_utils.h>

namespace asyncpp {

template <typename T>
inline T await(Future<T> future) {
  return future.get();
}

template <>
inline void await<void>(Future<void> future) {
  future.get();
}

template <typename F, typename... Args>
inline auto async(F f, Args... args) {
  Future<decltype(return_type(f))> result;

  auto t = std::thread([result, f, args...]() {
    if constexpr (std::is_same_v<decltype(return_type(f)), void>) {
      f(args...);
      result.set();
    } else {
      result.set(f(args...));
    }
  }, args...);

  t.detach();

  return result;
}

template <typename T, typename F, typename... Args>
inline auto async_pool(ThreadPool<T>& pool, F f, Args... args) {
  Future<decltype(return_type(f))> result;

  pool.addTask([result, f, args...]() {
    if constexpr (std::is_same_v<decltype(return_type(f)), void>) {
      f(args...);
      result.set();
    } else {
      result.set(f(args...));
    }
  });

  return result;
}

template <typename Rep, typename Period, typename F, typename... Args>
inline auto async_delayed(std::chrono::duration<Rep, Period> tp, F f, Args... args) {
  Future<decltype(return_type(f))> result;

  auto t = std::thread([result, tp, f, args...]() {
    std::this_thread::sleep_for(tp);
    if constexpr (std::is_same_v<decltype(return_type(f)), void>) {
      f(args...);
      result.set();
    } else {
      result.set(f(args...));
    }
  }, args...);

  t.detach();

  return result;
}

// async_constrained time_bound task args ???

} /* namespace asyncpp */

#endif /* _ASYNCPP_ASYNC_H_ */