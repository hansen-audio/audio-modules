// Copyright(c) 2021 Hansen Audio.

#pragma once

#include "types.h"

namespace ha::audio_modules {

//-----------------------------------------------------------------------------
/**
 * modulation_data
 */
struct modulation_data
{
    struct pin_data
    {
        tag_type tag = -1;
        real value   = 0.;
    };

    using pin_data_list = std::vector<pin_data>;
    pin_data_list pin_datas;
};

/**
 * process_data
 */
struct process_data
{
    mut_real sample_rate           = real(44100.);
    mut_real oversampling_factor   = real(1.);
    mut_real tempo                 = real(120.);
    mut_i32 num_samples            = 256;
    mut_i64 continous_time_samples = 0;
    mut_real project_time_music    = real(1.);

    audio_busses inputs;
    audio_busses outputs;
    modulation_data mod_data;
};

/**
 * process_setup
 */
struct process_setup
{
    real sample_rate   = real(44100.);
    i32 block_size     = 64;
    real reciprocal_sr = real(1.) / sample_rate;
};

/**
 * module
 */
struct module
{
    virtual void setup_processing(process_setup& setup) = 0;
    virtual bool process_audio(process_data& data)      = 0;

    virtual ~module() {}
};

//-----------------------------------------------------------------------------
} // namespace ha::audio_modules
