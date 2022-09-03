#include <chrono>
#include <asyncpp/asyncpp.h>

void forkedFunction() {
  printf("[process] start\n");
  sleep(1);
  printf("[process] stop\n");
  exit(25);
}

bool testLaunch() {
  auto p = asyncpp::Process::launch(forkedFunction)->toUnique();

  p->wait();
  return p->getExitCode() == 25;
}

bool testLaunchSync() {
  auto p = asyncpp::Process::launchSync(forkedFunction)->toUnique();

  return p->getExitCode() == 25;
}

bool testLaunchAsync() {
  auto p = asyncpp::Process::launchAsync(forkedFunction)->toUnique();

  sleep(2);

  return p->getExitCode() == 25;
}

int main(int argc, char ** argv) {
  bool result = false;

  // TODO: Rework
  result &= !testLaunch();
  result &= !testLaunchSync();
  result &= !testLaunchAsync();

  return result;
}
