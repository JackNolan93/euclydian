#include "EuclydianComponent.h"

EuclydianComponent::EuclydianComponent ()
{
    caluclateOnSteps ();
}

EuclydianComponent::~EuclydianComponent ()
{
}

void EuclydianComponent::resized ()
{

}

void EuclydianComponent::paint (juce::Graphics & g)
{
    g.setColour (juce::Colours::white);

    auto radius = (getWidth () - 20) / 2;
    auto centreX = 10 + radius;
    auto centreY = 10 + radius;

    auto stepMarkerSize = 14;

    g.drawEllipse (10,
                   10,
                   radius * 2,
                   radius * 2,
                   1.0);

    for (int i = 0; i < _numSteps; ++i)
    {
        auto angleInRadians = i * ((2 * juce::MathConstants< float >::pi) / _numSteps);
        auto x = centreX + cos (angleInRadians) * radius;
        auto y = centreY + sin (angleInRadians) * radius;

        if (_onSteps.contains (i))
        {
            g.fillEllipse (x - stepMarkerSize / 2,
                           y - stepMarkerSize / 2,
                           stepMarkerSize,
                           stepMarkerSize);


        }
        else
        {
            g.drawEllipse (x - stepMarkerSize / 2,
                           y - stepMarkerSize / 2,
                           stepMarkerSize,
                           stepMarkerSize,
                           1.0);
        }
    }

}

void EuclydianComponent::caluclateOnSteps ()
{
    _onSteps.clear ();
    auto interval = float (_numSteps) / float (_numOnSteps);

    for (int i = 0; i < _numSteps; ++i)
    {
        auto pos = i * interval;
        _onSteps.add (juce::roundToInt (pos));
    }

    repaint ();
}
