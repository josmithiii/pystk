#include "Common.h"

#include <Effect.h>
#include <Chorus.h>
#include <Echo.h>
#include <FreeVerb.h>
#include <JCRev.h>
#include <LentPitShift.h>
#include <NRev.h>
#include <PRCRev.h>
#include <PitShift.h>

void add_effects_bindings(nb::module_& m) {
    using namespace stk;

    nb::class_<Effect>(m, "Effect")
        .def("channels_out", &Effect::channelsOut)
        .def("set_effect_mix", &Effect::setEffectMix);

    nb::class_<Chorus, Effect>(m, "Chorus")
        .def(nb::init<StkFloat>(), "base_delay"_a = 6000.0)
        .def("clear", &Chorus::clear)
        .def("set_mod_depth", &Chorus::setModDepth)
        .def("set_mod_frequency", &Chorus::setModFrequency)
        .def("last_out", &Chorus::lastOut, "channel"_a = 0)
        .def("tick", nb::overload_cast<StkFloat, unsigned int>(&Chorus::tick), "input"_a = 0.0, "channel"_a = 0)
        .def("process_input", &effect_mono_to_stereo<Chorus>);

    nb::class_<Echo, Effect>(m, "Echo")
        .def(nb::init<unsigned long>(), "maximum_delay"_a = Stk::sampleRate())
        .def("clear", &Echo::clear)
        .def("set_maximum_delay", &Echo::setMaximumDelay)
        .def("set_delay", &Echo::setDelay)
        .def("last_out", &Echo::lastOut)
        .def("tick", nb::overload_cast<StkFloat>(&Echo::tick), "input"_a = 0.0)
        .def("process_input", &effect_mono_to_mono<Echo>);

    nb::class_<FreeVerb, Effect>(m, "FreeVerb")
        .def(nb::init<>())
        .def("set_effect_mix", &FreeVerb::setEffectMix)
        .def("set_room_size", &FreeVerb::setRoomSize)
        .def("get_room_size", &FreeVerb::getRoomSize)
        .def("set_damping", &FreeVerb::setDamping)
        .def("get_damping", &FreeVerb::getDamping)
        .def("set_width", &FreeVerb::setWidth)
        .def("get_width", &FreeVerb::getWidth)
        .def("set_mode", &FreeVerb::setMode)
        .def("get_mode", &FreeVerb::getMode)
        .def("clear", &FreeVerb::clear)
        .def("last_out", &FreeVerb::lastOut)
        .def("tick", nb::overload_cast<StkFloat, StkFloat, unsigned int>(&FreeVerb::tick), "inputL"_a = 0.0, "inputR"_a = 0.0, "channel"_a = 0)
        .def("process_input", &effect_mono_to_stereo<FreeVerb>)
        .def("process_input", &effect_stereo_to_stereo<FreeVerb>);

    nb::class_<JCRev, Effect>(m, "JCRev")
        .def(nb::init<StkFloat>(), "t60"_a = 1.0)
        .def("clear", &JCRev::clear)
        .def("set_t60", &JCRev::setT60)
        .def("last_out", &JCRev::lastOut)
        .def("tick", nb::overload_cast<StkFloat, unsigned int>(&JCRev::tick), "input"_a = 0.0, "channel"_a = 0)
        .def("process_input", &effect_mono_to_stereo<JCRev>);

    nb::class_<LentPitShift, Effect>(m, "LentPitShift")
        .def(nb::init<StkFloat>(), "shift"_a = 1.0)
        .def("clear", &LentPitShift::clear)
        .def("set_shift", &LentPitShift::setShift)
        .def("tick", nb::overload_cast<StkFloat>(&LentPitShift::tick), "input"_a = 0.0)
        .def("process_input", &effect_mono_to_mono<LentPitShift>);

    nb::class_<NRev, Effect>(m, "NRev")
        .def(nb::init<StkFloat>(), "t60"_a = 1.0)
        .def("clear", &NRev::clear)
        .def("set_t60", &NRev::setT60)
        .def("last_out", &NRev::lastOut)
        .def("tick", nb::overload_cast<StkFloat, unsigned int>(&NRev::tick), "input"_a = 0.0, "channel"_a = 0)
        .def("process_input", &effect_mono_to_stereo<NRev>);

    nb::class_<PRCRev, Effect>(m, "PRCRev")
        .def(nb::init<StkFloat>(), "t60"_a = 1.0)
        .def("clear", &PRCRev::clear)
        .def("set_t60", &PRCRev::setT60)
        .def("last_out", &PRCRev::lastOut)
        .def("tick", nb::overload_cast<StkFloat, unsigned int>(&PRCRev::tick), "input"_a = 0.0, "channel"_a = 0)
        .def("process_input", &effect_mono_to_stereo<PRCRev>);

    nb::class_<PitShift, Effect>(m, "PitShift")
        .def(nb::init<>())
        .def("clear", &PitShift::clear)
        .def("set_shift", &PitShift::setShift)
        .def("last_out", &PitShift::lastOut)
        .def("tick", nb::overload_cast<StkFloat>(&PitShift::tick), "input"_a = 0.0)
        .def("process_input", &effect_mono_to_mono<PitShift>);
}