/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTrial2AudioProcessor::GainTrial2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, "PARAMETERS", {std::make_unique<AudioParameterFloat>("GainId", "Gain", -48, 0, -15)})
#endif
{
}

GainTrial2AudioProcessor::~GainTrial2AudioProcessor()
{
    parameters.state = ValueTree("Parameters");
}

//==============================================================================
const String GainTrial2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainTrial2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainTrial2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainTrial2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainTrial2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainTrial2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainTrial2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainTrial2AudioProcessor::setCurrentProgram (int index)
{
}

const String GainTrial2AudioProcessor::getProgramName (int index)
{
    return {};
}

void GainTrial2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GainTrial2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    previousGain = pow(10, *parameters.getRawParameterValue("GainId") / 20);
}

void GainTrial2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainTrial2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void GainTrial2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    float currentGain = pow(10, *parameters.getRawParameterValue("GainId") / 20);
    
    if (currentGain == previousGain) {
        buffer.applyGain(currentGain);
    } else {
        buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, currentGain);
        previousGain = currentGain; 
    }
    
    
    /*
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
            channelData[sample] = buffer.getSample(channel, sample) * volume;
        }

    }
     */
}

//==============================================================================
bool GainTrial2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GainTrial2AudioProcessor::createEditor()
{
    return new GainTrial2AudioProcessorEditor (*this);
}

//==============================================================================
void GainTrial2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    ScopedPointer<XmlElement> xml(parameters.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void GainTrial2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ScopedPointer<XmlElement> theParameters(getXmlFromBinary(data, sizeInBytes));
    if (theParameters->hasTagName((parameters.state.getType()))) {
        parameters.state = ValueTree::fromXml(*theParameters);
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainTrial2AudioProcessor();
}
