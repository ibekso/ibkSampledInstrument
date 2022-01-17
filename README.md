# Ibekso Sampled Instrument

## Description

### Overview

**Ibekso Sampled Instrument _(Ibksi)_** is meant to be used as a template for building sampled instruments with [JUCE](https://juce.com) 6.x framework.

### Roadmap

As **_Ibksi_** is meant to be a template, it will continue evolving and will try to reamin as modular as possible. The next features will be:
- multimsampling support
- add FXs
- UI improvments
- generic installation setup

*If you have ideas or requests, do not hesitate to open issues in the repository.*

<img src="Assets/ibksi.png" width="654" height=306>

---
## Installation

### Building sources

So far there is not automatic installer for **_Ibksi_**, you have to build the source through the [Projucer](https://docs.juce.com/master/tutorial_new_projucer_project.html).

### Setup samples directory

To setup your samples directory, you have to modify the `samplesDir` variable in the `UtilsFiles.h` --> `createSamplesInputStream()` [L15] so it points to the folder where you store your samples.

By default, it is set as a regular MacOS installation at the following destination: `Library/Application Support/Ibekso/ibkSampledInstrument/Samples/`.

```cpp
auto samplesDir = juce::File::getSpecialLocation (juce::File::commonApplicationDataDirectory)
                        .getChildFile ("Application Support")
                        .getChildFile ("Ibekso")
                        .getChildFile ("ibkSampledInstrument")
                        .getChildFile ("Samples");
```
### Integrate your samples

To integrate your own samples, you have 2 different options:
1. Name your sample `os_synth.wav`
2. Modify the its name in `PluginProcessor.cpp` --> `createSamplesInputStream()` [L37]. 

```cpp
std::unique_ptr<juce::AudioFormatReader> audioReader (wavFormat.createReaderFor (createSamplesInputStream ("os_synth.wav").release(), true));
```

Please note that only `.wav` files and one shot sampling are supported as of `v0.1.0`.