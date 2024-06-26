What's the difference with [dimtass/DSP-Cpp-filters](https://github.com/dimtass/DSP-Cpp-filters)?
----
Filters are classified into 5 types depending on a set of parameters:
- BiquadSimple (`fc` and `fs` only)
- BiquadShelf (`gain_db`, `fc` and `fs`)
- BiquadQ (`Q`, `fc` and `fs`)
- BiquadBand (`bw`, `fc` and `fs`)
- BiquadParametric (`gain_db`, `Q`, `fc` and `fs`)

`fc` is corner frequency, `fs` is sample rate, `bw` is bandwidth, `Q` is quality factor.

Filter parameters are now set in the constructor. You need to call calculate_coeffs() function (which has been made virtual) only when you want to change them all at the same time. Added set_param(), set_fc(), set_fs(), set_gain(), set_Q(), set_bw() functions for the case when you want to change only one parameter. 

Example of usage from [my Android MIDI library](https://github.com/crylent/android-midilib):
```cpp
template<class FilterClass> requires(is_base_of<BiquadSimple, FilterClass>() == true)
void Filter::activateFilter() {
    mActiveFilter = make_unique<FilterClass>(mFrequency, AudioEngine::getSampleRate());
}

float Filter::process(float sample) {
    return mActiveFilter->process(sample);
}
```

[See the full code](https://github.com/crylent/android-midilib/blob/master/library/src/main/cpp/soundfx/Filter.cpp)

DSP filters in C++
----

[![dimtass](https://circleci.com/gh/dimtass/DSP-Cpp-filters.svg?style=svg)](https://circleci.com/gh/dimtass/DSP-Cpp-filters)

This repo contains some DSP biquad filters used in audio. I've extracted those
filters from the `Designing Audio Effect Plug-Ins in C++: With Digital Audio Signal Processing Theory`
book that you can find [here](https://www.amazon.com/Designing-Audio-Effect-Plug-Ins-Processing/dp/0240825152).

I've also implemented a real-time testing on a Cortex-M4 MCU, using the on-chip ADC and DAC. You can find the post [here](https://www.stupid-projects.com/biquad-audio-dsp-filters-using-stm32f303cc-black-pill/).

This is the formula I'm using for the [digital biquad filter](https://en.wikipedia.org/wiki/Digital_biquad_filter)
in the source code:
```
y(n) = a0*x(n) + a1*x(n-1) + a2*x(n-2) - b*y(n-1) + b2*y(n-2)
```

- First order all-pass filter (fo_apf)
- First order high-pass filter (fo_hpf)
- First order low-pass filter (fo_lpf)
- First order high-shelving filter (fo_shelving_high)
- First order low-shelving filter (fo_shelving_low)
- Second order all-pass filter (so_apf)
- Second order band-pass filter (so_bpf)
- Second order band-stop filter (so_bsf)
- Second order Butterworth band-pass filter (so_butterworth_bpf)
- Second order Butterworth band-stop filter (so_butterworth_bsf)
- Second order Butterworth high-pass filter (so_butterworth_hpf)
- Second order Butterworth low-pass filter (so_butterworth_lpf)
- Second order high-pass filter (so_hpf)
- Second order Linkwitz-Riley high-pass filter (so_linkwitz_riley_hpf)
- Second order Linkwitz-Riley low-pass filter (so_linkwitz_riley_lpf)
- Second order Low-pass filter (so_lpf)
- Second order parametric/peaking boost filter with constant-Q (so_parametric_cq_boost)
- Second order parametric/peaking cut filter with constant-Q (so_parametric_cq_cut)
- Second order parametric/peaking filter with non-constant-Q (so_parametric_ncq)

All the filters are now header files and they are located in the `lib/` folder.
In order to use them just copy the `lib/` folder (and rename it if needed) into
your project folder. There's an example how to build later in the README.

## Build & run tests
You can use cmake to build the tests. On Linux, you can just run this:
```sh
./build_tests.sh
```

The above command will build the tests and run them.

> Note: Tests are a bit naive in this case, since it doesn't make
much sense for testing using unit-tests, but anyways, I've added them

## Usage:
The filters can be used in your C++ code in the part where the audio sample is about to be processed. You need to include the _filter_includes.h_ file and create an object with filter you want to apply. Filter parameters can be changed with calculate_coeffs() function. Then in the sample processing function run the filter() function with the current sample as a parameter.

I've used [RackAFX](http://www.willpirkle.com/rackafx/) to test these filters.

## Code example
For example, to use the so-LPF filter then first create a `main.cpp` file
in the top directory of this repo.

```sh
touch main.cpp
```

Then add this code inside:

```cpp
#include <iostream>
#include <memory>
#include "filter_includes.h"

int main() {
    auto filter = std::make_unique<SO_LPF>(1.0, 5000, 96000);
    auto coeffs = filter->get_coeffs();
    auto yn = filter->process(0.303);

    std::cout << "Coeffs: " << std::endl;
    std::cout << "a0: " << coeffs.a0 << std::endl;
    std::cout << "a1: " << coeffs.a1 << std::endl;
    std::cout << "a2: " << coeffs.a2 << std::endl;
    std::cout << "b1: " << coeffs.b1 << std::endl;
    std::cout << "b2: " << coeffs.b2 << std::endl;

    std::cout << "yn: " << yn << std::endl;
    return 0;
}
```

Now to build the file run:
```sh
g++ main.cpp -I./lib
```

And then run the executable:
```sh
./a.out
```

This is will print the filter coefficients and then will process
a sample with the value `0.303`. You should see an output similar
to this:

```
Coeffs: 
a0: 0.0228608
a1: 0.0457215
a2: 0.0228608
b1: -1.63163
b2: 0.723069
yn: 0.00692681
```
