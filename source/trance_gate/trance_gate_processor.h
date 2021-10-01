// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "ha/audio_modules/module.h"
#include "ha/audio_modules/types.h"
#include "ha/fx_collection/trance_gate.h"
#include "silence_detection.h"

#define USE_FX_COLLECTION_RS 1
#if USE_FX_COLLECTION_RS
#include "fx-collection-rs_bindings.h"
#endif

namespace ha::audio_modules::trance_gate {

//-----------------------------------------------------------------------------
/**
 * tg_processor
 */
class tg_processor final : public module
{
public:
    //-------------------------------------------------------------------------
    tg_processor();
    ~tg_processor() override;

    bool process_audio(process_data& data) override;
    void setup_processing(process_setup& setup) override;

    //-------------------------------------------------------------------------
private:
    void update_param(tag_type param_tag, real value);

    struct context
    {
        mut_real delay_len     = real(0.);
        mut_real fade_in_len   = real(0.);
        mut_real trigger_phase = real(0.);
        silence_detection::context silence_detection_cx;
        bool needs_trigger = true;

#if USE_FX_COLLECTION_RS
        fx_collection_rs::trance_gate::TranceGate* fx_trance_gate_cx = nullptr;
#else
        fx_collection::trance_gate::context fx_trance_gate_cx =
            fx_collection::trance_gate::create();
#endif
    };

    context cx;
};

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules::trance_gate
