/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EuclydianAudioProcessor::EuclydianAudioProcessor()
     : AudioProcessor (BusesProperties().withInput("Input", juce::AudioChannelSet::mono(), true))
{
    addParameter (speed = new juce::AudioParameterFloat ("speed", "Arpeggiator Speed", 0.0, 1.0, 0.5));
}

EuclydianAudioProcessor::~EuclydianAudioProcessor()
{
}

//==============================================================================
const juce::String EuclydianAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EuclydianAudioProcessor::acceptsMidi() const
{
    return true;
}

bool EuclydianAudioProcessor::producesMidi() const
{
    return true;
}

bool EuclydianAudioProcessor::isMidiEffect() const
{
    return true;
}

double EuclydianAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EuclydianAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EuclydianAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EuclydianAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EuclydianAudioProcessor::getProgramName (int index)
{
    return {};
}

void EuclydianAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EuclydianAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused (samplesPerBlock);
    notes.clear();
    currentNote = 0;
    lastNoteValue = -1;
    time = 0;
    rate = static_cast<float> (sampleRate);
}

void EuclydianAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EuclydianAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{

}
#endif

void EuclydianAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // however we use the buffer to get timing information
    auto numSamples = buffer.getNumSamples();

    // get note duration
    auto noteDuration = static_cast<int> (std::ceil (rate * 0.25f * (0.1f + (1.0f - (*speed)))));

    for (const auto metadata : midiMessages)
    {
        const auto msg = metadata.getMessage();
        if      (msg.isNoteOn())  notes.add (msg.getNoteNumber());
        else if (msg.isNoteOff()) notes.removeValue (msg.getNoteNumber());
    }

    midiMessages.clear();

    if ((time + numSamples) >= noteDuration)
    {
        auto offset = juce::jmax (0, juce::jmin ((int) (noteDuration - time), numSamples - 1));

        if (lastNoteValue > 0)
        {
            midiMessages.addEvent (juce::MidiMessage::noteOff (1, lastNoteValue), offset);
            lastNoteValue = -1;
        }

        if (notes.size() > 0)
        {
            currentNote = (currentNote + 1) % notes.size();
            lastNoteValue = notes[currentNote];
            midiMessages.addEvent (juce::MidiMessage::noteOn  (1, lastNoteValue, (juce::uint8) 127), offset);
        }

    }

    time = (time + numSamples) % noteDuration;
    
}

//==============================================================================
bool EuclydianAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EuclydianAudioProcessor::createEditor()
{
    return new EuclydianAudioProcessorEditor (*this);
}

//==============================================================================
void EuclydianAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream (destData, true).writeFloat (*speed);
}

void EuclydianAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    speed->setValueNotifyingHost (juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat());
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EuclydianAudioProcessor();
}
