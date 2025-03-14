// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "hao/audio_modules/convert_funcs.h"
#include "hao/audio_modules/module.h"
#include "hao/audio_modules/module_tags.h"
#include "hao/audio_modules/param_info.h"
#include "hao/audio_modules/types.h"
#include <memory>

namespace hao::audio_modules {

//-----------------------------------------------------------------------------
using audio_module_ptr = std::unique_ptr<ModuleImpl>;

//-----------------------------------------------------------------------------
/**
 * module_factory
 */
struct ModuleFactoryImpl
{
    static ParamInfosList const param_infos(ModuleTags tag);
    static ConvertFuncsList const convert_funcs(ModuleTags tag);
    static audio_module_ptr create_audio_module(ModuleTags tag);
};

//-----------------------------------------------------------------------------
} // namespace hao::audio_modules