// Copyright(c) 2021 Hansen Audio.

#include <cstdlib>

/**
 * @brief Detect memory allocations in a thread.
 */
struct thread_malloc_detector final
{
    thread_malloc_detector();
    ~thread_malloc_detector();

    bool was_detected() const;
};
