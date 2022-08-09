#ifndef _ASYNCPP_ASYNCPP_H_
#define _ASYNCPP_ASYNCPP_H_ 1

#include <chrono>
#include <thread>

#include <asyncpp/async.h>
#include <asyncpp/executor.h>
#include <asyncpp/future.h>
#include <asyncpp/lock.h>
#include <asyncpp/locked.h>
#include <asyncpp/pool.h>
#include <asyncpp/task.h>
#include <asyncpp/type_utils.h>


#define ASYNCPP_VERSION_MAJOR 0
#define ASYNCPP_VERSION_MINOR 1
#define ASYNCPP_VERSION_PATCH 0

#define ASYNCPP_VERSION "0.1.0"

#define ASYNCPP_REQUIRE_VERSION(major, minor, patch) \
  static_assert(major == ASYNCPP_VERSION_MAJOR && minor == ASYNCPP_VERSION_MINOR && patch == ASYNCPP_VERSION_PATCH, "Required asyncpp version is different from actual version (" ASYNCPP_VERSION ")")

#define ASYNCPP_REQUIRE_AT_LEAST_VERSION(major, minor, patch) \
  static_assert(major >= ASYNCPP_VERSION_MAJOR && minor >= ASYNCPP_VERSION_MINOR && patch >= ASYNCPP_VERSION_PATCH, "Minimum required asyncpp version is newer than actual version (" ASYNCPP_VERSION ")")


namespace asyncpp {

template <typename Rep, typename Period>
void sleep(std::chrono::duration<Rep, Period> d) {
  std::this_thread::sleep_for(d);
}

} /* namespace asyncpp */

#endif /* _ASYNCPP_ASYNCPP_H_ */