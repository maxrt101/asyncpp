#include <chrono>
#include <asyncpp/asyncpp.h>

using namespace asyncpp;
using namespace std::chrono_literals;

void compute(int s, Future<int> result) {
  sleep(std::chrono::seconds(s));
  result.set(125);
}

int main(int argc, char ** argv) {
  Future<int> result;

  async(compute, 2, result);

  return result.get() != 125;
}
