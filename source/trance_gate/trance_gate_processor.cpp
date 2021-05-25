// Copyright(c) 2021 Hansen Audio.

#include "trance_gate_processor.h"
#include "ha/audio_modules/convert_funcs.h"
#include "trance_gate_config.h"
#include <cassert>

namespace ha::audio_modules::trance_gate {
namespace {

//-----------------------------------------------------------------------------
using fx_tg = fx_collection::trance_gate;

//-----------------------------------------------------------------------------
template <typename Func>
void update_parameter(param_change const& param,
                      fx_collection::trance_gate::context& tg_cx,
                      const Func& func)
{
    using cfg  = trance_gate::config;
    using tags = cfg::param_tags;

    switch (param.tag)
    {
        case tags::step_le_01:
        case tags::step_le_02:
        case tags::step_le_03:
        case tags::step_le_04:
        case tags::step_le_05:
        case tags::step_le_06:
        case tags::step_le_07:
        case tags::step_le_08:
        case tags::step_le_09:
        case tags::step_le_10:
        case tags::step_le_11:
        case tags::step_le_12:
        case tags::step_le_13:
        case tags::step_le_14:
        case tags::step_le_15:
        case tags::step_le_16:
        case tags::step_le_17:
        case tags::step_le_18:
        case tags::step_le_19:
        case tags::step_le_20:
        case tags::step_le_21:
        case tags::step_le_22:
        case tags::step_le_23:
        case tags::step_le_24:
        case tags::step_le_25:
        case tags::step_le_26:
        case tags::step_le_27:
        case tags::step_le_28:
        case tags::step_le_29:
        case tags::step_le_30:
        case tags::step_le_31:
        case tags::step_le_32: {
            constexpr i32 LEFT_CH_IDX = 0;

            const auto tag = param.tag - tags::step_le_01;
            fx_tg::set_step(tg_cx, LEFT_CH_IDX, tag, param.value);
            break;
        }
        case tags::step_ri_01:
        case tags::step_ri_02:
        case tags::step_ri_03:
        case tags::step_ri_04:
        case tags::step_ri_05:
        case tags::step_ri_06:
        case tags::step_ri_07:
        case tags::step_ri_08:
        case tags::step_ri_09:
        case tags::step_ri_10:
        case tags::step_ri_11:
        case tags::step_ri_12:
        case tags::step_ri_13:
        case tags::step_ri_14:
        case tags::step_ri_15:
        case tags::step_ri_16:
        case tags::step_ri_17:
        case tags::step_ri_18:
        case tags::step_ri_19:
        case tags::step_ri_20:
        case tags::step_ri_21:
        case tags::step_ri_22:
        case tags::step_ri_23:
        case tags::step_ri_24:
        case tags::step_ri_25:
        case tags::step_ri_26:
        case tags::step_ri_27:
        case tags::step_ri_28:
        case tags::step_ri_29:
        case tags::step_ri_30:
        case tags::step_ri_31:
        case tags::step_ri_32: {
            constexpr i32 RIGHT_CH_IDX = 1;

            const auto tag = param.tag - tags::step_ri_01;
            fx_tg::set_step(tg_cx, RIGHT_CH_IDX, tag, param.value);
            break;
        }
        case tags::amount: {
            fx_tg::set_mix(tg_cx, param.value);
            break;
        }
        case tags::contour: {
            static auto constexpr info = cfg::param_list.at(tags::contour);
            static auto const& conv_funcs =
                cfg::get_convert_functions(info.convert_tag);

            fx_tg::set_contour(tg_cx, conv_funcs.to_physical(param.value));
            break;
        }
        case tags::speed: {
            static auto constexpr info = cfg::param_list.at(tags::speed);
            static auto const& conv_funcs =
                cfg::get_convert_functions(info.convert_tag);

            auto const step_len =
                cfg::get_speed(conv_funcs.to_physical(param.value));

            fx_tg::set_step_len(tg_cx, step_len);
            break;
        }
        case tags::step_count: {
            static auto constexpr info = cfg::param_list.at(tags::step_count);
            static auto const& conv_funcs =
                cfg::get_convert_functions(info.convert_tag);

            fx_tg::set_step_count(tg_cx, conv_funcs.to_physical(param.value));
            break;
        }
        case tags::mode: {
            fx_tg::set_stereo_mode(tg_cx, param.value > 0.5 ? true : false);
            break;
        }
        case tags::width: {
            fx_tg::set_width(tg_cx, param.value);
            break;
        }
        case tags::shuffle: {
            fx_tg::set_shuffle_amount(tg_cx, param.value);
            break;
        }
        case tags::fade_in: {
            static auto constexpr info = cfg::param_list.at(tags::fade_in);
            static auto const& conv_funcs =
                cfg::get_convert_functions(info.convert_tag);

            real val =
                cfg::get_delay_fade_len(conv_funcs.to_physical(param.value));

            func(param.tag, val);
            break;
        }
        case tags::delay: {
            static auto constexpr info = cfg::param_list.at(tags::delay);
            static auto const& conv_funcs =
                cfg::get_convert_functions(info.convert_tag);
            real val =
                cfg::get_delay_fade_len(conv_funcs.to_physical(param.value));

            func(param.tag, val);
            break;
        }
        default:
            assert(true);
    }
}

//-----------------------------------------------------------------------------
template <typename Func>
void update_parameters(process_data::param_changes const& param_ins,
                       fx_collection::trance_gate::context& tg_cx,
                       const Func& func)
{
    for (const auto& pin : param_ins)
    {
        update_parameter(pin, tg_cx, func);
    }
}

//-----------------------------------------------------------------------------
bool is_silent_input(process_data& data, silence_detection::context& sd_cx)
{
    using audio_frame = fx_collection::audio_frame;

    audio_frame frame = fx_collection::zero_audio_frame;
    bool is_silent    = false;
    for (mut_i32 s = 0; s < data.num_samples; ++s)
    {
        frame.data[0] = data.inputs[0][0][s];
        frame.data[1] = data.inputs[0][1][s];

        is_silent = silence_detection::process(sd_cx, frame);
    }

    return is_silent;
}

//-----------------------------------------------------------------------------
void output_step_pos_param(fx_collection::trance_gate::context& cx,
                           process_data& data)
{
    using cfg  = trance_gate::config;
    using tags = cfg::param_tags;

    static auto constexpr info = cfg::param_list.at(tags::step_count);
    static auto const& conv_funcs =
        cfg::get_convert_functions(info.convert_tag);

    i32 index       = cx.step_val.pos + 1; // non programming index!
    real norm_index = conv_funcs.to_normalised(index);
    data.param_outputs.push_back({tags::step_pos, norm_index});
}

//-----------------------------------------------------------------------------
void process_audio_buffers(fx_collection::trance_gate::context& cx,
                           process_data& data)
{
    using audio_frame = fx_collection::audio_frame;
    constexpr i32 L   = 0;
    constexpr i32 R   = 1;

    audio_frame frame = fx_collection::zero_audio_frame;
    for (mut_i32 s = 0; s < data.num_samples; ++s)
    {
        frame.data[L] = data.inputs[0][L][s];
        frame.data[R] = data.inputs[0][R][s];
        fx_tg::process(cx, frame, frame);
        data.outputs[0][L][s] = frame.data[L];
        data.outputs[0][R][s] = frame.data[R];
    }

    output_step_pos_param(cx, data);
}

//-----------------------------------------------------------------------------
real compute_project_time_anchor(real project_time_music)
{
    if (project_time_music < real(0.))
    {
        real ptm       = abs(project_time_music);
        real remainder = fmod(ptm, real(1.));
        return remainder;
    }
    else
    {
        real ptm       = project_time_music;
        real remainder = fmod(ptm, real(1.));
        return real(1.) - remainder;
    }
}

//-----------------------------------------------------------------------------
} // namespace

/**
 * tg_processor
 */
tg_processor::tg_processor()
{
    for (param_info const& info : config::param_list)
    {
        // clang-format off
        update_parameter(
            {info.param_tag, info.default_normalised},
            cx.fx_trance_gate_cx, 
            [this](tag_type param_tag, real value) {
                update_param(param_tag, value);
            });
        // clang-format on
    }
}

//-----------------------------------------------------------------------------
bool tg_processor::process_audio(process_data& data)
{
    using audio_frame = fx_collection::audio_frame;

    update_parameters(data.param_inputs,
                      cx.fx_trance_gate_cx,
                      [this](tag_type param_tag, real value) {
                          update_param(param_tag, value);
                      });

    if (data.inputs.size() == 0 || data.outputs.size() == 0)
        return true;

    if (is_silent_input(data, cx.silence_detection_cx))
    {
        if (!cx.needs_trigger)
        {
            cx.fx_trance_gate_cx.step_val.pos = 0;
            output_step_pos_param(cx.fx_trance_gate_cx, data);
        }

        cx.needs_trigger = true;
        return true;
    }

    if (cx.needs_trigger)
    {
        cx.needs_trigger = false;
        fx_tg::trigger(cx.fx_trance_gate_cx, cx.delay_len, cx.fade_in_len);

        cx.trigger_phase = compute_project_time_anchor(data.project_time_music);
    }

    fx_tg::set_tempo(cx.fx_trance_gate_cx, data.tempo);

    real ptm = data.project_time_music + cx.trigger_phase;
    fx_tg::update_project_time_music(cx.fx_trance_gate_cx, ptm);

    process_audio_buffers(cx.fx_trance_gate_cx, data);

    return true;
}

//-----------------------------------------------------------------------------
void tg_processor::setup_processing(process_setup& setup)
{
    fx_tg::set_sample_rate(cx.fx_trance_gate_cx, setup.sample_rate);

    constexpr real RETRIGGER_TIMER = 0.5;
    cx.silence_detection_cx =
        silence_detection::create(setup.sample_rate, RETRIGGER_TIMER);
}

//-----------------------------------------------------------------------------
void tg_processor::update_param(tag_type param_tag, real value)
{
    using tags = config::param_tags;
    switch (param_tag)
    {
        case tags::fade_in:
            cx.fade_in_len = value;
            break;
        case tags::delay:
            cx.delay_len = value;
            break;
        default:
            break;
    }
}

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules::trance_gate