/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class EuclydianAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EuclydianAudioProcessorEditor (EuclydianAudioProcessor&);
    ~EuclydianAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EuclydianAudioProcessorEditor)

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EuclydianAudioProcessor & audioProcessor;

    juce::Slider _speedSlider;
    juce::Label  _speedLabel;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> speedAttachment;
    
    static constexpr int componentInset = 10;


};
