// Copyright(c) 2021 Hansen Audio.

#include "ha/audio_modules/module_factory.h"
#include "trance_gate/trance_gate_config.h"
#include "trance_gate/trance_gate_processor.h"

namespace ha::audio_modules {

//-----------------------------------------------------------------------------
/**
 * module_factory
 */
template <typename TAudioModuleConfig>
static const ParamInfosList build_param_infos()
{
    return {TAudioModuleConfig::param_list.begin(),
            TAudioModuleConfig::param_list.end()};
}

//-----------------------------------------------------------------------------
template <typename TAudioModuleConfig>
static const ConvertFuncsList build_convert_funcs()
{
    ConvertFuncsList list;
    for (size_t i = 0; i < TAudioModuleConfig::ConvertTags::count; ++i)
    {
        list.push_back(TAudioModuleConfig::get_convert_functions(i));
    }
    return list;
}

//-----------------------------------------------------------------------------
ParamInfosList const ModuleFactoryImpl::param_infos(ModuleTags tag)
{
    switch (tag)
    {
        case ModuleTags::TranceGate: {
            return build_param_infos<trance_gate::Config>();
        }
    }

    return {};
}

//-----------------------------------------------------------------------------
ConvertFuncsList const ModuleFactoryImpl::convert_funcs(ModuleTags tag)
{
    switch (tag)
    {
        case ModuleTags::TranceGate: {
            return build_convert_funcs<trance_gate::Config>();
        }
    }

    return {};
}

//-----------------------------------------------------------------------------
audio_module_ptr ModuleFactoryImpl::create_audio_module(ModuleTags tag)
{
    switch (tag)
    {
        case ModuleTags::TranceGate:
            return std::make_unique<trance_gate::TranceGateModuleImpl>();
            break;
        default:
            return std::make_unique<trance_gate::TranceGateModuleImpl>();
    }
}

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules