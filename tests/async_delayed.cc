#include <chrono>
#include <asyncpp/asyncpp.h>

using namespace asyncpp;
using namespace std::chrono_literals;

int compute() {
  return 125;
}

int main(int argc, char ** argv) {
  auto beginTime = std::chrono::system_clock::now();

  int result = await(asyncDelayed(2s, compute));

  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time: %f\n", time);

  return result != 125 || time < 2.0f;
}
