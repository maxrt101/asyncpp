#ifndef _ASYNCPP_PROCESS_H_
#define _ASYNCPP_PROCESS_H_ 1

#include <memory>
#include <unistd.h>
#include <sys/wait.h>

#include <asyncpp/async.h>
#include <asyncpp/lock.h>

namespace asyncpp {

struct Process {
 public:
  enum ProcessStatus {
    NOT_STARTED,
    RUNNING,
    FINISHED
  };

 private:
  pid_t pid = -1;
  int exitCode = -1;
  ProcessStatus status = NOT_STARTED;
  mutable Lock lock;

 public:
  inline Process() = default;
  inline ~Process() = default;

  inline pid_t getPid() const {
    return pid;
  }

  inline int getExitCode() const {
    auto sl = lock.lockScope();
    return exitCode;
  }

  inline bool running() const {
    return status == RUNNING;
  }

  inline bool finished() const {
    return status == FINISHED;
  }

  inline void wait() {
    int processStatus = 0, processCode = 0;
    waitpid(pid, &processStatus, 0);

    if (WIFEXITED(status)) {
      processCode = WEXITSTATUS(processStatus);
    }

    auto sl = lock.lockScope();
    exitCode = processCode;
    status = FINISHED;
  }

  inline std::unique_ptr<Process> toUnique() {
    return std::unique_ptr<Process>(this);
  }

  template <typename T, typename... Args>
  inline static Process* launch(T task, Args... args) {
    Process* ctx = new Process;

    ctx->pid = fork();
    if (ctx->pid == 0) {
      task(args...);
      exit(0);
    }

    return ctx;
  }

  template <typename T, typename... Args>
  inline static Process* launchSync(T task, Args... args) {
    Process* ctx = launch(task, args...);

    ctx->wait();

    return ctx;
  }

  template <typename T, typename... Args>
  inline static Process* launchAsync(T task, Args... args) {
    Process* ctx = launch(task, args...);

    async([ctx]() {
      ctx->wait();
    });

    return ctx;
  }
};

} /* namespace asyncpp */

#endif /* _ASYNCPP_PROCESS_H_ */