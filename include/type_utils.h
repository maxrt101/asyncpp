#ifndef _ASYNCPP_TYPE_UTILS_H_
#define _ASYNCPP_TYPE_UTILS_H_ 1

namespace asyncpp {

template<typename T, typename... Args>
inline T return_type(T(*)(Args...)) {}

template<typename Class, typename T, typename... Args>
inline T return_type(T(Class::*)(Args...)) {}

} /* namespace asyncpp */

#endif