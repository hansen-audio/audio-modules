// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/audio_modules/types.h"
#include "ha/fx_collection/types.h"

namespace ha::audio_modules::trance_gate {

/**
 * @brief Detecting silence
 *
 */
struct silence_detection final
{
    struct context
    {
        mut_real duration_in_samples = 44100.;
        mut_i32 frames_of_silence    = 0;
    };

    static context create(real sample_rate, real duration_in_seconds);
    static bool process(context& ctx, fx_collection::audio_frame const& frame);
};

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules::trance_gate