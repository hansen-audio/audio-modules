// Copyright(c) 2021 Hansen Audio.

#include "gtest/gtest.h"

#include "ha/audio_modules/audio_modules.h"
#include "thread_malloc_detector.h"
#include "trance_gate/trance_gate_config.h"
#include "trance_gate/trance_gate_processor.h"

using namespace ha;

namespace {

//-----------------------------------------------------------------------------
audio_modules::ProcessData create_process_data()
{
    constexpr audio_modules::i32 sample_count         = 32;
    constexpr audio_modules::i32 input_channel_count  = 2;
    constexpr audio_modules::i32 output_channel_count = 2;

    audio_modules::ProcessData data;

    data.num_samples = sample_count;
    data.inputs.resize(1);
    data.outputs.resize(1);
    data.inputs.at(0).resize(input_channel_count);
    data.outputs.at(0).resize(output_channel_count);
    data.inputs.at(0).at(0).resize(sample_count);
    data.inputs.at(0).at(1).resize(sample_count);
    data.outputs.at(0).at(0).resize(sample_count);
    data.outputs.at(0).at(1).resize(sample_count);
    data.param_inputs.reserve(128);
    data.param_outputs.reserve(128);
    return data;
}

//-----------------------------------------------------------------------------
audio_modules::ProcessSetup create_process_setup()
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
    audio_modules::trance_gate::TranceGateModuleImpl tgp;

    thread_malloc_detector detector;
    tgp.setup_processing(ps);
    EXPECT_FALSE(detector.was_detected());
}

//-----------------------------------------------------------------------------
TEST(audio_modules_test, test_allocation_free_process_audio)
{
    audio_modules::trance_gate::TranceGateModuleImpl tgp;

    auto ps = create_process_setup();
    tgp.setup_processing(ps);

    auto pd = create_process_data();
    pd.param_inputs.push_back(
        {audio_modules::trance_gate::Config::ParamTags::contour, 1.0});
    pd.param_inputs.push_back(
        {audio_modules::trance_gate::Config::ParamTags::amount, 1.0});
    pd.param_inputs.push_back(
        {audio_modules::trance_gate::Config::ParamTags::speed, 1.0});

    thread_malloc_detector detector;
    tgp.process_audio(pd);
    EXPECT_FALSE(detector.was_detected());
}

//-----------------------------------------------------------------------------
TEST(audio_modules_factory_test, test_trance_gate_mod_infos)
{
    using amf = audio_modules::ModuleFactoryImpl;
    const auto mod_infos =
        amf::param_infos(audio_modules::ModuleTags::TranceGate);
    const auto converters =
        amf::convert_funcs(audio_modules::ModuleTags::TranceGate);
    auto const converter =
        converters.at(audio_modules::trance_gate::Config::ConvertTags::speed);
    if (converter.num_steps)
        auto num_steps = converter.num_steps();

    auto tg_node =
        amf::create_audio_module(audio_modules::ModuleTags::TranceGate);
}

//-----------------------------------------------------------------------------
TEST(audio_modules_factory_test, test_trance_gate_step_count_converter)
{
    using amf = audio_modules::ModuleFactoryImpl;
    const auto mod_infos =
        amf::param_infos(audio_modules::ModuleTags::TranceGate);
    const auto converters =
        amf::convert_funcs(audio_modules::ModuleTags::TranceGate);
    auto const converter = converters.at(
        audio_modules::trance_gate::Config::ConvertTags::step_count);

    /*
        // TODO: Fix later
        const auto phys   = converter.to_physical(0.0322);
        int const rounded = static_cast<int>(phys);
        int rounded_2     = phys;
        EXPECT_TRUE(rounded == 2);
    */

    auto const converter_percent =
        converters.at(audio_modules::trance_gate::Config::ConvertTags::percent);

    float phys_rs = converter_percent.to_physical(0.25);
    EXPECT_TRUE(phys_rs == 25);

    float norm_rs = converter_percent.to_normalised(75);
    EXPECT_TRUE(norm_rs == 0.75);

    std::string display = converter_percent.to_string(75);
    EXPECT_TRUE(display == "75.00");

    auto from_display = converter_percent.from_string("66");
    EXPECT_TRUE(from_display == 66);
}

//-----------------------------------------------------------------------------
TEST(audio_modules_factory_test, test_trance_gate_contour_converter)
{
    using amf = audio_modules::ModuleFactoryImpl;
    const auto mod_infos =
        amf::param_infos(audio_modules::ModuleTags::TranceGate);
    const auto converters =
        amf::convert_funcs(audio_modules::ModuleTags::TranceGate);
    auto const converter =
        converters.at(audio_modules::trance_gate::Config::ConvertTags::contour);

    EXPECT_FLOAT_EQ(converter.to_physical(0.25), 0.665277243);
    EXPECT_FLOAT_EQ(converter.to_physical(0.5), 0.250000238);
    EXPECT_FLOAT_EQ(converter.to_physical(0.75), 0.0875945091);
}

//-----------------------------------------------------------------------------
} // namespace