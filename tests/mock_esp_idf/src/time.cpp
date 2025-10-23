#include "../include/sys/time.h"

#include "../include/mcu.hpp"

int gettimeofday(struct timeval *__restrict __tv, void *__restrict __tz)
{
    uint64_t time_in_ms = mock_mcu.get_time();
    __tv->tv_sec = time_in_ms / 1000;
    __tv->tv_usec = (time_in_ms % 1000) * 1000;
    return 0;
}

int settimeofday(const struct timeval *__tv, const struct timezone *__tz)
{
    mock_mcu.set_time((uint64_t)__tv->tv_sec * 1000 +
                      (uint64_t)__tv->tv_usec / 1000);
    return 0;
}