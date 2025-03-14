// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "hao/audio_modules/types.h"
#include "ha/fx_collection/types.h"

namespace ha::audio_modules::trance_gate {

/**
 * @brief SilenceDetection
 *
 */
struct SilenceDetection
{
    mut_real duration_in_samples = 44100.;
    mut_i32 frames_of_silence    = 0;
};

/**
 * @brief Detecting silence
 *
 */
struct SilenceDetectionImpl final
{
    using Self = SilenceDetection;

    static Self create(real sample_rate, real duration_in_seconds);
    static bool process(Self& silence_detection,
                        fx_collection::AudioFrame const& frame);
};

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules::trance_gate