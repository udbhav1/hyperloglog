#ifndef MEMORY_H
#define MEMORY_H

#ifdef __linux__

#include <sys/resource.h>

#elif __APPLE__

#include <mach/mach.h>

#endif

long long bytesUsed();

#endif
