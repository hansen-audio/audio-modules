// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/audio_modules/param_info.h"
#include <array>
#include <functional>

namespace ha::audio_modules::trance_gate {

//-----------------------------------------------------------------------------
/**
 * config
 */
struct config
{
    /**
     * Tags for all moduation pins resp. parameters
     */
    struct param_tags
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
            // sync,
            count
        };
    };

    /**
     * Tags for converters
     */
    struct convert_tags
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
            count
        };
    };

    using param_list_type = std::array<param_info const, param_tags::count>;
    static constexpr param_list_type param_list =
        // clang-format off
    {{
        {
            /*name = */               "Step L01",
            /*short_name = */         "L01",
            /*units = */              "%",
            /*param_tag = */          param_tags::step_le_01,
            /*default_normalised = */ 1.,
            /*convert_tag = */        convert_tags::percent
        },
        { "Step L02", "L02", "%", param_tags::step_le_02, 0., convert_tags::percent },
        { "Step L03", "L03", "%", param_tags::step_le_03, 1., convert_tags::percent },
        { "Step L04", "L04", "%", param_tags::step_le_04, 0., convert_tags::percent },
        { "Step L05", "L05", "%", param_tags::step_le_05, 1., convert_tags::percent },
        { "Step L06", "L06", "%", param_tags::step_le_06, 1., convert_tags::percent },
        { "Step L07", "L07", "%", param_tags::step_le_07, 1., convert_tags::percent },
        { "Step L08", "L08", "%", param_tags::step_le_08, 0., convert_tags::percent },
        { "Step L09", "L09", "%", param_tags::step_le_09, 1., convert_tags::percent },
        { "Step L10", "L10", "%", param_tags::step_le_10, 0., convert_tags::percent },
        { "Step L11", "L11", "%", param_tags::step_le_11, 1., convert_tags::percent },
        { "Step L12", "L12", "%", param_tags::step_le_12, 0., convert_tags::percent },
        { "Step L13", "L13", "%", param_tags::step_le_13, 1., convert_tags::percent },
        { "Step L14", "L14", "%", param_tags::step_le_14, 1., convert_tags::percent },
        { "Step L15", "L15", "%", param_tags::step_le_15, 1., convert_tags::percent },
        { "Step L16", "L16", "%", param_tags::step_le_16, 0., convert_tags::percent },
        { "Step L17", "L17", "%", param_tags::step_le_17, 1., convert_tags::percent },
        { "Step L18", "L18", "%", param_tags::step_le_18, 0., convert_tags::percent },
        { "Step L19", "L19", "%", param_tags::step_le_19, 1., convert_tags::percent },
        { "Step L20", "L20", "%", param_tags::step_le_20, 1., convert_tags::percent },
        { "Step L21", "L21", "%", param_tags::step_le_21, 1., convert_tags::percent },
        { "Step L22", "L22", "%", param_tags::step_le_22, 0., convert_tags::percent },
        { "Step L23", "L23", "%", param_tags::step_le_23, 0., convert_tags::percent },
        { "Step L24", "L24", "%", param_tags::step_le_24, 1., convert_tags::percent },
        { "Step L25", "L25", "%", param_tags::step_le_25, 0., convert_tags::percent },
        { "Step L26", "L26", "%", param_tags::step_le_26, 1., convert_tags::percent },
        { "Step L27", "L27", "%", param_tags::step_le_27, 1., convert_tags::percent },
        { "Step L28", "L28", "%", param_tags::step_le_28, 1., convert_tags::percent },
        { "Step L29", "L29", "%", param_tags::step_le_29, 0., convert_tags::percent },
        { "Step L30", "L30", "%", param_tags::step_le_30, 0., convert_tags::percent },
        { "Step L31", "L31", "%", param_tags::step_le_31, 0., convert_tags::percent },
        { "Step L32", "L32", "%", param_tags::step_le_32, 0., convert_tags::percent },
        {
            /*name = */               "Step R01",
            /*short_name = */         "R01",
            /*units = */              "%",
            /*param_tag = */          param_tags::step_ri_01,
            /*default_normalised = */ 1.,
            /*convert_tag = */        convert_tags::percent
        },
        { "Step R02", "R02", "%", param_tags::step_ri_02, 0., convert_tags::percent },
        { "Step R03", "R03", "%", param_tags::step_ri_03, 1., convert_tags::percent },
        { "Step R04", "R04", "%", param_tags::step_ri_04, 0., convert_tags::percent },
        { "Step R05", "R05", "%", param_tags::step_ri_05, 1., convert_tags::percent },
        { "Step R06", "R06", "%", param_tags::step_ri_06, 1., convert_tags::percent },
        { "Step R07", "R07", "%", param_tags::step_ri_07, 1., convert_tags::percent },
        { "Step R08", "R08", "%", param_tags::step_ri_08, 0., convert_tags::percent },
        { "Step R09", "R09", "%", param_tags::step_ri_09, 1., convert_tags::percent },
        { "Step R10", "R10", "%", param_tags::step_ri_10, 0., convert_tags::percent },
        { "Step R11", "R11", "%", param_tags::step_ri_11, 1., convert_tags::percent },
        { "Step R12", "R12", "%", param_tags::step_ri_12, 0., convert_tags::percent },
        { "Step R13", "R13", "%", param_tags::step_ri_13, 1., convert_tags::percent },
        { "Step R14", "R14", "%", param_tags::step_ri_14, 1., convert_tags::percent },
        { "Step R15", "R15", "%", param_tags::step_ri_15, 1., convert_tags::percent },
        { "Step R16", "R16", "%", param_tags::step_ri_16, 0., convert_tags::percent },
        { "Step R17", "R17", "%", param_tags::step_ri_17, 1., convert_tags::percent },
        { "Step R18", "R18", "%", param_tags::step_ri_18, 0., convert_tags::percent },
        { "Step R19", "R19", "%", param_tags::step_ri_19, 1., convert_tags::percent },
        { "Step R20", "R20", "%", param_tags::step_ri_20, 1., convert_tags::percent },
        { "Step R21", "R21", "%", param_tags::step_ri_21, 1., convert_tags::percent },
        { "Step R22", "R22", "%", param_tags::step_ri_22, 0., convert_tags::percent },
        { "Step R23", "R23", "%", param_tags::step_ri_23, 0., convert_tags::percent },
        { "Step R24", "R24", "%", param_tags::step_ri_24, 1., convert_tags::percent },
        { "Step R25", "R25", "%", param_tags::step_ri_25, 0., convert_tags::percent },
        { "Step R26", "R26", "%", param_tags::step_ri_26, 1., convert_tags::percent },
        { "Step R27", "R27", "%", param_tags::step_ri_27, 1., convert_tags::percent },
        { "Step R28", "R28", "%", param_tags::step_ri_28, 1., convert_tags::percent },
        { "Step R29", "R29", "%", param_tags::step_ri_29, 0., convert_tags::percent },
        { "Step R30", "R30", "%", param_tags::step_ri_30, 0., convert_tags::percent },
        { "Step R31", "R31", "%", param_tags::step_ri_31, 0., convert_tags::percent },
        { "Step R32", "R32", "%", param_tags::step_ri_32, 0., convert_tags::percent },
        {
            /*name = */               "Mix",
            /*short_name = */         "Mix",
            /*units = */              "%",
            /*param_tag = */          param_tags::amount,
            /*default_normalised = */ 1.,
            /*convert_tag = */        convert_tags::percent
        }, 
        {
            /*name = */               "Speed",
            /*short_name = */         "Spd",
            /*units = */              "Note",
            /*param_tag = */          param_tags::speed,
            /*default_normalised = */ 2. / 24., // 1/32
            /*convert_tag = */        convert_tags::speed
        }, 
        {
            /*name = */               "Contour",
            /*short_name = */         "Ctr",
            /*units = */              "s",
            /*param_tag = */          param_tags::contour,
            /*default_normalised = */ 1.,
            /*convert_tag = */        convert_tags::contour
        },
        {
            /*name = */               "Length",
            /*short_name = */         "Lgt",
            /*units = */              "steps",
            /*param_tag = */          param_tags::step_count,
            /*default_normalised = */ 0.25,
            /*convert_tag = */        convert_tags::step_count
        },
        {
            /*name = */               "Mode",
            /*short_name = */         "Mod",
            /*units = */              "",
            /*param_tag = */          param_tags::mode,
            /*default_normalised = */ 0.5,
            /*convert_tag = */        convert_tags::mono_stereo
        },
        {
            /*name = */               "Stereo Width",
            /*short_name = */         "Wid",
            /*units = */              "%",
            /*param_tag = */          param_tags::width,
            /*default_normalised = */ 1.,
            /*convert_tag = */        convert_tags::percent
        },
        {
            /*name = */               "Fade In",
            /*short_name = */         "FIn",
            /*units = */              "Note",
            /*param_tag = */          param_tags::fade_in,
            /*default_normalised = */ 0.,
            /*convert_tag = */        convert_tags::delay_fade_length
        },
        {
            /*name = */               "Delay",
            /*short_name = */         "Dly",
            /*units = */              "Note",
            /*param_tag = */          param_tags::delay,
            /*default_normalised = */ 0.,
            /*convert_tag = */        convert_tags::delay_fade_length
        },
        {
            /*name = */               "Shuffle",
            /*short_name = */         "Shf",
            /*units = */              "%",
            /*param_tag = */          param_tags::shuffle,
            /*default_normalised = */ 0.,
            /*convert_tag = */        convert_tags::percent
        },
        {
            /*name = */               "Step Position",
            /*short_name = */         "SPs",
            /*units = */              "%",
            /*param_tag = */          param_tags::step_pos,
            /*default_normalised = */ 0.,
            /*convert_tag = */        convert_tags::step_count,
            /*is_read_only = */       true
        }//,
        // {
        //     /*name = */               "Sync",
        //     /*short_name = */         "Syn",
        //     /*units = */              "",
        //     /*param_tag = */          param_tags::sync,
        //     /*default_normalised = */ 0.,
        //     /*convert_tag = */        convert_tags::sync_mode
        // }
    }};
    // clang-format on

    static_assert(param_tags::count == param_list.size(),
                  "The param_list does not contain all parameter definitions!");

    static convert_funcs const& get_convert_functions(tag_type convert_tag);
    static real get_speed(real value);
    static real get_delay_fade_len(real value);
};

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules::trance_gate