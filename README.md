# Async CPP
Some utilities for async programming in C++ that I use.  
Built on top of standard multithreading libraries (`thread`, `atomic`, `condition_variable`, etc).  


## How to install
Prerequisites: `gcc`/`clang`, `make`  
Steps:  
 - Clone the repo  
 - Run `make PREFIX=/path/to/installation/dir`  

The headers will be installed into `/path/to/installation/dir/include/asyncpp`


## Features
 - Simple `async`/`await` (async returns future, await blocks until the future is ready)
 - Thread Pool with templated Task class
 - Configurable Executors
    - Delayed (Timer)
    - Interval
    - Single threaded 
    - Multi threaded 
 - Futures
 - Locks
 - Locked (couples resource and a lock)
 - Convinience functions such as sleep()
