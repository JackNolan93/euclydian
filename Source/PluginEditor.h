
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

    juce::Slider _speedSlider;
    juce::Label  _speedLabel;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> speedAttachment;

    EuclydianComponent _euclydianComponent;

    static constexpr int componentInset = 10;


};
