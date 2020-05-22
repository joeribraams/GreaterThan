// Based off of the juce example code

#include "PluginProcessor.h"
#include "PluginEditor.h"

GreaterThanAudioProcessor::GreaterThanAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // init parameters with starting values, will be overwritten if instance has been opened before
    addParameter(wet  = new AudioParameterFloat("wet",  "Wet",  0.0f, 1.0f, 0.1f));
    addParameter(dry  = new AudioParameterFloat("dry",  "Dry",  0.0f, 1.0f, 1.0f));
    addParameter(gate = new AudioParameterFloat("gate", "Gate", 0.0f, 0.5f, 0.2f));
    addParameter(oct  = new AudioParameterFloat("oct",  "Oct",  0.0f, 1.0f, 0.0f));
}

GreaterThanAudioProcessor::~GreaterThanAudioProcessor()
{
}

const String GreaterThanAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GreaterThanAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GreaterThanAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GreaterThanAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GreaterThanAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GreaterThanAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GreaterThanAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GreaterThanAudioProcessor::setCurrentProgram (int index)
{
}

const String GreaterThanAudioProcessor::getProgramName (int index)
{
    return {};
}

void GreaterThanAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void GreaterThanAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void GreaterThanAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GreaterThanAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GreaterThanAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {

        auto* inBuffer = buffer.getReadPointer(channel % totalNumInputChannels);
        auto* outBuffer = buffer.getWritePointer (channel);

        // ..do something to the data...
        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            // add the octave up to the input signal
            input = (1 - *oct) * inBuffer[sample] + *oct * abs(inBuffer[sample]);
            // Do the comparisor and add dry signal
            outBuffer[sample] = (input > *gate) * *wet  + inBuffer[sample] * *dry;
        }
    }
}

bool GreaterThanAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GreaterThanAudioProcessor::createEditor()
{
    return new GreaterThanAudioProcessorEditor (*this);
}

void GreaterThanAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr<XmlElement> xml(new XmlElement("GreaterThan"));
    xml->setAttribute("wet",  (double)*wet);
    xml->setAttribute("dry",  (double)*dry);
    xml->setAttribute("gate", (double)*gate);
    xml->setAttribute("oct",  (double)*oct);
    copyXmlToBinary(*xml, destData);
}

void GreaterThanAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName("GreaterThan"))
        {
            *wet  = (float)xmlState->getDoubleAttribute("wet",  0.1);
            *dry  = (float)xmlState->getDoubleAttribute("dry",  1.0);
            *gate = (float)xmlState->getDoubleAttribute("gate", 0.2);
            *oct  = (float)xmlState->getDoubleAttribute("oct",  0.0);
        }
    }
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GreaterThanAudioProcessor();
}
