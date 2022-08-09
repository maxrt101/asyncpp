#include <chrono>
#include <asyncpp/asyncpp.h>

using namespace asyncpp;
using namespace std::chrono_literals;

Locked<int> counter;

void compute() {
  sleep(1s);
  counter.update([](int& value) { ++value; });
}

int main(int argc, char ** argv) {
  ThreadPool pool(4);

  auto beginTime = std::chrono::system_clock::now();

  pool.addTask(compute);
  pool.addTask(compute);
  pool.addTask(compute);

  pool.waitForAll();

  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time: %f\n", time);

  return counter.get() != 3 || time < 1.0f || time > 1.5f;
}
