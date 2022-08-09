#ifndef _ASYNCPP_LOCK_H_
#define _ASYNCPP_LOCK_H_ 1

#include <mutex>

namespace asyncpp {

class Lock {
 public:
  class ScopedLock {
   private:
    Lock& m_lock;

   public:
    inline ScopedLock(Lock& lock) : m_lock(lock) {
      m_lock.lock();
    }

    inline ~ScopedLock() {
      m_lock.unlock();
    }
  };

 private:
  std::mutex m_mutex;

 public:
  inline Lock() = default;
  inline Lock(const Lock&) = delete;
  inline ~Lock() = default;

  inline void lock() {
    m_mutex.lock();
  }

  inline void tryLock() {
    m_mutex.try_lock();
  }

  inline void unlock() {
    m_mutex.unlock();
  }

  inline std::mutex& getMutex() {
    return m_mutex;
  }

  inline ScopedLock lockScope() {
    return ScopedLock(*this);
  }
};

}; /* namespace asyncpp */

#endif /* _ASYNCPP_LOCK_H_ */