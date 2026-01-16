#include <pybind11/pybind11.h>
#include "LanguageModel.h"

namespace py = pybind11;

PYBIND11_MODULE(my_cpp_model, m) {
    m.doc() = "pybind11 wrapper for C++ Language Model";

    py::class_<LanguageModel>(m, "LanguageModel")
        .def(py::init<int>(), py::arg("k") = 3)
        .def("train", &LanguageModel::train, py::arg("text"))
        .def("generate_text", &LanguageModel::generateText, py::arg("length"));
}
