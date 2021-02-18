#pragma once

#include <JuceHeader.h>


class EuclydianComponent
    : public juce::Component
{
public:
    EuclydianComponent ();
    ~EuclydianComponent ();

    void resized () override;
    void paint (juce::Graphics & g) override;

private:

    void caluclateOnSteps (); 

    int _numSteps = 16;
    int _numOnSteps = 9;
    juce::Array <int> _onSteps;

};
