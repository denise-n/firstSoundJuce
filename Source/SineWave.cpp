#include "SineWave.h"

#include <cmath>
// #include <juce_audio_basics/buffers/juce_AudioSampleBuffer.h>
// #include <juce_core/maths/juce_MathsFunctions.h>
// #include <JuceHeader.h>


void SineWave::prepare(const double sampleRate, const int numChannels) {
    currentSampleRate = static_cast<float>(sampleRate);
    timeIncrement = 1.0f / currentSampleRate;
    currentTime.resize(numChannels, 0.0f);
}

void SineWave::process(juce::AudioBuffer<float>& buffer) {
    if (currentTime.size() != buffer.getNumChannels())
        return;

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto* output = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample ) {
            output[sample] = amplitude * std::sinf(juce::MathConstants<float>::twoPi) * frequency * currentTime[channel];
            currentTime[channel]  = currentTime[channel] + timeIncrement;

        }
    }
}
