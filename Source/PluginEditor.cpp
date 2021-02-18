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
    stepsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (p.treeState, "STEPS", _stepsSlider);

    addAndMakeVisible (_speedSlider);
    _speedSlider.setRange (0.0, 1.0);
    _speedSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    _speedSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    _speedSlider.onValueChange = [this] {  };

    addAndMakeVisible (_speedLabel);
    _speedLabel.setText ("Tempo", juce::dontSendNotification);
    _speedLabel.setJustificationType (juce::Justification::centred);
    _speedLabel.setFont (12.f);
    
    addAndMakeVisible (_stepsSlider);
    _stepsSlider.setRange (1, 16);
    _stepsSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    _stepsSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    _stepsSlider.onValueChange = [this]
    {
        _euclydianComponent.setNumOnSteps (int (_stepsSlider.getValue ()));
        audioProcessor.updateSteps ();
    };

    addAndMakeVisible (_stepsLabel);
    _stepsLabel.setText ("Number Of Steps", juce::dontSendNotification);
    _stepsLabel.setJustificationType (juce::Justification::centred);
    _stepsLabel.setFont (12.f);


    addAndMakeVisible (_euclydianComponent);
}

EuclydianAudioProcessorEditor::~EuclydianAudioProcessorEditor()
{
}

//==============================================================================
void EuclydianAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void EuclydianAudioProcessorEditor::resized()
{
    auto sliderSize = 100;

    _speedSlider.setBounds (componentInset, componentInset, sliderSize, sliderSize);
    _speedLabel .setBounds (_speedSlider.getX (), _speedSlider.getBottom () - componentInset, sliderSize, 20);

    _euclydianComponent. setBounds (getWidth () / 4 ,
                                    getHeight () / 2 - getWidth () / 4,
                                    getWidth () / 2,
                                    getWidth () / 2);
    
    _stepsSlider.setBounds (getLocalBounds().getWidth() - (componentInset + sliderSize), componentInset, sliderSize, sliderSize);
    _stepsLabel.setBounds (_stepsSlider.getX (), _stepsSlider.getBottom (), sliderSize, 30);

    _euclydianComponent. setBounds (getWidth () / 4 ,
                                    getHeight () / 2 - getWidth () / 4,
                                    getWidth () / 2,
                                    getWidth () / 2);
}
