// Copyright(c) 2021 Hansen Audio.

#include "trance_gate_processor.h"
#include "ha/audio_modules/convert_funcs.h"
#include "trance_gate_config.h"
#include <cassert>

namespace ha::audio_modules::trance_gate {
namespace {

//-----------------------------------------------------------------------------
template <typename Func>
void update_parameter(param_change const& param,
                      fx_collection::trance_gate::context& trance_gate_cx,
                      const Func& func)
{
    using tg_config = trance_gate::config;
    using tg        = fx_collection::trance_gate;

    switch (param.tag)
    {
        case tg_config::param_tags::step_le_01:
        case tg_config::param_tags::step_le_02:
        case tg_config::param_tags::step_le_03:
        case tg_config::param_tags::step_le_04:
        case tg_config::param_tags::step_le_05:
        case tg_config::param_tags::step_le_06:
        case tg_config::param_tags::step_le_07:
        case tg_config::param_tags::step_le_08:
        case tg_config::param_tags::step_le_09:
        case tg_config::param_tags::step_le_10:
        case tg_config::param_tags::step_le_11:
        case tg_config::param_tags::step_le_12:
        case tg_config::param_tags::step_le_13:
        case tg_config::param_tags::step_le_14:
        case tg_config::param_tags::step_le_15:
        case tg_config::param_tags::step_le_16:
        case tg_config::param_tags::step_le_17:
        case tg_config::param_tags::step_le_18:
        case tg_config::param_tags::step_le_19:
        case tg_config::param_tags::step_le_20:
        case tg_config::param_tags::step_le_21:
        case tg_config::param_tags::step_le_22:
        case tg_config::param_tags::step_le_23:
        case tg_config::param_tags::step_le_24:
        case tg_config::param_tags::step_le_25:
        case tg_config::param_tags::step_le_26:
        case tg_config::param_tags::step_le_27:
        case tg_config::param_tags::step_le_28:
        case tg_config::param_tags::step_le_29:
        case tg_config::param_tags::step_le_30:
        case tg_config::param_tags::step_le_31:
        case tg_config::param_tags::step_le_32: {
            constexpr i32 LEFT_CH_IDX = 0;

            const auto tag = param.tag - tg_config::param_tags::step_le_01;
            tg::set_step(trance_gate_cx, LEFT_CH_IDX, tag, param.value);
            break;
        }
        case tg_config::param_tags::step_ri_01:
        case tg_config::param_tags::step_ri_02:
        case tg_config::param_tags::step_ri_03:
        case tg_config::param_tags::step_ri_04:
        case tg_config::param_tags::step_ri_05:
        case tg_config::param_tags::step_ri_06:
        case tg_config::param_tags::step_ri_07:
        case tg_config::param_tags::step_ri_08:
        case tg_config::param_tags::step_ri_09:
        case tg_config::param_tags::step_ri_10:
        case tg_config::param_tags::step_ri_11:
        case tg_config::param_tags::step_ri_12:
        case tg_config::param_tags::step_ri_13:
        case tg_config::param_tags::step_ri_14:
        case tg_config::param_tags::step_ri_15:
        case tg_config::param_tags::step_ri_16:
        case tg_config::param_tags::step_ri_17:
        case tg_config::param_tags::step_ri_18:
        case tg_config::param_tags::step_ri_19:
        case tg_config::param_tags::step_ri_20:
        case tg_config::param_tags::step_ri_21:
        case tg_config::param_tags::step_ri_22:
        case tg_config::param_tags::step_ri_23:
        case tg_config::param_tags::step_ri_24:
        case tg_config::param_tags::step_ri_25:
        case tg_config::param_tags::step_ri_26:
        case tg_config::param_tags::step_ri_27:
        case tg_config::param_tags::step_ri_28:
        case tg_config::param_tags::step_ri_29:
        case tg_config::param_tags::step_ri_30:
        case tg_config::param_tags::step_ri_31:
        case tg_config::param_tags::step_ri_32: {
            constexpr i32 RIGHT_CH_IDX = 1;

            const auto tag = param.tag - tg_config::param_tags::step_ri_01;
            tg::set_step(trance_gate_cx, RIGHT_CH_IDX, tag, param.value);
            break;
        }
        case tg_config::param_tags::amount: {
            tg::set_mix(trance_gate_cx, param.value);
            break;
        }
        case tg_config::param_tags::contour: {
            static auto constexpr info =
                tg_config::param_list.at(tg_config::param_tags::contour);
            static auto const& conv_funcs =
                tg_config::get_convert_functions(info.convert_tag);

            tg::set_contour(trance_gate_cx,
                            conv_funcs.to_physical(param.value));
            break;
        }
        case tg_config::param_tags::speed: {
            static auto constexpr info =
                tg_config::param_list.at(tg_config::param_tags::speed);
            static auto const& conv_funcs =
                tg_config::get_convert_functions(info.convert_tag);

            auto const step_len =
                tg_config::get_speed(conv_funcs.to_physical(param.value));

            tg::set_step_len(trance_gate_cx, step_len);
            break;
        }
        case tg_config::param_tags::step_count: {
            static auto constexpr info =
                tg_config::param_list.at(tg_config::param_tags::step_count);
            static auto const& conv_funcs =
                tg_config::get_convert_functions(info.convert_tag);

            tg::set_step_count(trance_gate_cx,
                               conv_funcs.to_physical(param.value));
            break;
        }
        case tg_config::param_tags::mode: {
            tg::set_stereo_mode(trance_gate_cx,
                                param.value > 0.5 ? true : false);
            break;
        }
        case tg_config::param_tags::width: {
            tg::set_width(trance_gate_cx, param.value);
            break;
        }
        case tg_config::param_tags::shuffle: {
            tg::set_shuffle_amount(trance_gate_cx, param.value);
            break;
        }
        case tg_config::param_tags::fade_in: {
            static auto constexpr info =
                tg_config::param_list.at(tg_config::param_tags::fade_in);
            static auto const& conv_funcs =
                tg_config::get_convert_functions(info.convert_tag);

            real val = tg_config::get_delay_fade_len(
                conv_funcs.to_physical(param.value));

            func(param.tag, val);
            break;
        }
        case tg_config::param_tags::delay: {
            static auto constexpr info =
                tg_config::param_list.at(tg_config::param_tags::delay);
            static auto const& conv_funcs =
                tg_config::get_convert_functions(info.convert_tag);
            real val = tg_config::get_delay_fade_len(
                conv_funcs.to_physical(param.value));

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
                       fx_collection::trance_gate::context& trance_gate_cx,
                       const Func& func)
{
    for (const auto& pin : param_ins)
    {
        update_parameter(pin, trance_gate_cx, func);
    }
}

//-----------------------------------------------------------------------------
bool is_silent_input(process_data& data,
                     silence_detection::context& silence_detection_cx)
{
    using audio_frame = fx_collection::audio_frame;

    audio_frame frame = fx_collection::zero_audio_frame;
    bool is_silent    = false;
    for (mut_i32 s = 0; s < data.num_samples; ++s)
    {
        frame.data[0] = data.inputs[0][0][s];
        frame.data[1] = data.inputs[0][1][s];

        is_silent = silence_detection::process(silence_detection_cx, frame);
    }

    return is_silent;
}

//-----------------------------------------------------------------------------
void output_step_pos_param(fx_collection::trance_gate::context& cx,
                           process_data& data)
{
    using tg_config = trance_gate::config;

    static auto constexpr info =
        tg_config::param_list.at(tg_config::param_tags::step_count);
    static auto const& conv_funcs =
        tg_config::get_convert_functions(info.convert_tag);

    i32 index       = cx.step_val.pos + 1; // non programming index!
    real norm_index = conv_funcs.to_normalised(index);
    data.param_outputs.push_back({tg_config::param_tags::step_pos, norm_index});
}

//-----------------------------------------------------------------------------
void process_audio_buffers(fx_collection::trance_gate::context& trance_gate_cx,
                           process_data& data)
{
    using tg          = fx_collection::trance_gate;
    using audio_frame = fx_collection::audio_frame;
    constexpr i32 L   = 0;
    constexpr i32 R   = 1;

    audio_frame frame = fx_collection::zero_audio_frame;
    for (mut_i32 s = 0; s < data.num_samples; ++s)
    {
        frame.data[L] = data.inputs[0][L][s];
        frame.data[R] = data.inputs[0][R][s];
        tg::process(trance_gate_cx, frame, frame);
        data.outputs[0][L][s] = frame.data[L];
        data.outputs[0][R][s] = frame.data[R];
    }

    output_step_pos_param(trance_gate_cx, data);
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
            cx.trance_gate_cx, 
            [this](tag_type param_tag, real value) {
                update_param(param_tag, value);
            });
        // clang-format on
    }
}

//-----------------------------------------------------------------------------
bool tg_processor::process_audio(process_data& data)
{
    using tg          = fx_collection::trance_gate;
    using audio_frame = fx_collection::audio_frame;

    update_parameters(data.param_inputs,
                      cx.trance_gate_cx,
                      [this](tag_type param_tag, real value) {
                          update_param(param_tag, value);
                      });

    if (data.inputs.size() == 0 || data.outputs.size() == 0)
        return true;

    if (is_silent_input(data, cx.silence_detection_cx))
    {
        if (!cx.needs_trigger)
        {
            cx.trance_gate_cx.step_val.pos = 0;
            output_step_pos_param(cx.trance_gate_cx, data);
        }

        cx.needs_trigger = true;
        return true;
    }

    if (cx.needs_trigger)
    {
        cx.needs_trigger = false;
        tg::trigger(cx.trance_gate_cx, cx.delay_len, cx.fade_in_len);

        cx.trigger_phase = compute_project_time_anchor(data.project_time_music);
    }

    tg::set_tempo(cx.trance_gate_cx, data.tempo);

    real ptm = data.project_time_music + cx.trigger_phase;
    tg::update_project_time_music(cx.trance_gate_cx, ptm);

    process_audio_buffers(cx.trance_gate_cx, data);

    return true;
}

//-----------------------------------------------------------------------------
void tg_processor::setup_processing(process_setup& setup)
{
    using tg = fx_collection::trance_gate;

    tg::set_sample_rate(cx.trance_gate_cx, setup.sample_rate);

    constexpr real RETRIGGER_TIMER = 0.5;
    cx.silence_detection_cx =
        silence_detection::create(setup.sample_rate, RETRIGGER_TIMER);
}

//-----------------------------------------------------------------------------
void tg_processor::update_param(tag_type param_tag, real value)
{
    switch (param_tag)
    {
        case config::param_tags::fade_in:
            cx.fade_in_len = value;
            break;
        case config::param_tags::delay:
            cx.delay_len = value;
            break;
        default:
            break;
    }
}

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules::trance_gate