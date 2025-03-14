// Copyright(c) 2021 Hansen Audio.

#include "silence_detection.h"
#include <cmath>
#include <cstddef>

namespace hao::audio_modules::trance_gate {

//-----------------------------------------------------------------------------
SilenceDetection SilenceDetectionImpl::create(real sample_rate,
                                              real duration_in_seconds)
{
    SilenceDetection silence_detection{sample_rate * duration_in_seconds};
    return silence_detection;
}

//-----------------------------------------------------------------------------
bool SilenceDetectionImpl::process(Self& self,
                                   ha::fx_collection::AudioFrame const& frame)
{
    constexpr auto THRESHOLD = 1e-9f;

    // Increment the silence counter...
    self.frames_of_silence++;

    ha::fx_collection::AudioFrame sum{real(0.)};
    for (std::size_t s = 0; s < frame.data.size(); ++s)
    {
        sum.data[s] += std::abs(frame.data[s]);
        if (sum.data[s] >= THRESHOLD)
        {
            //...but set it back to zero when there is noise.
            self.frames_of_silence = 0;
            break;
        }
    }

    // When the counter reaches the duration specified, it is silent.
    return self.frames_of_silence > self.duration_in_samples;
}

//-----------------------------------------------------------------------------
} // namespace hao::audio_modules::trance_gate
