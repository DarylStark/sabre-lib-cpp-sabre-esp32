#ifndef MOCK_ESP_IDF_SYS_TIME_H
#define MOCK_ESP_IDF_SYS_TIME_H

int gettimeofday(struct timeval *__restrict __tv, void *__restrict __tz);
int settimeofday(const struct timeval *__tv, const struct timezone *__tz);

#endif