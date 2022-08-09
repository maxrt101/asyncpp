#include <chrono>
#include <asyncpp/asyncpp.h>

using namespace asyncpp;
using namespace std::chrono_literals;

bool singeThreaded() {
  auto task = [](int s) {
    sleep(std::chrono::seconds(s));
  };

  SingeThreadedExecutor<Task<int>> executor;

  auto beginTime = std::chrono::system_clock::now();

  executor.addTask({task, 1});
  executor.addTask({task, 1});

  executor.waitForAll();

  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time(singeThreaded): %f\n", time);

  return time < 2.0f;
}

bool multiThreaded() {
  auto task = [](int s) {
    sleep(std::chrono::seconds(s));
  };

  MultiThreadedExecutor<Task<int>> executor;

  auto beginTime = std::chrono::system_clock::now();

  executor.addTask({task, 1});
  executor.addTask({task, 1});

  executor.waitForAll();

  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time(multiThreaded): %f\n", time);

  return time > 1.2f;
}

bool delayedSingle() {
  auto task = []() {};

  DelayedExecutor executor;

  auto beginTime = std::chrono::system_clock::now();

  executor.addTask(1s, task);
  executor.addTask(1s, task);

  executor.waitForAll();

  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time(delayedSingle): %f\n", time);

  return time < 2.0f;
}

bool delayedMulti() {
  auto task = []() {};

  DelayedExecutor executor(2);

  auto beginTime = std::chrono::system_clock::now();

  executor.addTask(1s, task);
  executor.addTask(1s, task);

  executor.waitForAll();

  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time(delayedMulti): %f\n", time);

  return time > 1.2f;
}


bool intervalSingle() {
  Locked<int> counter1 = 5, counter2 = 1;

  auto task = []() {};

  IntervalExecutor executor;

  auto beginTime = std::chrono::system_clock::now();

  executor.addTask(200ms, [&counter1]() -> bool {
    counter1.set(counter1.get() * 2);
    return counter1.get() < 100;
  });

  executor.addTask(200ms, [&counter2]() -> bool {
    counter2.set(counter2.get() * 2);
    return counter2.get() < 100;
  });

  executor.waitForAll();

  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time(intervalSingle): %f\n", time);

  return time < 2.2f;
}

bool intervalMulti() {
  Locked<int> counter1 = 5, counter2 = 1;

  auto task = []() {};

  IntervalExecutor executor(2);

  auto beginTime = std::chrono::system_clock::now();

  executor.addTask(200ms, [&counter1]() -> bool {
    counter1.set(counter1.get() * 2);
    return counter1.get() < 100;
  });

  executor.addTask(200ms, [&counter2]() -> bool {
    counter2.set(counter2.get() * 2);
    return counter2.get() < 100;
  });

  executor.waitForAll();

  auto endTime = std::chrono::system_clock::now();

  float time = static_cast<std::chrono::duration<float>>(endTime - beginTime).count();

  printf("time(intervalMulti): %f\n", time);

  return time < 1.5f;
}

int main(int argc, char ** argv) {
  bool result = false;

  // TODO: Rework
  result &= !singeThreaded();
  result &= !multiThreaded();
  result &= !delayedSingle();
  result &= !delayedMulti();
  result &= !intervalSingle();
  result &= !intervalMulti();

  return result;
}
