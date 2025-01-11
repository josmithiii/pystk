#include "Common.h"

void add_instrmnt_bindings(nb::module_& m);
void add_effects_bindings(nb::module_& m);
void add_filter_bindings(nb::module_& m);
void add_function_bindings(nb::module_& m);

NB_MODULE(_pystk_impl, m) {

    m.def("sample_rate", &Stk::sampleRate);
    m.def("set_sample_rate", &Stk::setSampleRate);
    m.def("rawwave_path", &Stk::rawwavePath);
    m.def("set_rawwave_path", &Stk::setRawwavePath);

    add_instrmnt_bindings(m);
    add_effects_bindings(m);
    add_function_bindings(m);
}