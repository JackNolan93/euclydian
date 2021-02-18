
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "EuclydianComponent.h"

class EuclydianAudioProcessorEditor
    : public juce::AudioProcessorEditor
{
public:
    EuclydianAudioProcessorEditor (EuclydianAudioProcessor&);
    ~EuclydianAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EuclydianAudioProcessorEditor)

    EuclydianAudioProcessor & audioProcessor;

    juce::Slider _tempoSlider;
    juce::Label  _tempoLabel;
    juce::Label  _tempoValueLabel;
    
    juce::Slider _stepsSlider;
    juce::Label  _stepsLabel;
    juce::Label  _numStepsLabel;

    juce::Label  _title { "Euclydian" };
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> speedAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> stepsAttachment;

    EuclydianComponent _euclydianComponent;

    static constexpr int componentInset = 10;


};
