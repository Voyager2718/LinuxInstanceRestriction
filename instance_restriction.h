/**
  * Original address: https://github.com/Voyager2718/LinuxInstanceRestriction
  * License: GPL v2.0
  */

#ifndef INSTANCE_RESTRICTION
#define INSTANCE_RESTRICTION

#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

#define MAX_INSTANCE 2
#define MAX_INSTANCE_DIGITS 10
#define LOCK_PREFIX "/tmp/instance"
#define LOCK_SUFFIX ".lock"

bool ReachedMaximumInstance();

#endif
