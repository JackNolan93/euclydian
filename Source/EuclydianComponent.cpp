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
    caluclateOnSteps ();
}

void EuclydianComponent::paint (juce::Graphics & g)
{
    g.setColour (juce::Colours::white);

    _centerPoints.clear ();

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
        g.setColour (juce::Colours::white);

        if (_onSteps.contains (i))
        {
            g.fillEllipse (x - stepMarkerSize / 2,
                           y - stepMarkerSize / 2,
                           stepMarkerSize,
                           stepMarkerSize);

            std::pair <int, int> newPoint = {int (x), int (y)};
            _centerPoints.add (newPoint);
        }
        else
        {
            g.setColour (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
            g.fillEllipse (x - stepMarkerSize / 2,
                           y - stepMarkerSize / 2,
                           stepMarkerSize,
                           stepMarkerSize);

            g.setColour (juce::Colours::white);
            g.drawEllipse (x - stepMarkerSize / 2,
                           y - stepMarkerSize / 2,
                           stepMarkerSize,
                           stepMarkerSize,
                           1.0);
        }
    }

    for (int i = 0; i < _centerPoints.size (); ++i)
    {
        auto start = _centerPoints [i];
        auto end = i + 1 >= _centerPoints.size () ? _centerPoints [0] : _centerPoints [i + 1];

        g.drawLine (start.first, start.second, end.first, end.second, 1.0);
    }

}

void EuclydianComponent::setNumOnSteps (int numOnSteps)
{
    if (_numOnSteps != numOnSteps)
    {
        _numOnSteps = numOnSteps;
        caluclateOnSteps ();
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
