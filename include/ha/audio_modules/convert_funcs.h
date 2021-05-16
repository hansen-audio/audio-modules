// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/audio_modules/types.h"
#include <functional>

namespace ha::audio_modules {

//-----------------------------------------------------------------------------
/**
 * convert_funcs
 */
struct convert_funcs
{
    using to_physical_func   = std::function<real(real)>;
    using to_string_func     = std::function<string(real)>;
    using to_normalised_func = std::function<real(real)>;
    using from_string_func   = std::function<real(string)>;
    using num_steps_func     = std::function<i32()>;

    to_physical_func to_physical;
    to_normalised_func to_normalised;
    to_string_func to_string;
    from_string_func from_string;
    num_steps_func num_steps;
};

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules