// Copyright(c) 2021 Hansen Audio.

#include "trance_gate_processor.h"
#include "hao/audio_modules/convert_funcs.h"
#include "trance_gate_config.h"
#include <cassert>

namespace hao::audio_modules::trance_gate {
namespace {

//-----------------------------------------------------------------------------
#if USE_FX_COLLECTION_RS
namespace TranceGateImpl = fx_collection_rs;
using TranceGateFx       = fx_collection_rs::TranceGate;
using AudioFrame         = fx_collection_rs::AudioFrame;
#else
using TranceGateImpl = ha::fx_collection::TranceGateImpl;
using TranceGateFx   = ha::fx_collection::TranceGate;
#endif

//-----------------------------------------------------------------------------
template <typename Func>
void update_parameter(ParamChange const& param,
#if USE_FX_COLLECTION_RS
                      TranceGateFx* trance_gate_fx,
#else
                      TranceGateFx& trance_gate_fx,
#endif
                      const Func& func)
{
    using cfg  = trance_gate::Config;
    using tags = cfg::ParamTags;

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
            TranceGateImpl::set_step(
                trance_gate_fx, LEFT_CH_IDX, tag, param.value);
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
            TranceGateImpl::set_step(
                trance_gate_fx, RIGHT_CH_IDX, tag, param.value);
            break;
        }
        case tags::amount: {
            TranceGateImpl::set_mix(trance_gate_fx, param.value);
            break;
        }
        case tags::contour: {
            static auto constexpr info = cfg::param_list.at(tags::contour);
            static auto const& conv_funcs =
                cfg::get_convert_functions(info.convert_tag);

            TranceGateImpl::set_contour(trance_gate_fx,
                                        conv_funcs.to_physical(param.value));
            break;
        }
        case tags::speed: {
            static auto constexpr info = cfg::param_list.at(tags::speed);
            static auto const& conv_funcs =
                cfg::get_convert_functions(info.convert_tag);

            auto const step_len =
                cfg::get_speed(conv_funcs.to_physical(param.value));

            TranceGateImpl::set_step_len(trance_gate_fx, step_len);
            break;
        }
        case tags::step_count: {
            static auto constexpr info = cfg::param_list.at(tags::step_count);
            static auto const& conv_funcs =
                cfg::get_convert_functions(info.convert_tag);

            TranceGateImpl::set_step_count(trance_gate_fx,
                                           conv_funcs.to_physical(param.value));
            break;
        }
        case tags::mode: {
            TranceGateImpl::set_stereo_mode(trance_gate_fx,
                                            param.value > 0.5 ? true : false);
            break;
        }
        case tags::width: {
            TranceGateImpl::set_width(trance_gate_fx, param.value);
            break;
        }
        case tags::shuffle: {
            TranceGateImpl::set_shuffle_amount(trance_gate_fx, param.value);
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
void update_parameters(ProcessData::param_changes const& param_ins,
#if USE_FX_COLLECTION_RS
                       TranceGateFx* trance_gate_fx,
#else
                       TranceGateFx& trance_gate_fx,
#endif
                       const Func& func)
{
    for (const auto& pin : param_ins)
    {
        update_parameter(pin, trance_gate_fx, func);
    }
}

//-----------------------------------------------------------------------------
bool is_silent_input(ProcessData& data, SilenceDetection& silence_detection)
{
    using AudioFrame = ha::fx_collection::AudioFrame;

    AudioFrame frame = ha::fx_collection::zero_audio_frame;
    bool is_silent   = false;
    for (mut_i32 s = 0; s < data.num_samples; ++s)
    {
        frame.data[0] = data.inputs[0][0][s];
        frame.data[1] = data.inputs[0][1][s];

        is_silent = SilenceDetectionImpl::process(silence_detection, frame);
    }

    return is_silent;
}

//-----------------------------------------------------------------------------
void output_step_pos_param(
#if USE_FX_COLLECTION_RS
    TranceGateFx* trance_gate_fx,
#else
    TranceGateFx& trance_gate_fx,
#endif
    ProcessData& data)
{
    using cfg  = trance_gate::Config;
    using tags = cfg::ParamTags;

    static auto constexpr info = cfg::param_list.at(tags::step_pos);
    static auto const& conv_funcs =
        cfg::get_convert_functions(info.convert_tag);

    i32 step_pos    = TranceGateImpl::get_step_pos(trance_gate_fx);
    i32 index       = step_pos + 1; // non programming index!
    real norm_index = conv_funcs.to_normalised(index);
    data.param_outputs.push_back({tags::step_pos, norm_index});
}

//-----------------------------------------------------------------------------
void process_audio_buffers(
#if USE_FX_COLLECTION_RS
    TranceGateFx* trance_gate_fx,
#else
    TranceGateFx& trance_gate_fx,
#endif
    ProcessData& data)
{
    constexpr i32 L = 0;
    constexpr i32 R = 1;

#if USE_FX_COLLECTION_RS
    struct AudioFrameType
    {
        AudioFrame data;
    };
    AudioFrameType frame;
#else
    using AudioFrame = ha::fx_collection::AudioFrame;
    AudioFrame frame = ha::fx_collection::zero_audio_frame;
#endif
    for (mut_i32 s = 0; s < data.num_samples; ++s)
    {
        frame.data[L] = data.inputs[0][L][s];
        frame.data[R] = data.inputs[0][R][s];
#if USE_FX_COLLECTION_RS
        process(trance_gate_fx, &(frame.data), &(frame.data));
#else
        TranceGateImpl::process(trance_gate_fx, frame, frame);
#endif
        data.outputs[0][L][s] = frame.data[L];
        data.outputs[0][R][s] = frame.data[R];
    }

    output_step_pos_param(trance_gate_fx, data);
}

//-----------------------------------------------------------------------------
f64 compute_project_time_anchor(f64 project_time_music)
{
    /**
     * 'Delay' and 'Fade In' parameters' max len is '4 notes'
     * which is 16 beats.
     */
    constexpr f64 MAX_PHASE_LEN_IN_BEATS = f64(16.);

    if (project_time_music < f64(0.))
    {
        f64 ptm       = abs(project_time_music);
        f64 remainder = fmod(ptm, MAX_PHASE_LEN_IN_BEATS);
        return remainder;
    }
    else
    {
        f64 ptm       = project_time_music;
        f64 remainder = fmod(ptm, MAX_PHASE_LEN_IN_BEATS);
        return MAX_PHASE_LEN_IN_BEATS - remainder;
    }
}

//-----------------------------------------------------------------------------
} // namespace

/**
 * TranceGateModuleImpl
 */
TranceGateModuleImpl::TranceGateModuleImpl()
{
#if USE_FX_COLLECTION_RS
    module.trance_gate_fx = fx_collection_rs::create_trance_gate();
#endif

    for (ParamInfo const& info : Config::param_list)
    {
        // clang-format off
        update_parameter(
            {info.param_tag, info.default_normalised},
            module.trance_gate_fx, 
            [this](tag_type param_tag, real value) {
                update_param(param_tag, value);
            });
        // clang-format on
    }
}

//-----------------------------------------------------------------------------
TranceGateModuleImpl::~TranceGateModuleImpl()
{
#if USE_FX_COLLECTION_RS
    fx_collection_rs::destroy_trance_gate(module.trance_gate_fx);
#endif
}

//-----------------------------------------------------------------------------
bool TranceGateModuleImpl::process_audio(ProcessData& data)
{
    update_parameters(data.param_inputs,
                      module.trance_gate_fx,
                      [this](tag_type param_tag, real value) {
                          update_param(param_tag, value);
                      });

    if (data.inputs.size() == 0 || data.outputs.size() == 0)
        return true;

    if (is_silent_input(data, module.silence_detection))
    {
        if (!module.needs_trigger)
        {
            TranceGateImpl::reset_step_pos(module.trance_gate_fx, 0);
            output_step_pos_param(module.trance_gate_fx, data);
        }

        if (!module.needs_trigger)
            module.needs_trigger = true;

        return true;
    }

    if (module.needs_trigger)
    {
        module.needs_trigger = false;
        TranceGateImpl::trigger(
            module.trance_gate_fx, module.delay_len, module.fade_in_len);

        module.trigger_phase =
            compute_project_time_anchor(data.project_time_music);
    }

    TranceGateImpl::set_tempo(module.trance_gate_fx, data.tempo);

    real ptm = data.project_time_music + module.trigger_phase;
    TranceGateImpl::update_project_time_music(module.trance_gate_fx, ptm);

    process_audio_buffers(module.trance_gate_fx, data);

    return true;
}

//-----------------------------------------------------------------------------
void TranceGateModuleImpl::setup_processing(ProcessSetup& setup)
{
    TranceGateImpl::set_sample_rate(module.trance_gate_fx, setup.sample_rate);

    constexpr real RETRIGGER_TIMER = 0.5;
    module.silence_detection =
        SilenceDetectionImpl::create(setup.sample_rate, RETRIGGER_TIMER);
}

//-----------------------------------------------------------------------------
void TranceGateModuleImpl::update_param(tag_type param_tag, real value)
{
    using tags = Config::ParamTags;
    switch (param_tag)
    {
        case tags::fade_in:
            module.fade_in_len = value;
            break;
        case tags::delay:
            module.delay_len = value;
            break;
        default:
            break;
    }
}

//-----------------------------------------------------------------------------
} // namespace hao::audio_modules::trance_gate