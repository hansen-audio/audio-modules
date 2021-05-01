// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/aligned_allocator/allocator.h"
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace ha {
namespace audio_modules {

//------------------------------------------------------------------------
using i32     = std::int32_t const;
using mut_i32 = std::remove_const<i32>::type;

using i64     = std::int32_t const;
using mut_i64 = std::remove_const<i64>::type;

using real     = float const;
using mut_real = std::remove_const<real>::type;

using tag_param     = i32;
using mut_tag_param = mut_i32;

using tag_convert     = i32;
using mut_tag_convert = mut_i32;

using string_view = std::string_view const;

using string = std::string const;

using param_infos_list   = std::vector<struct param_info>;
using convert_funcs_list = std::vector<struct convert_funcs>;

using sample  = mut_real;
using tag_pin = i32;

using allocator_r16 = alignment::aligned_allocator<sample, 16>;
using audio_channel = std::vector<sample, allocator_r16>;
using audio_bus     = std::vector<audio_channel>;
using audio_busses  = std::vector<audio_bus>;

//------------------------------------------------------------------------
} // namespace audio_modules
} // namespace ha
