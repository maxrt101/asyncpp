#ifndef _ASYNCPP_FUTURE_
#define _ASYNCPP_FUTURE_ 1

#include <condition_variable>
#include <functional>
#include <atomic>

#include <asyncpp/lock.h>

namespace asyncpp {

template <typename T>
class Future {
 public:
  using CallbackT = std::function<void(T&)>;

 private:
  struct FutureState {
    std::atomic<bool> isReady;
    std::condition_variable cv;
    Lock lock;
    CallbackT callback;
    T result;

    inline FutureState() : isReady(false) {}
  };

 private:
  size_t* m_count = nullptr;
  FutureState* m_state = nullptr;

 public:
  inline Future() {
    m_count = new size_t(0);
    m_state = new FutureState;
  }

  inline Future(const Future& rhs) {
    m_count = rhs.m_count;
    m_state = rhs.m_state;
    (*m_count)++;
  }

  // inline Future(Future&&) = default;

  inline ~Future() {
    cleanup();
  }

  Future& operator =(const Future& rhs) {
    *this = rhs;
    return *this;
  }

  inline bool isReady() const {
    return m_state->isReady.load();
  }

  inline void onReady(CallbackT cb) {
    m_state->callback = cb;
  }

  inline T& get() {
    if (!isReady()) {
      waitForResult();
    }
    auto sl = m_state->lock.lockScope();
    return m_state->result;
  }

  inline const T& get() const {
    if (!isReady()) {
      waitForResult();
    }
    auto sl = m_state->lock.lockScope();
    return m_state->result;
  }

  inline void set(T& value) {
    auto sl = m_state->lock.lockScope();
    m_state->result = value;
    notifyResultReady();
  }

  inline void set(const T& value) const {
    auto sl = m_state->lock.lockScope();
    m_state->result = value;
    notifyResultReady();
  }

 private:
  inline void waitForResult() const {
    auto lock = std::unique_lock<std::mutex>(m_state->lock.getMutex());
    m_state->cv.wait(lock, [&]() { return isReady(); });
  }

  inline void notifyResultReady() const {
    m_state->isReady.store(true);
    m_state->cv.notify_all();
  }

  inline void cleanup() {
    if (m_count && m_state) {
      (*m_count)--;
      if (!m_count) {
        delete m_count;
        delete m_state;
        m_count = nullptr;
        m_state = nullptr;
      }
    }
  }
};


template <>
class Future<void> {
 public:
  using CallbackT = std::function<void(void)>;

 private:
  struct FutureState {
    std::atomic<bool> isReady;
    std::condition_variable cv;
    Lock lock;
    CallbackT callback;

    inline FutureState() : isReady(false) {}
  };

 private:
  size_t* m_count = nullptr;
  FutureState* m_state = nullptr;

 public:
  inline Future() {
    m_count = new size_t(0);
    m_state = new FutureState;
  }

  inline Future(const Future& rhs) {
    m_count = rhs.m_count;
    m_state = rhs.m_state;
    (*m_count)++;
  }

  // inline Future(Future&&) = default;

  inline ~Future() {
    cleanup();
  }

  Future& operator =(const Future& rhs) {
    *this = rhs;
    return *this;
  }

  inline bool isReady() const {
    return m_state->isReady.load();
  }

  inline void onReady(CallbackT cb) {
    m_state->callback = cb;
  }

  inline void get() const {
    if (!isReady()) {
      waitForResult();
    }
    auto sl = m_state->lock.lockScope();
  }

  inline void set() const {
    auto sl = m_state->lock.lockScope();
    notifyResultReady();
  }

 private:
  inline void waitForResult() const {
    auto lock = std::unique_lock<std::mutex>(m_state->lock.getMutex());
    m_state->cv.wait(lock, [&]() { return isReady(); });
  }

  inline void notifyResultReady() const {
    m_state->isReady.store(true);
    m_state->cv.notify_all();
  }

  inline void cleanup() {
    if (m_count && m_state) {
      (*m_count)--;
      if (!m_count) {
        delete m_count;
        delete m_state;
        m_count = nullptr;
        m_state = nullptr;
      }
    }
  }
};

} /* namespace asyncpp */

#endif /* _ASYNCPP_FUTURE_ */