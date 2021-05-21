// Copyright(c) 2021 Hansen Audio.

#include "silence_detection.h"
#include <cmath>

namespace ha::audio_modules::trance_gate {

//-----------------------------------------------------------------------------
silence_detection::context silence_detection::create(real sample_rate,
                                                     real duration_in_seconds)
{
    context ctx{sample_rate * duration_in_seconds};
    return ctx;
}

//-----------------------------------------------------------------------------
bool silence_detection::process(context& ctx,
                                fx_collection::audio_frame const& frame)
{
    using value_type = decltype(fx_collection::audio_frame::data)::value_type;
    constexpr auto THRESHOLD = 1e-9f;

    // Increment the silence counter...
    ctx.frames_of_silence++;

    fx_collection::audio_frame sum{real(0.)};
    for (mut_i32 s = 0; s < frame.data.size(); ++s)
    {
        sum.data[s] += std::abs(frame.data[s]);
        if (sum.data[s] >= THRESHOLD)
        {
            //...but set it back to zero when there is noise.
            ctx.frames_of_silence = 0;
            break;
        }
    }

    // When the counter reaches the duration specified, it is silent.
    return ctx.frames_of_silence > ctx.duration_in_samples;
}

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules::trance_gate
