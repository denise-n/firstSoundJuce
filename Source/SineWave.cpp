#include "SineWave.h"

#include <cmath>

void SineWave::prepare(const double sampleRate, const int numChannels) {
    currentSampleRate = static_cast<float>(sampleRate);
    timeIncrement = 1.0f / currentSampleRate;
    currentTime.resize(numChannels, 0.0f);
}

void SineWave::process(juce::AudioBuffer<float>& buffer) {
    // process loop will not complete unless prepare method has been called first
    if (currentTime.size() != buffer.getNumChannels())
        return;

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto* output = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample ) {
            output[sample] = amplitude * std::sinf(juce::MathConstants<float>::twoPi * frequency * currentTime[channel]);
            currentTime[channel]  = currentTime[channel] + timeIncrement;

        }
    }
}
