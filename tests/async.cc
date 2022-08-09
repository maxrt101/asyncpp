#include <chrono>
#include <asyncpp/asyncpp.h>

using namespace asyncpp;
using namespace std::chrono_literals;

int compute(int s) {
  sleep(std::chrono::seconds(s));
  return 125;
}

int main(int argc, char ** argv) {
  int result = await(async(compute, 2));

  return result != 125;
}
