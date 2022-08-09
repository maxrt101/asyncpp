#include <chrono>
#include <asyncpp/asyncpp.h>

using namespace asyncpp;
using namespace std::chrono_literals;

Locked<int> resource = 0;

void compute(int s) {
  resource.lock();
  sleep(std::chrono::seconds(s));
  resource.getValue() = 10;
  resource.unlock();
}

void computeScoped(int s) {
  resource.update([s](int& value) {
    sleep(std::chrono::seconds(s));
    value *= 2;
  });
}

int main(int argc, char ** argv) {
  auto beginTime = std::chrono::system_clock::now();

  auto f1 = async(compute, 1);
  auto f2 =async(computeScoped, 2);

  sleep(200ms); // Give time for async to start

  await(f1, f2);
  
  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time: %f\n", time);

  return resource.get() != 20 || time < 3;
}
