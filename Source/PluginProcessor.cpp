/*
  ==============================================================================

    PluginProcessor.cpp
 
    Copyright (C) 2022 Francois Decourcelle

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
IbkSampledInstrumentAudioProcessor::IbkSampledInstrumentAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Setup voices
    for (int i = 0; i < mNumVoices; i++)
    {
        mSampledInstrument.addVoice (new juce::SamplerVoice());
    }
    
    // Setup sampled sound
    mSampledInstrument.clearSounds();
    juce::WavAudioFormat wavFormat;
    
    std::unique_ptr<juce::AudioFormatReader> audioReader (wavFormat.createReaderFor (createSampleInputStream ("os_synth.wav").release(), true));
    
    juce::BigInteger allNotes;
    allNotes.setRange (0, 128, true);
    
    mSampledInstrument.clearSounds();
    mSampledInstrument.addSound (new juce::SamplerSound ("vox",         // name
                                                         *audioReader,  // source
                                                         allNotes,      // midi notes range
                                                         74,            // root midi note
                                                         0.1,           // attack time (sec)
                                                         0.1,           // release time (sec)
                                                         10.0           // maximum sample length (sec)
                                                         ));
}

IbkSampledInstrumentAudioProcessor::~IbkSampledInstrumentAudioProcessor()
{
}

//==============================================================================
const juce::String IbkSampledInstrumentAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool IbkSampledInstrumentAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool IbkSampledInstrumentAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool IbkSampledInstrumentAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double IbkSampledInstrumentAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int IbkSampledInstrumentAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int IbkSampledInstrumentAudioProcessor::getCurrentProgram()
{
    return 0;
}

void IbkSampledInstrumentAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String IbkSampledInstrumentAudioProcessor::getProgramName (int index)
{
    return {};
}

void IbkSampledInstrumentAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void IbkSampledInstrumentAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSampledInstrument.setCurrentPlaybackSampleRate (sampleRate);
}

void IbkSampledInstrumentAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool IbkSampledInstrumentAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void IbkSampledInstrumentAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    mSampledInstrument.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool IbkSampledInstrumentAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* IbkSampledInstrumentAudioProcessor::createEditor()
{
    return new IbkSampledInstrumentAudioProcessorEditor (*this);
}

//==============================================================================
void IbkSampledInstrumentAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void IbkSampledInstrumentAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IbkSampledInstrumentAudioProcessor();
}
