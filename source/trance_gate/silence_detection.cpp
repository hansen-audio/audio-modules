// Copyright(c) 2021 Hansen Audio.

#include "silence_detection.h"
#include <cmath>

namespace ha {
namespace audio_modules {
namespace trance_gate {

//-----------------------------------------------------------------------------
silence_detection::context silence_detection::create(real sample_rate, real duration_in_seconds)
{
    context ctx{sample_rate * duration_in_seconds};
    return ctx;
}

//-----------------------------------------------------------------------------
bool silence_detection::process(context& ctx, fx_collection::audio_frame const& frame)
{
    using value_type         = decltype(fx_collection::audio_frame::data)::value_type;
    constexpr auto THRESHOLD = 1e-22f;

    value_type sum = 0.;
    for (const auto& sample : frame.data)
    {
        value_type const abs_value = std::abs(value_type(sample));
        sum += abs_value;
    }

    if (sum < THRESHOLD)
        ctx.sample_count += 1;
    else
        ctx.sample_count = 0;

    auto const duration_exceeded = ctx.sample_count > ctx.duration_in_samples;
    return duration_exceeded;
}

//-----------------------------------------------------------------------------
} // namespace trance_gate
} // namespace audio_modules
} // namespace ha