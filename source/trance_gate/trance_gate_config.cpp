// Copyright(c) 2021 Hansen Audio.

#include "trance_gate_config.h"
#include "ha/audio_modules/convert_funcs.h"
#include "ha/audio_modules/param_info.h"
#include "ha/audio_modules/types.h"
#include "hao/param-tool-box-rs/cbindings.h"
#include <algorithm>
#include <memory>

namespace ha::audio_modules::trance_gate {

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

using converter_list_type =
    std::array<const ConverterFuncs, Config::ConvertTags::count>;

#define PARAM_TOOL_BOX_RS 1

// clang-format off
using namespace hao;
namespace ptb_rs = param_tool_box_rs;

struct ConverterDeleter {
    void operator()(ptb_rs::Converter* c) 
    { 
        ptb_rs::delete_converter(c);
    }
};

using ConverterPtr = std::unique_ptr<ptb_rs::Converter, ConverterDeleter>;

static ConverterPtr percent_rs (ptb_rs::new_linear(0., 100., false));
static ConverterPtr contour_rs (ptb_rs::new_log(4., 0.001, 0.25));
static ConverterPtr speed_rs (ptb_rs::new_list(speed_strings.size()));
static ConverterPtr delay_fade_rs(ptb_rs::new_list(delay_fade_len_values.size()));
static ConverterPtr step_count_rs (ptb_rs::new_linear(2., 32., true));
static ConverterPtr mono_mode_rs (ptb_rs::new_list(mono_mode_strings.size()));
static ConverterPtr sync_mode_rs (ptb_rs::new_list(sync_mode_strings.size()));
static ConverterPtr step_pos_rs (ptb_rs::new_linear(1., 32., true));

static std::string display_string(ptb_rs::Converter* converter, real phys, i32 precision) {
    static std::string output;

    ptb_rs::to_string(converter, phys, precision, [](const char *s){
        output.assign((const char*)s);
    });

    return output;
}

template <typename TStringList>
static std::string from_string_list(const TStringList& string_list, real phys) {
    auto i = static_cast<size_t>(phys);
    i = std::clamp(i, size_t(0), string_list.size() - 1);
    return string_list[i];
}

static converter_list_type const convert_list = {{
    {   // ConvertTags::normalised
        /*to_physical   = */ [](real norm) { return norm; },
        /*to_normalised = */ [](real phys) { return phys; },
        /*to_string     = */ [](real phys) { return std::to_string(phys); },
        /*from_string   = */ [](string s)  { return std::stof (s); },
        /*num_steps     = */ []() -> i32   { return 0; }
    },
    {   // ConvertTags::percent
        /*to_physical   = */ [](real norm) { return ptb_rs::to_physical(percent_rs.get(), norm); },
        /*to_normalised = */ [](real phys) { return ptb_rs::to_normalized(percent_rs.get(), phys); },
        /*to_string     = */ [](real phys) { return display_string(percent_rs.get(), phys, phys < 100. ? 2 : 1); },
        /*from_string   = */ [](string s)  { return ptb_rs::from_string(percent_rs.get(), s.data()); },
        /*num_steps     = */ []() -> i32   { return ptb_rs::num_steps(percent_rs.get()); }
    },
    {   // ConvertTags::contour
        /*to_physical   = */ [](real norm) { return ptb_rs::to_physical(contour_rs.get(), norm); },
        /*to_normalised = */ [](real phys) { return ptb_rs::to_normalized(contour_rs.get(), phys); },
        /*to_string     = */ [](real phys) { return display_string(contour_rs.get(), phys, 3); },
        /*from_string   = */ [](string s)  { return ptb_rs::from_string(contour_rs.get(), s.data()); },
        /*num_steps     = */ []() -> i32   { return ptb_rs::num_steps(contour_rs.get()); }
    },
    {   // ConvertTags::speed
        /*to_physical   = */ [](real norm) { return ptb_rs::to_physical(speed_rs.get(), norm); },
        /*to_normalised = */ [](real phys) { return ptb_rs::to_normalized(speed_rs.get(), phys); },
        /*to_string     = */ [](real phys) { return from_string_list(speed_strings, phys); },
        /*from_string   = */ [](string s)  { return ptb_rs::from_string(speed_rs.get(), s.data()); },
        /*num_steps     = */ []() -> i32   { return ptb_rs::num_steps(speed_rs.get()); }
    },
    {   // ConvertTags::delay_fade_length
        /*to_physical   = */ [](real norm) { return ptb_rs::to_physical(delay_fade_rs.get(), norm); },
        /*to_normalised = */ [](real phys) { return ptb_rs::to_normalized(delay_fade_rs.get(), phys); },
        /*to_string     = */ [](real phys) { return from_string_list(delay_fade_len_strings, phys); },
        /*from_string   = */ [](string s)  { return ptb_rs::from_string(delay_fade_rs.get(), s.data()); },
        /*num_steps     = */ []() -> i32   { return ptb_rs::num_steps(delay_fade_rs.get()); }
    },
    {   // ConvertTags::step_count
        /*to_physical   = */ [](real norm) { return ptb_rs::to_physical(step_count_rs.get(), norm); },
        /*to_normalised = */ [](real phys) { return ptb_rs::to_normalized(step_count_rs.get(), phys); },
        /*to_string     = */ [](real phys) { return display_string(step_count_rs.get(), phys, 0); },
        /*from_string   = */ [](string s)  { return ptb_rs::from_string(step_count_rs.get(), s.data()); },
        /*num_steps     = */ []() -> i32   { return ptb_rs::num_steps(step_count_rs.get());; }
    },
    {   // ConvertTags::mono_stereo
        /*to_physical   = */ [](real norm) { return ptb_rs::to_physical(mono_mode_rs.get(), norm); },
        /*to_normalised = */ [](real phys) { return ptb_rs::to_normalized(mono_mode_rs.get(), phys); },
        /*to_string     = */ [](real phys) { return from_string_list(mono_mode_strings, phys); },
        /*from_string   = */ [](string s)  { return ptb_rs::from_string(mono_mode_rs.get(), s.data()); },
        /*num_steps     = */ []() -> i32   { return ptb_rs::num_steps(mono_mode_rs.get()); }
    },
    {   // ConvertTags::sync_mode
        /*to_physical   = */ [](real norm) { return ptb_rs::to_physical(sync_mode_rs.get(), norm); },
        /*to_normalised = */ [](real phys) { return ptb_rs::to_normalized(sync_mode_rs.get(), phys); },
        /*to_string     = */ [](real phys) { return from_string_list(sync_mode_strings, phys); },
        /*from_string   = */ [](string s)  { return ptb_rs::from_string(sync_mode_rs.get(), s.data()); },
        /*num_steps     = */ []() -> i32   { return ptb_rs::num_steps(sync_mode_rs.get()); }
    },
    {   // ConvertTags::step_pos
        /*to_physical   = */ [](real norm) { return ptb_rs::to_physical(step_pos_rs.get(), norm); },
        /*to_normalised = */ [](real phys) { return ptb_rs::to_normalized(step_pos_rs.get(), phys); },
        /*to_string     = */ [](real phys) { return display_string(step_pos_rs.get(), phys, 0); },
        /*from_string   = */ [](string s)  { return ptb_rs::from_string(step_pos_rs.get(), s.data()); },
        /*num_steps     = */ []() -> i32   { return ptb_rs::num_steps(step_pos_rs.get()); }
    },
}};
// clang-format on

static_assert(convert_list.size() == Config::ConvertTags::count);

//-----------------------------------------------------------------------------
ConverterFuncs const& Config::get_convert_functions(tag_type convert_tag)
{
    return convert_list.at(convert_tag);
}

//-----------------------------------------------------------------------------
real Config::get_speed(real value)
{
    size_t const index = static_cast<size_t>(value);
    return speed_values.at(index);
}

//-----------------------------------------------------------------------------
real Config::get_delay_fade_len(real value)
{
    size_t const index = static_cast<size_t>(value);
    return delay_fade_len_values.at(index);
}

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules::trance_gate