// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "hao/audio_modules/param_info.h"
#include <array>
#include <functional>

namespace hao::audio_modules::trance_gate {

//-----------------------------------------------------------------------------
/**
 * config
 */
struct Config
{
    /**
     * Tags for all moduation pins resp. parameters
     */
    struct ParamTags
    {
        enum : tag_type
        {
            step_le_01 = 0,
            step_le_02,
            step_le_03,
            step_le_04,
            step_le_05,
            step_le_06,
            step_le_07,
            step_le_08,
            step_le_09,
            step_le_10,
            step_le_11,
            step_le_12,
            step_le_13,
            step_le_14,
            step_le_15,
            step_le_16,
            step_le_17,
            step_le_18,
            step_le_19,
            step_le_20,
            step_le_21,
            step_le_22,
            step_le_23,
            step_le_24,
            step_le_25,
            step_le_26,
            step_le_27,
            step_le_28,
            step_le_29,
            step_le_30,
            step_le_31,
            step_le_32,
            step_ri_01,
            step_ri_02,
            step_ri_03,
            step_ri_04,
            step_ri_05,
            step_ri_06,
            step_ri_07,
            step_ri_08,
            step_ri_09,
            step_ri_10,
            step_ri_11,
            step_ri_12,
            step_ri_13,
            step_ri_14,
            step_ri_15,
            step_ri_16,
            step_ri_17,
            step_ri_18,
            step_ri_19,
            step_ri_20,
            step_ri_21,
            step_ri_22,
            step_ri_23,
            step_ri_24,
            step_ri_25,
            step_ri_26,
            step_ri_27,
            step_ri_28,
            step_ri_29,
            step_ri_30,
            step_ri_31,
            step_ri_32,
            amount,
            speed,
            contour,
            step_count,
            mode,
            width,
            fade_in,
            delay,
            shuffle,
            step_pos,
            count
        };
    };

    /**
     * Tags for converters
     */
    struct ConvertTags
    {
        enum : tag_type
        {
            normalised = 0,
            percent,
            contour,
            speed,
            delay_fade_length,
            step_count,
            mono_stereo,
            sync_mode,
            step_pos,
            count
        };
    };

    using param_list_type = std::array<ParamInfo const, ParamTags::count>;
    static constexpr param_list_type param_list =
        // clang-format off
    {{
        {
            /*name = */               "Step L01",
            /*short_name = */         "L01",
            /*units = */              "%",
            /*param_tag = */          ParamTags::step_le_01,
            /*default_normalised = */ 1.,
            /*convert_tag = */        ConvertTags::percent
        },
        { "Step L02", "L02", "%", ParamTags::step_le_02, 0., ConvertTags::percent },
        { "Step L03", "L03", "%", ParamTags::step_le_03, 1., ConvertTags::percent },
        { "Step L04", "L04", "%", ParamTags::step_le_04, 0., ConvertTags::percent },
        { "Step L05", "L05", "%", ParamTags::step_le_05, 1., ConvertTags::percent },
        { "Step L06", "L06", "%", ParamTags::step_le_06, 1., ConvertTags::percent },
        { "Step L07", "L07", "%", ParamTags::step_le_07, 1., ConvertTags::percent },
        { "Step L08", "L08", "%", ParamTags::step_le_08, 0., ConvertTags::percent },
        { "Step L09", "L09", "%", ParamTags::step_le_09, 1., ConvertTags::percent },
        { "Step L10", "L10", "%", ParamTags::step_le_10, 0., ConvertTags::percent },
        { "Step L11", "L11", "%", ParamTags::step_le_11, 1., ConvertTags::percent },
        { "Step L12", "L12", "%", ParamTags::step_le_12, 0., ConvertTags::percent },
        { "Step L13", "L13", "%", ParamTags::step_le_13, 1., ConvertTags::percent },
        { "Step L14", "L14", "%", ParamTags::step_le_14, 1., ConvertTags::percent },
        { "Step L15", "L15", "%", ParamTags::step_le_15, 1., ConvertTags::percent },
        { "Step L16", "L16", "%", ParamTags::step_le_16, 0., ConvertTags::percent },
        { "Step L17", "L17", "%", ParamTags::step_le_17, 1., ConvertTags::percent },
        { "Step L18", "L18", "%", ParamTags::step_le_18, 0., ConvertTags::percent },
        { "Step L19", "L19", "%", ParamTags::step_le_19, 1., ConvertTags::percent },
        { "Step L20", "L20", "%", ParamTags::step_le_20, 1., ConvertTags::percent },
        { "Step L21", "L21", "%", ParamTags::step_le_21, 1., ConvertTags::percent },
        { "Step L22", "L22", "%", ParamTags::step_le_22, 0., ConvertTags::percent },
        { "Step L23", "L23", "%", ParamTags::step_le_23, 0., ConvertTags::percent },
        { "Step L24", "L24", "%", ParamTags::step_le_24, 1., ConvertTags::percent },
        { "Step L25", "L25", "%", ParamTags::step_le_25, 0., ConvertTags::percent },
        { "Step L26", "L26", "%", ParamTags::step_le_26, 1., ConvertTags::percent },
        { "Step L27", "L27", "%", ParamTags::step_le_27, 1., ConvertTags::percent },
        { "Step L28", "L28", "%", ParamTags::step_le_28, 1., ConvertTags::percent },
        { "Step L29", "L29", "%", ParamTags::step_le_29, 0., ConvertTags::percent },
        { "Step L30", "L30", "%", ParamTags::step_le_30, 0., ConvertTags::percent },
        { "Step L31", "L31", "%", ParamTags::step_le_31, 0., ConvertTags::percent },
        { "Step L32", "L32", "%", ParamTags::step_le_32, 0., ConvertTags::percent },
        {
            /*name = */               "Step R01",
            /*short_name = */         "R01",
            /*units = */              "%",
            /*param_tag = */          ParamTags::step_ri_01,
            /*default_normalised = */ 1.,
            /*convert_tag = */        ConvertTags::percent
        },
        { "Step R02", "R02", "%", ParamTags::step_ri_02, 0., ConvertTags::percent },
        { "Step R03", "R03", "%", ParamTags::step_ri_03, 1., ConvertTags::percent },
        { "Step R04", "R04", "%", ParamTags::step_ri_04, 0., ConvertTags::percent },
        { "Step R05", "R05", "%", ParamTags::step_ri_05, 1., ConvertTags::percent },
        { "Step R06", "R06", "%", ParamTags::step_ri_06, 1., ConvertTags::percent },
        { "Step R07", "R07", "%", ParamTags::step_ri_07, 1., ConvertTags::percent },
        { "Step R08", "R08", "%", ParamTags::step_ri_08, 0., ConvertTags::percent },
        { "Step R09", "R09", "%", ParamTags::step_ri_09, 1., ConvertTags::percent },
        { "Step R10", "R10", "%", ParamTags::step_ri_10, 0., ConvertTags::percent },
        { "Step R11", "R11", "%", ParamTags::step_ri_11, 1., ConvertTags::percent },
        { "Step R12", "R12", "%", ParamTags::step_ri_12, 0., ConvertTags::percent },
        { "Step R13", "R13", "%", ParamTags::step_ri_13, 1., ConvertTags::percent },
        { "Step R14", "R14", "%", ParamTags::step_ri_14, 1., ConvertTags::percent },
        { "Step R15", "R15", "%", ParamTags::step_ri_15, 1., ConvertTags::percent },
        { "Step R16", "R16", "%", ParamTags::step_ri_16, 0., ConvertTags::percent },
        { "Step R17", "R17", "%", ParamTags::step_ri_17, 1., ConvertTags::percent },
        { "Step R18", "R18", "%", ParamTags::step_ri_18, 0., ConvertTags::percent },
        { "Step R19", "R19", "%", ParamTags::step_ri_19, 1., ConvertTags::percent },
        { "Step R20", "R20", "%", ParamTags::step_ri_20, 1., ConvertTags::percent },
        { "Step R21", "R21", "%", ParamTags::step_ri_21, 1., ConvertTags::percent },
        { "Step R22", "R22", "%", ParamTags::step_ri_22, 0., ConvertTags::percent },
        { "Step R23", "R23", "%", ParamTags::step_ri_23, 0., ConvertTags::percent },
        { "Step R24", "R24", "%", ParamTags::step_ri_24, 1., ConvertTags::percent },
        { "Step R25", "R25", "%", ParamTags::step_ri_25, 0., ConvertTags::percent },
        { "Step R26", "R26", "%", ParamTags::step_ri_26, 1., ConvertTags::percent },
        { "Step R27", "R27", "%", ParamTags::step_ri_27, 1., ConvertTags::percent },
        { "Step R28", "R28", "%", ParamTags::step_ri_28, 1., ConvertTags::percent },
        { "Step R29", "R29", "%", ParamTags::step_ri_29, 0., ConvertTags::percent },
        { "Step R30", "R30", "%", ParamTags::step_ri_30, 0., ConvertTags::percent },
        { "Step R31", "R31", "%", ParamTags::step_ri_31, 0., ConvertTags::percent },
        { "Step R32", "R32", "%", ParamTags::step_ri_32, 0., ConvertTags::percent },
        {
            /*name = */               "Mix",
            /*short_name = */         "Mix",
            /*units = */              "%",
            /*param_tag = */          ParamTags::amount,
            /*default_normalised = */ 1.,
            /*convert_tag = */        ConvertTags::percent
        }, 
        {
            /*name = */               "Speed",
            /*short_name = */         "Spd",
            /*units = */              "note",
            /*param_tag = */          ParamTags::speed,
            /*default_normalised = */ 2. / 24., // 1/32
            /*convert_tag = */        ConvertTags::speed
        }, 
        {
            /*name = */               "Contour",
            /*short_name = */         "Ctr",
            /*units = */              "s",
            /*param_tag = */          ParamTags::contour,
            /*default_normalised = */ 1.,
            /*convert_tag = */        ConvertTags::contour
        },
        {
            /*name = */               "Length",
            /*short_name = */         "Lgt",
            /*units = */              "steps",
            /*param_tag = */          ParamTags::step_count,
            /*default_normalised = */ 0.25,
            /*convert_tag = */        ConvertTags::step_count
        },
        {
            /*name = */               "Mode",
            /*short_name = */         "Mod",
            /*units = */              "",
            /*param_tag = */          ParamTags::mode,
            /*default_normalised = */ 0.,
            /*convert_tag = */        ConvertTags::mono_stereo
        },
        {
            /*name = */               "Stereo Width",
            /*short_name = */         "Wid",
            /*units = */              "%",
            /*param_tag = */          ParamTags::width,
            /*default_normalised = */ 1.,
            /*convert_tag = */        ConvertTags::percent
        },
        {
            /*name = */               "Fade In",
            /*short_name = */         "FIn",
            /*units = */              "note",
            /*param_tag = */          ParamTags::fade_in,
            /*default_normalised = */ 0.,
            /*convert_tag = */        ConvertTags::delay_fade_length
        },
        {
            /*name = */               "Delay",
            /*short_name = */         "Dly",
            /*units = */              "note",
            /*param_tag = */          ParamTags::delay,
            /*default_normalised = */ 0.,
            /*convert_tag = */        ConvertTags::delay_fade_length
        },
        {
            /*name = */               "Shuffle",
            /*short_name = */         "Shf",
            /*units = */              "%",
            /*param_tag = */          ParamTags::shuffle,
            /*default_normalised = */ 0.,
            /*convert_tag = */        ConvertTags::percent
        },
        {
            /*name = */               "Step Position",
            /*short_name = */         "SPs",
            /*units = */              "%",
            /*param_tag = */          ParamTags::step_pos,
            /*default_normalised = */ 0.,
            /*convert_tag = */        ConvertTags::step_pos,
            /*is_read_only = */       true
        }
    }};
    // clang-format on

    static_assert(ParamTags::count == param_list.size(),
                  "The param_list does not contain all parameter definitions!");

    static ConverterFuncs const& get_convert_functions(tag_type convert_tag);
    static real get_speed(real value);
    static real get_delay_fade_len(real value);
};

//-----------------------------------------------------------------------------
} // namespace hao::audio_modules::trance_gate