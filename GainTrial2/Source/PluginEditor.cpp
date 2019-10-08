/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainTrial2AudioProcessorEditor::GainTrial2AudioProcessorEditor (GainTrial2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 300);
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 50, 20);
    gainSlider.setRange(-48, 0);
    gainSlider.setValue(-15);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.addListener(this);
    
    sliderAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "GainId", gainSlider);
}

GainTrial2AudioProcessorEditor::~GainTrial2AudioProcessorEditor()
{
}

//==============================================================================
void GainTrial2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::grey);
}

void GainTrial2AudioProcessorEditor::resized()
{
    gainSlider.setBounds(getLocalBounds());
}

void GainTrial2AudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &gainSlider) {
        processor.volume = pow(10, slider->getValue() / 20);
    }
}
