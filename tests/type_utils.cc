#include <chrono>
#include <asyncpp/asyncpp.h>

using namespace asyncpp;
using namespace std::chrono_literals;

int compute_i(int a, float b) {
  return 125;
}

float compute_f(int a) {
  return 125.0f;
}

void compute_v() {}

int main(int argc, char ** argv) {
  return !std::is_same_v<decltype(return_type(compute_i)), int>
      && !std::is_same_v<decltype(return_type(compute_f)), float>
      && !std::is_same_v<decltype(return_type(compute_v)), void>;
}
