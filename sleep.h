#ifdef _WIN32

#include <stdio.h>
#include <windows.h>

static void sleepSeconds(unsigned seconds) { Sleep(seconds * 1000U); }

#elif defined(__linux__)

#include <unistd.h>

static void sleepSeconds(unsigned seconds) { void(sleep)(seconds); }

#else
#error nL&nW
#endif
