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

    void setNumOnSteps (int numOnSteps);

    void setStepOnIndex (int onIndex);

private:

    void caluclateOnSteps ();

    int _onIndex = 0;
    int _stepIndex = 0;

    int _numSteps = 16;
    int _numOnSteps = 9;

    juce::Array <int> _onSteps;
    juce::Array <std::pair <int, int>> _centerPoints;

};
