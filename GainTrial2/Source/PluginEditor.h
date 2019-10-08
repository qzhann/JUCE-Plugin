/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class GainTrial2AudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    GainTrial2AudioProcessorEditor (GainTrial2AudioProcessor&);
    ~GainTrial2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainTrial2AudioProcessor& processor;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainTrial2AudioProcessorEditor)
    
public:
    Slider gainSlider;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderAttachment;
};
