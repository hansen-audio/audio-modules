// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "hao/audio_modules/types.h"

namespace hao::audio_modules {

//-----------------------------------------------------------------------------
/**
 * param_info
 */
struct ParamInfo
{
    static constexpr tag_type INVALID_PARAM_TAG   = -1;
    static constexpr tag_type INVALID_CONVERT_TAG = -1;

    string_view name;
    string_view short_name;
    string_view units;
    tag_type param_tag      = INVALID_PARAM_TAG;
    real default_normalised = 0.;
    tag_type convert_tag    = INVALID_CONVERT_TAG;
    bool is_read_only       = false;
};

//-----------------------------------------------------------------------------
} // namespace hao::audio_modules