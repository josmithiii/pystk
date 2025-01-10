#include <nanobind/nanobind.h>

#include <Stk.h>

namespace nb = nanobind;

using namespace nb::literals;

NB_MODULE(_pystk_impl, m) {
    m.doc() = "This is a \"hello world\" example with nanobind";
    m.def("sample_rate", &stk::Stk::sampleRate);
    m.def("set_sample_rate", &stk::Stk::setSampleRate);
}