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
    auto ibksi = juce::ImageCache::getFromMemory(BinaryData::ibksi_png , BinaryData::ibksi_pngSize);
    
    if (ibksi.isValid())
    {
        mImageComponentIbksi.setImage(ibksi, juce::RectanglePlacement::stretchToFit);
    }
    else{
        jassert(ibksi.isValid());
    }
    
    addAndMakeVisible(mImageComponentIbksi);
    
    setSize (982, 460);
}

IbkSampledInstrumentAudioProcessorEditor::~IbkSampledInstrumentAudioProcessorEditor()
{
}

//==============================================================================
void IbkSampledInstrumentAudioProcessorEditor::paint (juce::Graphics& g)
{
    mImageComponentIbksi.setBounds(0,0,982,460);
}

void IbkSampledInstrumentAudioProcessorEditor::resized()
{
}
