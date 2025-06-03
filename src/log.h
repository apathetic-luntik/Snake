#ifndef LOG_H
#define LOG_H

#include "iostream"
#include "mutex"

struct Logimpl;

class Log {
public:
    Log();
    size_t &get();
    // API взаимодействия

private:
    static Logimpl &impl();
    Logimpl &impl_;
};

#endif // LOG_H
