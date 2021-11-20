// Copyright(c) 2021 Hansen Audio.

#include "ha/audio_modules/module_factory.h"
#include "trance_gate/trance_gate_config.h"
#include "trance_gate/trance_gate_processor.h"

namespace ha::audio_modules {

//-----------------------------------------------------------------------------
/**
 * module_factory
 */
template <typename AudioModuleConfig>
static const param_infos_list build_param_infos()
{
    return {AudioModuleConfig::param_list.begin(),
            AudioModuleConfig::param_list.end()};
}

//-----------------------------------------------------------------------------
template <typename AudioModuleConfig>
static const convert_funcs_list build_convert_funcs()
{
    convert_funcs_list list;
    for (size_t i = 0; i < AudioModuleConfig::convert_tags::count; ++i)
    {
        list.push_back(AudioModuleConfig::get_convert_functions(i));
    }
    return list;
}

//-----------------------------------------------------------------------------
param_infos_list const module_factory::param_infos(module_tags tag)
{
    switch (tag)
    {
        case module_tags::TRANCE_GATE: {
            return build_param_infos<trance_gate::config>();
        }
    }

    return {};
}

//-----------------------------------------------------------------------------
convert_funcs_list const module_factory::convert_funcs(module_tags tag)
{
    switch (tag)
    {
        case module_tags::TRANCE_GATE: {
            return build_convert_funcs<trance_gate::config>();
        }
    }

    return {};
}

//-----------------------------------------------------------------------------
audio_module_ptr module_factory::create_audio_module(module_tags tag)
{
    switch (tag)
    {
        case module_tags::TRANCE_GATE:
            return std::make_unique<trance_gate::TranceGateModuleImpl>();
            break;
        default:
            return std::make_unique<trance_gate::TranceGateModuleImpl>();
    }
}

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules