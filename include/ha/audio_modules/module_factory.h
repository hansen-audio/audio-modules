// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/audio_modules/convert_funcs.h"
#include "ha/audio_modules/module.h"
#include "ha/audio_modules/module_tags.h"
#include "ha/audio_modules/param_info.h"
#include "ha/audio_modules/types.h"
#include <memory>

namespace ha::audio_modules {

//-----------------------------------------------------------------------------
using audio_module_ptr = std::unique_ptr<module>;

//-----------------------------------------------------------------------------
/**
 * module_factory
 */
struct module_factory
{
    static param_infos_list const param_infos(module_tags tag);
    static convert_funcs_list const convert_funcs(module_tags tag);
    static audio_module_ptr create_audio_module(module_tags tag);
};

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules