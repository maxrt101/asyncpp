#ifndef _ASYNCPP_LOCKED_H_
#define _ASYNCPP_LOCKED_H_ 1

#include <functional>
#include <asyncpp/lock.h>

namespace asyncpp {

template <typename T>
class Locked {
 public:
  using UpdaterT = std::function<void(T&)>;
  using WorkerT = std::function<void(const T&)>;

 private:
  T m_value;
  mutable Lock m_lock;

 public:
  inline Locked() = default;
  inline Locked(const T& value) : m_value(value) {}
  inline ~Locked() = default;

  inline Locked& operator =(const T& value) {
    auto sl = m_lock.lockScope();
    m_value = value;
    return *this;
  }

  inline T& getValue() {
    return m_value;
  }

  inline T& get() {
    return m_value;
  }

  inline const T& get() const {
    return m_value;
  }

  inline void set(T& value) {
    auto sl = m_lock.lockScope();
    m_value = value;
  }

  inline void set(const T& value) {
    auto sl = m_lock.lockScope();
    m_value = value;
  }

  inline void update(UpdaterT updater) {
    auto sl = m_lock.lockScope();
    updater(m_value);
  }

  inline void withLocked(WorkerT worker) {
    auto sl = m_lock.lockScope();
    worker(m_value);
  }

  inline void lock() {
    m_lock.lock();
  }

  inline void unlock() {
    m_lock.unlock();
  }

  inline Lock::ScopedLock lockScope() {
    return std::move(m_lock.lockScope());
  }

};

} /* namespace asyncpp */

#endif /* _ASYNCPP_LOCKED_H_ */