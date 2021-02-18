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
    
    speedAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (p.treeState, "SPEED", _speedSlider);

    addAndMakeVisible (_speedSlider);
    _speedSlider.setRange (0.0, 1.0);
    _speedSlider.setValue (0.5);
    _speedSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    _speedSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    _speedSlider.onValueChange = [this] {  };

    addAndMakeVisible (_speedLabel);
    _speedLabel.setText ("Num Steps On", juce::dontSendNotification);
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

    _speedSlider.setBounds (componentInset, componentInset, sliderSize, sliderSize);
    _speedLabel .setBounds (_speedSlider.getX (), _speedSlider.getBottom (), sliderSize, 30);
}
