// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "hao/audio_modules/module.h"
#include "hao/audio_modules/types.h"
#include "ha/fx_collection/trance_gate.h"
#include "silence_detection.h"

#define USE_FX_COLLECTION_RS 1
#if USE_FX_COLLECTION_RS
#include "hao/fx-collection-rs/cbindings.h"
#endif

namespace hao::audio_modules::trance_gate {

//-----------------------------------------------------------------------------
/**
 * TranceGateModuleImpl
 */

struct TranceGateModule
{
    mut_real delay_len     = real(0.);
    mut_real fade_in_len   = real(0.);
    mut_real trigger_phase = real(0.);
    SilenceDetection silence_detection;
    bool needs_trigger = true;

#if USE_FX_COLLECTION_RS
    fx_collection_rs::TranceGate* trance_gate_fx = nullptr;
#else
    ha::fx_collection::TranceGate trance_gate_fx =
        ha::fx_collection::TranceGateImpl::create();
#endif
};

class TranceGateModuleImpl final : public ModuleImpl
{
public:
    //-------------------------------------------------------------------------
    TranceGateModuleImpl();
    ~TranceGateModuleImpl() override;

    bool process_audio(ProcessData& data) override;
    void setup_processing(ProcessSetup& setup) override;

    //-------------------------------------------------------------------------
private:
    void update_param(tag_type param_tag, real value);

    TranceGateModule module;
};

//-----------------------------------------------------------------------------
} // namespace hao::audio_modules::trance_gate
