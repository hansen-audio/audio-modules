// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/audio_modules/module.h"
#include "ha/audio_modules/types.h"
#include "ha/fx_collection/trance_gate.h"
#include "silence_detection.h"

namespace ha {
namespace audio_modules {
namespace trance_gate {

//-----------------------------------------------------------------------------
/**
 * tg_processor
 */
class tg_processor : public module
{
public:
    //-------------------------------------------------------------------------
    tg_processor();

    bool process_audio(process_data& data) override;
    void setup_processing(process_setup& setup) override;

    //-------------------------------------------------------------------------
private:
    void update_param(tag_param param_tag, real value);

    mut_real delay_len   = 0.;
    mut_real fade_in_len = 0.;
    silence_detection::context sd_context;
    bool needs_trigger = true;

    fx_collection::trance_gate::context tg_context = fx_collection::trance_gate::create();
};

//-----------------------------------------------------------------------------
} // namespace trance_gate
} // namespace audio_modules
} // namespace ha
