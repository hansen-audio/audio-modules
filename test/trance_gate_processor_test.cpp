// Copyright(c) 2021 Hansen Audio.

#include "gtest/gtest.h"

#include "ha/audio_modules/audio_modules.h"
#include "thread_malloc_detector.h"
#include "trance_gate/trance_gate_config.h"
#include "trance_gate/trance_gate_processor.h"

using namespace ha;

namespace {

//-----------------------------------------------------------------------------
audio_modules::process_data create_process_data()
{
    constexpr audio_modules::i32 sample_count         = 32;
    constexpr audio_modules::i32 input_channel_count  = 2;
    constexpr audio_modules::i32 output_channel_count = 2;

    audio_modules::process_data data;

    data.num_samples = sample_count;
    data.inputs.resize(1);
    data.outputs.resize(1);
    data.inputs.at(0).resize(input_channel_count);
    data.outputs.at(0).resize(output_channel_count);
    data.inputs.at(0).at(0).resize(sample_count);
    data.inputs.at(0).at(1).resize(sample_count);
    data.outputs.at(0).at(0).resize(sample_count);
    data.outputs.at(0).at(1).resize(sample_count);
    data.mod_data.pin_datas.reserve(128);

    return data;
}

//-----------------------------------------------------------------------------
audio_modules::process_setup create_process_setup()
{
    return {/*setup.sample_rate   =*/audio_modules::real(44100.),
            /*setup.block_size    =*/32,
            /*setup.reciprocal_sr =*/audio_modules::real(1. / 44100.)};
}

//-----------------------------------------------------------------------------
//  Tests
//-----------------------------------------------------------------------------
TEST(audio_modules_test, test_allocation_free_trance_gate_constructor)
{
    thread_malloc_detector log;
    auto pd = create_process_data();
    EXPECT_TRUE(log.was_detected());
}

//-----------------------------------------------------------------------------
TEST(audio_modules_test, test_allocation_free_process_setup)
{
    auto ps = create_process_setup();
    audio_modules::trance_gate::tg_processor tgp;

    thread_malloc_detector detector;
    tgp.setup_processing(ps);
    EXPECT_FALSE(detector.was_detected());
}

//-----------------------------------------------------------------------------
TEST(audio_modules_test, test_allocation_free_process_audio)
{
    audio_modules::trance_gate::tg_processor tgp;

    auto ps = create_process_setup();
    tgp.setup_processing(ps);

    auto pd = create_process_data();
    pd.mod_data.pin_datas.push_back({audio_modules::trance_gate::config::param_tags::contour, 1.0});
    pd.mod_data.pin_datas.push_back({audio_modules::trance_gate::config::param_tags::amount, 1.0});
    pd.mod_data.pin_datas.push_back({audio_modules::trance_gate::config::param_tags::speed, 1.0});

    thread_malloc_detector detector;
    tgp.process_audio(pd);
    EXPECT_FALSE(detector.was_detected());
}

//-----------------------------------------------------------------------------
TEST(audio_modules_factory_test, test_trance_gate_mod_infos)
{
    using amf             = audio_modules::module_factory;
    const auto mod_infos  = amf::param_infos(audio_modules::module_tags::TRANCE_GATE);
    const auto converters = amf::convert_funcs(audio_modules::module_tags::TRANCE_GATE);
    auto const converter  = converters.at(audio_modules::trance_gate::config::convert_tags::speed);
    if (converter.num_steps)
        auto num_steps = converter.num_steps();

    auto tg_node = amf::create_audio_module(audio_modules::module_tags::TRANCE_GATE);
}

//-----------------------------------------------------------------------------
} // namespace