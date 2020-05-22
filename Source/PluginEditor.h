// Based off of the juce example code

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class GreaterThanAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    GreaterThanAudioProcessorEditor (GreaterThanAudioProcessor&);
    ~GreaterThanAudioProcessorEditor();

    void paint (Graphics&) override;
    void resized() override;

private:

    void sliderValueChanged(Slider* slider) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GreaterThanAudioProcessor& processor;

    // the UI objects
    Slider wet;
    Slider dry;
    Slider gate;
    Slider oct;

    // incorporated custom font for fun
    Font coolvetica = (Font(Typeface::createSystemTypefaceFor(BinaryData::coolvetica_rg_ttf, BinaryData::coolvetica_rg_ttfSize)));

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GreaterThanAudioProcessorEditor)
};
