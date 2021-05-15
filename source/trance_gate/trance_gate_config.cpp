// Copyright(c) 2021 Hansen Audio.

#include "trance_gate_config.h"
#include "ha/audio_modules/convert_funcs.h"
#include "ha/audio_modules/param_info.h"
#include "ha/audio_modules/types.h"
#include "ha/param_tool_box/convert/logarithmic.h"
#include "ha/param_tool_box/convert/percent.h"
#include "ha/param_tool_box/convert/string_list.h"

namespace ha {
namespace audio_modules {
namespace trance_gate {

//-----------------------------------------------------------------------------
// clang-format off
static constexpr std::array delay_fade_len_strings = {
    "Instant",
    "1/16",
    "1/8",
    "1/4",
    "1/2",
    "1",
    "2",
    "3",
    "4"
};

static constexpr std::array<real, delay_fade_len_strings.size()> const delay_fade_len_values = {
    0.,
    1. / 16.,
    1. / 8,
    1. / 4.,
    1. / 2.,
    1.,
    2.,
    3.,
    4
};

static_assert(delay_fade_len_strings.size() == delay_fade_len_values.size());

//-----------------------------------------------------------------------------
static constexpr std::array mono_mode_strings = {
    "Mono",
    "Stereo",
};

//-----------------------------------------------------------------------------
static constexpr std::array on_off_strings = {
    "Off",
    "On",
};

//-----------------------------------------------------------------------------
static constexpr std::array sync_mode_strings = {
    "Free", "Tempo", "Project",
};

//-----------------------------------------------------------------------------
// A speed value is the length of one step in seconds.
static std::array const speed_strings = {
    "1/128",  "1/64",  "1/32",  "1/16",  "1/8",  "1/4",  "1/2",  "1",
    "1/128T", "1/64T", "1/32T", "1/16T", "1/8T", "1/4T", "1/2T", "1T",
    "1/128D", "1/64D", "1/32D", "1/16D", "1/8D", "1/4D", "1/2D", "1D"
};

static constexpr real tri(real const x) { return x * (2. / 3.); }
static constexpr real dot(real const x) { return x * (3. / 2.); }
static constexpr std::array<real, speed_strings.size()> const speed_values = {
    1. / 128.,
    1. / 64.,
    1. / 32.,
    1. / 16.,
    1. / 8.,
    1. / 4.,
    1. / 2.,
    1.,
    tri(1. / 128.),
    tri(1. / 64.),
    tri(1. / 32.),
    tri(1. / 16.),
    tri(1. / 8.),
    tri(1. / 4.),
    tri(1. / 2.),
    tri(1.),
    dot(1. / 128.),
    dot(1. / 64.),
    dot(1. / 32.),
    dot(1. / 16.),
    dot(1. / 8.),
    dot(1. / 4.),
    dot(1. / 2.),
    dot(1.)
};

static_assert(speed_values.size() == speed_strings.size());

//-----------------------------------------------------------------------------
// clang-format on
using percent_type = ptb::convert::percent<mut_real>;
using log_type     = ptb::convert::logarithmic<mut_real>;
using lin_type     = ptb::convert::linear<mut_real>;
using speed_type = ptb::convert::string_list<mut_real, decltype(speed_strings)>;
using dly_fad_type =
    ptb::convert::string_list<mut_real, decltype(delay_fade_len_strings)>;
using mono_mode_type =
    ptb::convert::string_list<mut_real, decltype(mono_mode_strings)>;
using sync_mode_type =
    ptb::convert::string_list<mut_real, decltype(sync_mode_strings)>;
using on_off_type =
    ptb::convert::string_list<mut_real, decltype(on_off_strings)>;
using converter_list_type =
    std::array<const convert_funcs, config::convert_tags::count>;

static percent_type const percent_converter;
static log_type const contour_converter(4., 0.001, 0.25);
static speed_type const speed_converter(speed_strings);
static dly_fad_type const delay_fade_converter(delay_fade_len_strings);
static lin_type const step_count_converter(1, 32);
static mono_mode_type const mono_mode_converter(mono_mode_strings);
static on_off_type const on_off_converter(on_off_strings);
static sync_mode_type const sync_mode_converter(sync_mode_strings);

// clang-format off
static converter_list_type const convert_list = {{
    {   // convert_tags::normalised
        /*to_physical   = */ [](real norm) { return norm; },
        /*to_normalised = */ [](real phys) { return phys; },
        /*to_string     = */ [](real phys) { return std::to_string(phys); },
        /*from_string   = */ [](string string) { return std::stof (string); },
        /*num_steps     = */ []() -> i32   { return 0; }
    },
    {   // convert_tags::percent
        /*to_physical   = */ [](real norm) { return percent_converter.to_physical(norm); },
        /*to_normalised = */ [](real phys) { return percent_converter.to_normalized(phys); },
        /*to_string     = */ [](real phys) { 
                auto precisionFunc = [](auto value) -> i32 {
                return value < 100. ? 2 : 1;
            };
            return percent_converter.to_string(phys, precisionFunc); 
        },
        /*from_string   = */ [](string string) { return percent_converter.from_string(string); },
        /*num_steps     = */ []() -> i32   { return 0; }
    },
    {   // convert_tags::contour
        /*to_physical   = */ [](real norm) { return contour_converter.to_physical(norm); },
        /*to_normalised = */ [](real phys) { return contour_converter.to_normalized(phys); },
        /*to_string     = */ [](real phys) {
            auto precisionFunc = [](decltype(contour_converter)::value_type) -> i32 {
                return 3;
            };
            return contour_converter.to_string(phys, precisionFunc); 
        },
        /*from_string   = */ [](string string) { return contour_converter.from_string(string); },
        /*num_steps     = */ []() -> i32   { return 0; }
    },
    {   // convert_tags::speed
        /*to_physical   = */ [](real norm) { return speed_converter.to_physical(norm); },
        /*to_normalised = */ [](real phys) { return speed_converter.to_normalized(phys); },
        /*to_string     = */ [](real phys) { return speed_converter.to_string(phys); },
        /*from_string   = */ [](string string) { return speed_converter.from_string(string); },
        /*num_steps     = */ []() -> i32   { return speed_values.size() - 1; }
    },
    {   // convert_tags::delay_fade_length
        /*to_physical   = */ [](real norm) { return delay_fade_converter.to_physical(norm); },
        /*to_normalised = */ [](real phys) { return delay_fade_converter.to_normalized(phys); },
        /*to_string     = */ [](real phys) { return delay_fade_converter.to_string(phys); },
        /*from_string   = */ [](string string) { return delay_fade_converter.from_string(string); },
        /*num_steps     = */ []() -> i32   { return delay_fade_len_values.size() - 1; }
    },
    {   // convert_tags::step_count
        /*to_physical   = */ [](real norm) { return step_count_converter.to_physical(norm); },
        /*to_normalised = */ [](real phys) { return step_count_converter.to_normalized(phys); },
        /*to_string     = */ [](real phys) {
            using val_type = decltype(step_count_converter)::value_type;
            auto precisionFunc = [](val_type) -> i32 {
                return 0;
            };
            auto rounded = static_cast<val_type>(static_cast<i32>(phys));
            return step_count_converter.to_string(rounded, precisionFunc);
        },
        /*from_string   = */ [](string string) { return step_count_converter.from_string(string); },
        /*num_steps     = */ []() -> i32   { return step_count_converter.to_physical(1.)
                                                    - step_count_converter.to_physical(0.); }
    },
    {   // convert_tags::mono_stereo
        /*to_physical   = */ [](real norm) { return mono_mode_converter.to_physical(norm); },
        /*to_normalised = */ [](real phys) { return mono_mode_converter.to_normalized(phys); },
        /*to_string     = */ [](real phys) { return mono_mode_converter.to_string(phys); },
        /*from_string   = */ [](string string) { return mono_mode_converter.from_string(string); },
        /*num_steps     = */ []() -> i32   { return mono_mode_strings.size() - 1; }
    },
    {   // convert_tags::sync_mode
        /*to_physical   = */ [](real norm) { return sync_mode_converter.to_physical(norm); },
        /*to_normalised = */ [](real phys) { return sync_mode_converter.to_normalized(phys); },
        /*to_string     = */ [](real phys) { return sync_mode_converter.to_string(phys); },
        /*from_string   = */ [](string string) { return sync_mode_converter.from_string(string); },
        /*num_steps     = */ []() -> i32   { return sync_mode_strings.size() - 1; }
    }
}};
// clang-format on

static_assert(convert_list.size() == config::convert_tags::count);

//-----------------------------------------------------------------------------
convert_funcs const& config::get_convert_functions(tag_type convert_tag)
{
    return convert_list.at(convert_tag);
}

//-----------------------------------------------------------------------------
real config::get_speed(real value)
{
    size_t const index = static_cast<size_t>(value);
    return speed_values.at(index);
}

//-----------------------------------------------------------------------------
real config::get_delay_fade_len(real value)
{
    size_t const index = static_cast<size_t>(value);
    return delay_fade_len_values.at(index);
}

//-----------------------------------------------------------------------------
} // namespace trance_gate
} // namespace audio_modules
} // namespace ha