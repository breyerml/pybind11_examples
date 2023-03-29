#include "pybind11/pybind11.h"

namespace py = pybind11;

void init_functions(py::module_ &);
void init_enums(py::module_ &);
void init_exceptions(py::module_ &);
void init_classes(py::module_ &);
void init_numpy_performance(py::module_ &m);

PYBIND11_MODULE(showcase, m) {
  init_functions(m);
  init_enums(m);
  init_exceptions(m);
  init_classes(m);
  init_numpy_performance(m);
}