#ifndef PYSTKCOMMON_H
#define PYSTKCOMMON_H

#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/string.h>

#include <Stk.h>

namespace nb = nanobind;
using namespace nb::literals;
using namespace stk;

typedef nb::ndarray<nb::numpy, StkFloat, nb::ndim<2>> audio_frames;
typedef nb::ndarray<nb::numpy, StkFloat, nb::shape<1, -1>> mono_frames;
typedef nb::ndarray<nb::numpy, StkFloat, nb::shape<2, -1>> stereo_frames;
typedef std::map<int, nb::ndarray<StkFloat, nb::ndim<1>>> controls_dict;
typedef const std::map<std::string, int> control_ids;

inline StkFloat midi_to_hz(int midi) {
    return 220.0 * pow(2.0, (midi - 57.0) / 12.0);
}

template<typename T>
mono_frames synth_with_controls(T& self, const unsigned long n_samples, const controls_dict& controls) {
    const auto data = new StkFloat[n_samples];

    nb::capsule owner(data, [](void* p) noexcept {
        delete[] static_cast<StkFloat*>(p);
    });

    for (int n = 0; n < n_samples; n++) {
        for (const auto& [control, value] : controls) {
            self.controlChange(control, value(n));
        }
        data[n] = self.tick();
    }
    return mono_frames(data, {1, n_samples}, owner);
}

template<typename T>
mono_frames effect_mono_to_mono(T& self, const mono_frames& input) {
    const unsigned long n_samples = input.shape(1);

    const auto data = new StkFloat[n_samples];

    nb::capsule owner(data, [](void* p) noexcept {
        delete[] static_cast<StkFloat*>(p);
    });

    for (int n = 0; n < n_samples; n++) {
        data[n] = self.tick(input(0, n));
    }
    return mono_frames(data, {1, n_samples}, owner);
}

template<typename T>
stereo_frames effect_mono_to_stereo(T& self, const mono_frames& input) {
    const unsigned long n_samples = input.shape(1);

    const auto data = new StkFloat[n_samples * 2];

    nb::capsule owner(data, [](void* p) noexcept {
        delete[] static_cast<StkFloat*>(p);
    });

    for (int n = 0; n < n_samples; n++) {
        data[n * 2] = self.tick(input(0, n));
        data[n * 2 + 1] = self.lastOut(1);
    }
    return stereo_frames(data, {2, n_samples}, owner);
}

template<typename T>
stereo_frames effect_stereo_to_stereo(T& self, const stereo_frames& input) {
    const unsigned long n_samples = input.shape(1);

    const auto data = new StkFloat[n_samples * 2];

    nb::capsule owner(data, [](void* p) noexcept {
        delete[] static_cast<StkFloat*>(p);
    });

    for (int n = 0; n < n_samples; n++) {
        data[n * 2] = self.tick(input(0, n), input(1, n));
        data[n * 2 + 1] = self.lastOut(1);
    }
    return stereo_frames(data, {2, n_samples}, owner);
}

#endif //PYSTKCOMMON_H
