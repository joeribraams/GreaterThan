#include "PluginProcessor.h"
#include "PluginEditor.h"

GreaterThanAudioProcessorEditor::GreaterThanAudioProcessorEditor (GreaterThanAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    // these define the parameters of our slider objects
    wet.setSliderStyle(Slider::LinearBarVertical);
    wet.setColour(Slider::trackColourId, Colour(0x80343d46));
    wet.setColour(Slider::textBoxOutlineColourId, Colour(0x00eeeeee));
    wet.setRange(0.0, 1.0);
    wet.setSkewFactor(0.5, false);
    wet.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    wet.setValue(*processor.wet);

    dry.setSliderStyle(Slider::LinearBarVertical);
    dry.setColour(Slider::trackColourId, Colour(0x80343d46));
    dry.setColour(Slider::textBoxOutlineColourId, Colour(0x00eeeeee));
    dry.setSkewFactor(0.5, false);
    dry.setRange(0.0, 1.0);
    dry.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    dry.setValue(*processor.dry);

    gate.setSliderStyle(Slider::LinearBarVertical);
    gate.setColour(Slider::trackColourId, Colour(0x80343d46));
    gate.setColour(Slider::textBoxOutlineColourId, Colour(0x00eeeeee));
    gate.setSkewFactor(0.3, false);
    gate.setRange(0.0, 0.5);
    gate.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    gate.setValue(*processor.gate);

    oct.setSliderStyle(Slider::LinearBarVertical);
    oct.setColour(Slider::trackColourId, Colour(0x80343d46));
    oct.setColour(Slider::textBoxOutlineColourId, Colour(0x00eeeeee));
    oct.setRange(0.0, 1.0);
    oct.setTextBoxStyle(Slider::NoTextBox, true, 90, 0);
    oct.setValue(*processor.oct);

    // this function adds the sliders to the editor
    addAndMakeVisible(wet);
    addAndMakeVisible(dry);
    addAndMakeVisible(gate);
    addAndMakeVisible(oct);

    // add the listener to the sliders
    wet.addListener(this);
    dry.addListener(this);
    gate.addListener(this);
    oct.addListener(this);
}

GreaterThanAudioProcessorEditor::~GreaterThanAudioProcessorEditor()
{
}

void GreaterThanAudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window eeeeee
    g.fillAll(Colour(0xffeeeeee));

    // set the current drawing colour to grey
    g.setColour(Colour(0xff343d46));

    // set the font and size and draw text to the screen
    g.setFont(Font("coolvetica", 40.0f, 0));
    g.drawFittedText("GREATER > THAN", 0, 2, getWidth(), 30, Justification::centred, 1);

    g.setFont(40.0f);
    g.drawFittedText("WET",  0,                 getHeight() - 35, getWidth() / 4, 30, Justification::centred, 1);
    g.drawFittedText("DRY",  getWidth() * 0.25, getHeight() - 35, getWidth() / 4, 30, Justification::centred, 1);
    g.drawFittedText("GATE", getWidth() * 0.5,  getHeight() - 35, getWidth() / 4, 30, Justification::centred, 1);
    g.drawFittedText("OCT", getWidth() * 0.75, getHeight() - 35, getWidth() / 4, 30, Justification::centred, 1);
}

void GreaterThanAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    wet.setBounds(0,                  1, getWidth() / 4, getHeight() - 2);
    dry.setBounds(getWidth() * 0.25,  1, getWidth() / 4, getHeight() - 2);
    gate.setBounds(getWidth() * 0.5,  1, getWidth() / 4, getHeight() - 2);
    oct.setBounds(getWidth() * 0.75, 1, getWidth() / 4, getHeight() - 2);
}

void GreaterThanAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (*processor.wet != wet.getValue())
    {
        *processor.wet = wet.getValue();
    }

    if (*processor.dry != dry.getValue())
    {
        *processor.dry = dry.getValue();
    }

    if (*processor.gate != gate.getValue())
    {
        *processor.gate = gate.getValue();
    }

    if (*processor.oct != oct.getValue())
    {
        *processor.oct = oct.getValue();
    }
}