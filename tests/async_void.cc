#include <chrono>
#include <asyncpp/asyncpp.h>

using namespace asyncpp;
using namespace std::chrono_literals;

Locked<int> result;

void compute(int s) {
  sleep(std::chrono::seconds(s));
  result.set(125);
}

int main(int argc, char ** argv) {
  await(async(compute, 2));

  return result.get() != 125;
}
