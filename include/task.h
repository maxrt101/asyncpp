#ifndef _ASYNCPP_TASK_H_
#define _ASYNCPP_TASK_H_ 1

#include <functional>
#include <tuple>

namespace asyncpp {

template <typename... Args>
class Task {
 private:
  std::function<void(Args...)> m_function;
  std::tuple<Args...> m_args;

 public:
  inline Task() {}

  template <class F>
  inline Task(F function, Args... args) : m_function(function), m_args(args...) {}

  inline void operator()() {
    std::apply(m_function, m_args);
  }
};

} /* namespace asyncpp */

#endif /* _ASYNCPP_TASK_H_ */