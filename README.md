# Async CPP
Some utilities for async programming in C++ that I use.  
Built on top of standard concurrency support headers (`thread`, `atomic`, `condition_variable`, etc).  
The main rationale behind this library (aside from just collecting everything that I have ever written on multithreading) is the ease of use.  
Standard library is often cryptic, and while it allows for far greater configuration, if you haven't used it for some time - you will surely need to look into the docs.  
Asyncpp, on the other hand, aims to be straightforward and easy to use.  


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
 - Custom Future
 - Lock (also provides scoped lock)
 - Locked (couples resource and a lock)
 - Multiprocessing heplers (`launch`/`launchSync`/`launchAsync` functions)
 - Convinience functions such as `sleep`
