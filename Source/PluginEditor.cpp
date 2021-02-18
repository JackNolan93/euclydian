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
    setSize (650, 500);
    
    speedAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (p.treeState, "TEMPO", _tempoSlider);
    stepsAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (p.treeState, "STEPS", _stepsSlider);

    addAndMakeVisible (_tempoSlider);
    _tempoSlider.setRange (20.0, 200.0);
    _tempoSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    _tempoSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    _tempoSlider.onValueChange = [this, &p]
    {
        audioProcessor.updateTempo ();
    };
    _tempoSlider.setPopupDisplayEnabled(true, true, this);

    addAndMakeVisible (_tempoLabel);
    _tempoLabel.setText ("Tempo", juce::dontSendNotification);
    _tempoLabel.setJustificationType (juce::Justification::centred);
    _tempoLabel.setFont (12.f);
    
    addAndMakeVisible (_stepsSlider);
    _stepsSlider.setRange (1, 16);
    _stepsSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    _stepsSlider.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    _stepsSlider.onValueChange = [this, &p]
    {
        _euclydianComponent.setNumOnSteps (*p.treeState.getRawParameterValue ("STEPS"));
        audioProcessor.updateSteps ();

        _numStepsLabel.setText (juce::String (*p.treeState.getRawParameterValue ("STEPS")), juce::dontSendNotification);
    };

    addAndMakeVisible (_numStepsLabel);
    _numStepsLabel.setJustificationType (juce::Justification::centred);
    _numStepsLabel.setFont (16.f);
    _numStepsLabel.setInterceptsMouseClicks (false, false);
    _numStepsLabel.setText (juce::String (*p.treeState.getRawParameterValue ("STEPS")), juce::dontSendNotification);

    addAndMakeVisible (_stepsLabel);
    _stepsLabel.setText ("Number Of Steps", juce::dontSendNotification);
    _stepsLabel.setJustificationType (juce::Justification::centred);
    _stepsLabel.setFont (12.f);


    addAndMakeVisible (_euclydianComponent);
    _euclydianComponent.setNumOnSteps (int (_stepsSlider.getValue ()));

    p._stepChange = [this] (int stepIndex) { _euclydianComponent.setStepOnIndex (stepIndex); };
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

    _tempoSlider.setBounds (componentInset, componentInset, sliderSize, sliderSize);
    _tempoLabel .setBounds (_tempoSlider.getX (), _tempoSlider.getBottom () - componentInset, sliderSize, 20);
    
    _stepsSlider.setBounds (getLocalBounds().getWidth() - (componentInset + sliderSize), componentInset, sliderSize, sliderSize);
    _stepsLabel.setBounds (_stepsSlider.getX (), _stepsSlider.getBottom () - componentInset, sliderSize, 20);
    _numStepsLabel.setBounds (_stepsSlider.getBounds ());

    _euclydianComponent. setBounds (getWidth () / 4 ,
                                    getHeight () / 2 - getWidth () / 4,
                                    getWidth () / 2,
                                    getWidth () / 2);
}
