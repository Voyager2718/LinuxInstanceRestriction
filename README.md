# Summary
This library restricts instance quantity on *nix system.

# Compatibility
## OS
- Linux
- Unix
- OS X Darwin Kernel Version 16.7.0

## Compiler
- Apple LLVM version 8.1.0 (clang-802.0.42)
- gcc
- g++

## Programming language
- C
- C++

# Usage
```C
#include "instance_restriction.h"

int main()
{
    if (ReachedMaximumInstance())
    {
        perror("Too many instances.");
    }

    return EXIT_SUCCESS;
}
```

# Mechanism
This library will create lock file `LOCK_PREFIX` + count + `LOCK_SUFFIX` and put current pid in it once it runs.
(Defined in *instance_restriction.h*)

When try to run another process, `ReachedMaximumInstance` will check the existence of lock file. If lock file exists already,
it will check if pid logged in lock file is still running. If process is still running, it will check if has exceeded 
`MAX_INSTANCE`. If it has, then it will return 1. Otherwise, it will remove deprecated lock and create a new lock and return 0.

# License
GPL v2.0
