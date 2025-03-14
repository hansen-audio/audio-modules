// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "types.h"

namespace hao::audio_modules {

//-----------------------------------------------------------------------------
/**
 * params_data
 */
struct ParamChange
{
    mut_tag_type tag = -1;
    mut_real value   = real(0.);
};

/**
 * ProcessData
 */
struct ProcessData
{
    using param_changes = std::vector<ParamChange>;

    mut_real sample_rate           = real(44100.);
    mut_real oversampling_factor   = real(1.);
    mut_real tempo                 = real(120.);
    mut_i32 num_samples            = 256;
    mut_i64 continous_time_samples = 0;
    mut_f64 project_time_music     = mut_f64(1.);

    AudioBusses inputs;
    AudioBusses outputs;
    param_changes param_inputs;
    param_changes param_outputs;
};

/**
 * process_setup
 */
struct ProcessSetup
{
    real sample_rate   = real(44100.);
    i32 block_size     = 64;
    real reciprocal_sr = real(1.) / sample_rate;
};

/**
 * module
 */
struct ModuleImpl
{
    virtual void setup_processing(ProcessSetup& setup) = 0;
    virtual bool process_audio(ProcessData& data)      = 0;

    virtual ~ModuleImpl() {}
};

//-----------------------------------------------------------------------------
} // namespace hao::audio_modules
