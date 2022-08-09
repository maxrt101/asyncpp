#include <chrono>
#include <asyncpp/asyncpp.h>

using namespace asyncpp;
using namespace std::chrono_literals;

int compute(int value) {
  sleep(1s);
  return value;
}

int main(int argc, char ** argv) {
  ThreadPool pool(4);

  auto beginTime = std::chrono::system_clock::now();

  auto f1 = async_pool(pool, compute, 10);
  auto f2 = async_pool(pool, compute, 20);

  int res1 = f1.get(), res2 = f2.get();

  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time: %f\n", time);

  return res1 != 10 || res2 != 20 || time < 1.0f || time > 1.5f;
}
