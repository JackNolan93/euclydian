/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EuclydianAudioProcessorEditor::EuclydianAudioProcessorEditor (EuclydianAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 450);

    addAndMakeVisible (_stepsOnSlider);
    _stepsOnSlider.setRange (1, 16);
    _stepsOnSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    _stepsOnSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    _stepsOnSlider.onValueChange = [this] {  };

    addAndMakeVisible (_stepsOnLabel);
    _stepsOnLabel.setText ("Num Steps On", juce::dontSendNotification);
}

EuclydianAudioProcessorEditor::~EuclydianAudioProcessorEditor()
{
}

//==============================================================================
void EuclydianAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EuclydianAudioProcessorEditor::resized()
{
    auto sliderSize = 100;

    _stepsOnSlider.setBounds (componentInset, componentInset, sliderSize, sliderSize);
    _stepsOnLabel .setBounds (_stepsOnSlider.getX (), _stepsOnSlider.getBottom (), sliderSize, 30);
}
