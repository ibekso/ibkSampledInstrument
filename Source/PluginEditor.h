/*
  ==============================================================================

    PluginEditor.h
 
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Utils/UtilsFiles.h"

//==============================================================================
/**
*/
class IbkSampledInstrumentAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    IbkSampledInstrumentAudioProcessorEditor (IbkSampledInstrumentAudioProcessor&);
    ~IbkSampledInstrumentAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ImageComponent mImageComponentIbksi;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    IbkSampledInstrumentAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IbkSampledInstrumentAudioProcessorEditor)
};
