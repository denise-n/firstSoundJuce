#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <juce_gui_basics/juce_gui_basics.h>


//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    frequencySlider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    frequencySlider.setRange(0.0f, 1.0f, 0.01f);
    addAndMakeVisible(frequencySlider);

    // play button
    playButton.setButtonText("Playing");
    playButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    playButton.setClickingTogglesState(true);
    playButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    playButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);

    playButton.onClick = [this]()
    {
        // change state of button when clicked
        const bool isPlaying = playButton.getToggleState();
        playButton.setButtonText(isPlaying ? "Playing" : "Bypassed");
    };
    addAndMakeVisible(playButton);

    // frequency label
    frequencyLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(frequencyLabel);

    setSize (400, 400);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{

    // frequencyLabel.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 120, 100, 20);
    // frequencySlider.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 100, 100, 200);
    // playButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 + 120, 100, 20);

     juce::FlexBox flexbox;
     flexbox.flexDirection = juce::FlexBox::Direction::column;
     flexbox.justifyContent = juce::FlexBox::JustifyContent::center;
     flexbox.alignItems = juce::FlexBox::AlignItems::center;

     flexbox.items.add(juce::FlexItem(frequencyLabel).withMinHeight(20).withMinWidth(100));
     flexbox.items.add(juce::FlexItem(frequencySlider).withMinHeight(200).withMinWidth(100).withMargin(juce::FlexItem::Margin(0, 0, 10, 0)));
     flexbox.items.add(juce::FlexItem(playButton).withMinHeight(20).withMinWidth(100));

     flexbox.performLayout(getLocalBounds());
}
