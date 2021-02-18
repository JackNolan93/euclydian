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

    auto radius = (getWidth () - 30) / 2;
    auto centreX = 15 + radius;
    auto centreY = 15 + radius;

    auto stepMarkerSize = 12;
    auto onMarkerSize = 24;

    _stepIndex = 0;

    g.drawEllipse (15,
                   15,
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

            juce::Path newPath;
            newPath.addPieSegment (x - onMarkerSize / 2, y - onMarkerSize / 2, onMarkerSize, onMarkerSize, 0, 2 * juce::MathConstants< float >::pi, 0.7);

            if (_stepIndex == _onIndex)
                g.fillPath (newPath);

            ++_stepIndex;
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
        g.setColour (juce::Colours::white);
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

void EuclydianComponent::setStepOnIndex (int onIndex)
{
    _onIndex = onIndex;

    juce::MessageManager::callAsync ([this] ()
     { repaint (); });
}
