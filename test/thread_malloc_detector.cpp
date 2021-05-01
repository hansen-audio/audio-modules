// Copyright(c) 2021 Hansen Audio.

#include "thread_malloc_detector.h"
#include <cassert>
#include <cstdlib>

//------------------------------------------------------------------------
static thread_local bool enabled   = false;
static thread_local bool allocated = false;

//------------------------------------------------------------------------
void* operator new(size_t size)
{
    allocated = true;

    return malloc(size);
}

//------------------------------------------------------------------------
thread_malloc_detector::thread_malloc_detector()
{
    assert((enabled == false) && "Multiple thread_malloc_detectors instances in the same thread!");

    enabled   = true;
    allocated = false;
}

//------------------------------------------------------------------------
thread_malloc_detector::~thread_malloc_detector()
{
    enabled   = false;
    allocated = false; // reset value
}

//------------------------------------------------------------------------
bool thread_malloc_detector::was_detected() const
{
    return allocated;
}
