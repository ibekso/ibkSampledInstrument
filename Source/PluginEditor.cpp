/*
  ==============================================================================

    PluginEditor.cpp
 
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IbkSampledInstrumentAudioProcessorEditor::IbkSampledInstrumentAudioProcessorEditor (IbkSampledInstrumentAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
}

IbkSampledInstrumentAudioProcessorEditor::~IbkSampledInstrumentAudioProcessorEditor()
{
}

//==============================================================================
void IbkSampledInstrumentAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::blueviolet);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Ibekso Sampled Instrument", getLocalBounds(), juce::Justification::centred, 1);
}

void IbkSampledInstrumentAudioProcessorEditor::resized()
{
}
