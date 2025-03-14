// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/aligned_allocator/allocator.h"
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace hao::audio_modules {

//------------------------------------------------------------------------
using i32     = std::int32_t const;
using mut_i32 = std::remove_const<i32>::type;

using i64     = std::int32_t const;
using mut_i64 = std::remove_const<i64>::type;

using real     = float const;
using mut_real = std::remove_const<real>::type;

using tag_type     = i32;
using mut_tag_type = mut_i32;

using f64     = double const;
using mut_f64 = std::remove_const<f64>::type;

using string_view = std::string_view const;

using string = std::string const;

using ParamInfosList   = std::vector<struct ParamInfo>;
using ConvertFuncsList = std::vector<struct ConverterFuncs>;

using sample = mut_real;

using allocator_r16 = ha::alignment::aligned_allocator<sample, 16>;
using AudioChannel  = std::vector<sample, allocator_r16>;
using AudioBus      = std::vector<AudioChannel>;
using AudioBusses   = std::vector<AudioBus>;

//------------------------------------------------------------------------
} // namespace hao::audio_modules
