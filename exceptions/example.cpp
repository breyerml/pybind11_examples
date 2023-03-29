#include <stdexcept>
#include <string>

#include "pybind11/pybind11.h"

namespace py = pybind11;

class my_exception : public std::runtime_error {
 public:
  explicit my_exception(const std::string &what = "") : std::runtime_error{what} {}
};

class my_fancy_exception : public my_exception {
 public:
  explicit my_fancy_exception(const std::string &what = "") : my_exception{what} {}
};

void init_exceptions(py::module_ &m) {
  auto base_exception = py::register_exception<my_exception>(m, "MyError");
  py::register_exception<my_fancy_exception>(m, "MyFancyError", base_exception.ptr());
}