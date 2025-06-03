#include "log.h"

struct Logimpl {
    Logimpl() : error_count_(0) {}
    size_t error_count_;
    std::mutex lock_;
};

inline Log::Log() : impl_(impl()) {}

inline size_t &Log::get()
{
    return impl_.error_count_;
}

inline Logimpl &Log::impl()
{
    static Logimpl instance_;
    return instance_;
}
