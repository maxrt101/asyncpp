#include <chrono>
#include <asyncpp/asyncpp.h>

using namespace asyncpp;
using namespace std::chrono_literals;

Lock lock;

void compute(int s) {
  lock.lock();
  sleep(std::chrono::seconds(s));
  lock.unlock();
}

void computeScoped(int s) {
  auto sl = lock.lockScope();
  sleep(std::chrono::seconds(s));
}

int main(int argc, char ** argv) {
  auto beginTime = std::chrono::system_clock::now();

  async(compute, 2);
  async(computeScoped, 1);

  sleep(200ms); // Give time for async to start

  lock.lock();
  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time: %f\n", time);

  return time < 3;
}
