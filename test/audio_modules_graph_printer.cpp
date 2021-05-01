// Copyright(c) 2021 Hansen Audio.

#include "ha/audio_components/trance_gate_processor.h"
#include "ha/audio_graph/module.h"

#include <kompositum/builder.h>
#include <kompositum/component.h>
#include <kompositum/composite.h>
#include <kompositum/leaf.h>
#include <kompositum/util.h>

#include <map>
#include <memory>
#include <string>

using namespace ha;
using namespace Kompositum;

namespace {

//-----------------------------------------------------------------------------
enum
{
    COMPOSITE_ROOT_ID   = 0,
    COMPONENT_PLUGIN_ID = COMPOSITE_ROOT_ID,
    COMPONENT_PARENT_01_ID,
    COMPONENT_OTHER_01,
    COMPONENT_OTHER_02,
    COMPONENT_OTHER_03,
    COMPONENT_OTHER_04,
    COMPONENT_UP_SAMPLER,
    COMPONENT_DOWN_SAMPLER,
    NUM_COMPOSITES

};
//-----------------------------------------------------------------------------
static ParentChildTreeDef const kTreeDef = {
    {COMPONENT_PLUGIN_ID, COMPONENT_PARENT_01_ID},
    {COMPONENT_PARENT_01_ID, COMPONENT_UP_SAMPLER},
    {COMPONENT_PARENT_01_ID, COMPONENT_OTHER_01},
    {COMPONENT_PARENT_01_ID, COMPONENT_OTHER_02},
    {COMPONENT_PARENT_01_ID, COMPONENT_OTHER_03},
    {COMPONENT_PARENT_01_ID, COMPONENT_OTHER_04},
    {COMPONENT_PARENT_01_ID, COMPONENT_DOWN_SAMPLER},
};

auto const kComponentTree = buildComposite(COMPOSITE_ROOT_ID, kTreeDef);

using string_type                         = std::string const;
using ComponentMap                        = std::map<Kompositum::IDType, string_type> const;
static ComponentMap const kComponentNames = {
    {COMPONENT_PLUGIN_ID, "Plugin"},
    {COMPONENT_PARENT_01_ID, "Parent-01"},
    {COMPONENT_OTHER_01, "Other-01"},
    {COMPONENT_OTHER_02, "Other-02"},
    {COMPONENT_OTHER_03, "Other-03"},
    {COMPONENT_OTHER_04, "Other-04"},
    {COMPONENT_UP_SAMPLER, "UpSampler"},
    {COMPONENT_DOWN_SAMPLER, "DownSampler"},
};

/*
 * other_processor
 */
class other_processor : public audio_graph::module
{
public:
    //-------------------------------------------------------------------------
    other_processor() = default;

    bool process_audio(audio_graph::process_data& data) override
    {
        printf(" > processing()...(%.1fx)", data.oversampling_factor);
        return true;
    }

    void setup_processing(audio_graph::process_setup& setup) override {}
    //-------------------------------------------------------------------------
private:
};

/*
 * resampler_processor
 */
class resampler_processor : public audio_graph::module
{
public:
    //-------------------------------------------------------------------------
    resampler_processor() = default;

    bool process_audio(audio_graph::process_data& data) override
    {
        if (sample_up)
            printf(" > processing()... (%.1fx -> 2.0x)", data.oversampling_factor);
        else
            printf(" > processing()... (%.1fx -> 1.0x)", data.oversampling_factor);

        data.oversampling_factor = sample_up == true ? 2.f : 1.f;
        sample_up                = !sample_up;

        return true;
    }

    void setup_processing(audio_graph::process_setup& setup) override {}
    //-------------------------------------------------------------------------
private:
    bool sample_up = true;
};

/*
 * root_processor
 */
class root_processor
: public Visitor
, public audio_graph::module
{
public:
    //-------------------------------------------------------------------------
    root_processor()
    {
        auto resampler        = std::make_shared<resampler_processor>();
        audio_components_list = {
            {COMPONENT_PARENT_01_ID, std::make_shared<ha::audio_modules::tg_processor>()},
            {COMPONENT_OTHER_01, std::make_shared<other_processor>()},
            {COMPONENT_OTHER_02, std::make_shared<other_processor>()},
            {COMPONENT_OTHER_03, std::make_shared<other_processor>()},
            {COMPONENT_OTHER_04, std::make_shared<other_processor>()},
            {COMPONENT_UP_SAMPLER, resampler},
            {COMPONENT_DOWN_SAMPLER, resampler}};

        audio_process_data.output_busses.resize(1);
        audio_process_data.output_busses.at(0).resize(2);
        audio_process_data.output_busses.at(0).at(0).resize(32);
        audio_process_data.output_busses.at(0).at(1).resize(32);
    }

    bool process_audio(audio_graph::process_data& _data) override
    {
        audio_process_data = _data;
        printf(" > processing...");
        return true;
    }

    void setup_processing(audio_graph::process_setup& setup) override
    {
        for (auto& component : audio_components_list)
        {
            component.second->setup_processing(setup);
        }
    }

    void visit(Leaf* leaf) override
    {
        if (!leaf)
            return;

        doIndentation();
        auto const& name = kComponentNames.at(leaf->getID());
        printf("- Leaf (%s) (%Ilu)", name.data(), leaf->getID());

        auto element = audio_components_list.at(leaf->getID());
        (*element).process_audio(audio_process_data);
        printf("\n");
    }

    void visit(Composite* composite) override
    {
        if (!composite)
            return;

        doIndentation();
        indent++;

        auto const& name = kComponentNames.at(composite->getID());
        if (!composite->hasChildren())
        {
            printf("- Composite (%s) (%Ilu): empty", name.data(), composite->getID());
            printf("\n");
        }
        else
        {
            printf("- Composite (%s) (%Ilu)", name.data(), composite->getID());
            auto iter = audio_components_list.find(composite->getID());
            if (iter != audio_components_list.end())
            {
                (*iter).second->process_audio(audio_process_data);
            }
            else
            {
                process_audio(audio_process_data);
            }
            printf("\n");
            composite->visitChildren(*this);
        }

        indent--;
    }

    //-------------------------------------------------------------------------
private:
    void doIndentation() const
    {
        for (auto i = 0u; i < indent; ++i)
        {
            printf("+--");
        }
    }

    unsigned int indent = 0;

    using audio_processor_ptr = std::shared_ptr<audio_graph::module>;
    using audio_modules       = std::map<IDType, audio_processor_ptr>;
    audio_modules audio_components_list;

    audio_graph::process_data audio_process_data;
};

//-----------------------------------------------------------------------------
} // namespace

int main()
{
    root_processor processor;
    audio_graph::process_setup setup;
    processor.setup_processing(setup);
    audio_graph::process_data audio_process_data;
    kComponentTree->accept(processor);
}