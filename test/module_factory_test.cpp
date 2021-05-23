// Copyright(c) 2021 Hansen Audio.

#include "gtest/gtest.h"

#include "ha/audio_modules/audio_modules.h"

using namespace ha;

namespace {

//-----------------------------------------------------------------------------
//  Tests
//-----------------------------------------------------------------------------
TEST(module_factory_test, test_get_param_infos)
{
    using mf   = audio_modules::module_factory;
    using tags = audio_modules::module_tags;

    auto const param_infos = mf::param_infos(tags::TRANCE_GATE);
    EXPECT_FALSE(param_infos.empty());
}

//-----------------------------------------------------------------------------
} // namespace