// Copyright(c) 2021 Hansen Audio.

#include "gtest/gtest.h"

#include "hao/audio_modules/audio_modules.h"

using namespace ha;

namespace {

//-----------------------------------------------------------------------------
//  Tests
//-----------------------------------------------------------------------------
TEST(module_factory_test, test_get_param_infos)
{
    using mf   = audio_modules::ModuleFactoryImpl;
    using tags = audio_modules::ModuleTags;

    auto const param_infos = mf::param_infos(tags::TranceGate);
    EXPECT_FALSE(param_infos.empty());
}

//-----------------------------------------------------------------------------
} // namespace